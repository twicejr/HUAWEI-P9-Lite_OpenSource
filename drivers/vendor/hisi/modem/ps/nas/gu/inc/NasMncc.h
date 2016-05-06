/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMncc.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月25日
  最近修改   : 2007年8月25日
  功能描述   : 定义MNCC原语
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年10月20日
    作    者   : h44270
    修改内容   : 问题单号:A32D14153,来电时，用户尚未接听电话就打开了声码器,，AMR速率变换没有上报
  3.日    期   : 2009年12月04日
    作    者   : h44270
    修改内容   : 问题单号:AT2D15770,CC向TAF多上报了一条SYNC原语

  4.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  5.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS1
******************************************************************************/
#ifndef  NAS_MNCC_H
#define  NAS_MNCC_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "NasCcAirMsg.h"
/* Added by wx270776 for OM融合, 2015-7-24, begin */
#include "msp_diag_comm.h"
/* Added by wx270776 for OM融合, 2015-7-24, end */

#define MNCC_EMERGENCY_MAX_LIST                       (16)
#define MNCC_EMERGENCY_NUMBER_MAX_LENGTH              (46)                      /* Emergency Number information的最大字节数 */


/* MNCC Primitives defination */
typedef enum
{
    /* MN --> CC */
    MNCC_SETUP_REQ,                                                             /* parameter: SETUP message */
    MNCC_EMERG_SETUP_REQ,                                                       /* parameter: EMERGENCY SETUP message */
    MNCC_SETUP_RES,                                                             /* parameter: CONNECT message */
    MNCC_CALL_CONF_REQ,                                                         /* parameter: CALL CONFIRM message */
    MNCC_ALERT_REQ,                                                             /* parameter: ALERTING message */
    MNCC_DISC_REQ,                                                              /* parameter: DISCONNECT message */
    MNCC_REL_REQ,                                                               /* parameter: RELEASE message */
    MNCC_REJ_REQ,                                                               /* parameter: RELEASE COMPLETE message */
    MNCC_FACILITY_REQ,                                                          /* parameter: FACILITY message */
    MNCC_HOLD_REQ,                                                              /* parameter: HOLD message */
    MNCC_RETRIEVE_REQ,                                                          /* parameter: RETRIEVE message */
    MNCC_START_DTMF_REQ,                                                        /* parameter: START DTMF message */
    MNCC_STOP_DTMF_REQ,                                                         /* parameter: None */
    MNCC_MODIFY_REQ,                                                            /* parameter: MODIFY message */
    MNCC_MODIFY_RES,                                                            /* parameter: MODIFY COMPLETE message */
    MNCC_MODIFY_REJ_REQ,                                                        /* parameter: MODIFY REJECT message */
    MNCC_EST_CNF_REQ,                                                           /* parameter: Establishment Cnf message */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-23, begin */
    MNCC_SRVCC_CALL_INFO_NOTIFY,                                                /* parameter:srvcc call info notify message */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-23, end */
    MNCC_CALL_STATUS_NTY,                                                       /* parameter:call status notify message */

    /* CC --> MN */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-23, begin */
    MNCC_SETUP_IND = 0x0100,                                                    /* parameter: SETUP message */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-23, end */
    MNCC_SETUP_CNF,                                                             /* parameter: CONNECT message */
    MNCC_SETUP_COMPL_IND,                                                       /* parameter: None */
    MNCC_CALL_PROC_IND,                                                         /* parameter: CALL PROCEEDING message */
    MNCC_ALERT_IND,                                                             /* parameter: ALERTING message */
    MNCC_DISC_IND,                                                              /* parameter: DISCONNECT message */
    MNCC_REL_IND,                                                               /* parameter: RELEASE message */
    MNCC_REL_CNF,                                                               /* parameter: RELEASE COMPLETE message */
    MNCC_REJ_IND,                                                               /* parameter: Cause or none */
    MNCC_FACILITY_IND,                                                          /* parameter: FACILITY message */
    MNCC_FACILITY_LOCAL_REJ,                                                    /* parameter: Invoke ID */
    MNCC_HOLD_CNF,                                                              /* parameter: None */
    MNCC_HOLD_REJ,                                                              /* parameter: HOLD REJ message */
    MNCC_RETRIEVE_CNF,                                                          /* parameter: None */
    MNCC_RETRIEVE_REJ,                                                          /* parameter: RETRIEVE REJ message */
    MNCC_START_DTMF_CNF,                                                        /* parameter: None */
    MNCC_START_DTMF_REJ,                                                        /* parameter: Cause */
    MNCC_STOP_DTMF_CNF,                                                         /* parameter: None */
    MNCC_MODIFY_IND,                                                            /* parameter: Modify message */
    MNCC_MODIFY_CNF,                                                            /* parameter: Modify Complete message */
    MNCC_MODIFY_REJ_IND,                                                        /* parameter: MODIFY REJECT message */
    MNCC_SYNC_IND,                                                              /* parameter: sync message */
    MNCC_PROGRESS_IND,                                                          /* parameter: Process message */
    MNCC_CC_EST_IND,                                                            /* parameter:CC ESTABLISHMENT message*/
    MNCC_RECALL_IND,                                                            /* parameter:recall message*/
    MNCC_UUSINFO_IND,                                                           /* parameter:Uus message*/

    MNCC_EMERGENCY_LIST_IND,
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-23, begin */
    MNCC_SRVCC_STATUS_IND,                                                      /* parameter:srvcc status notify message */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-23, end */

    MNCC_PRIM_NAME_MAX

} MNCC_PRIM_NAME_ENUM;
typedef VOS_UINT16  MNCC_PRIM_NAME_ENUM_U16;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;
    NAS_CC_MSG_SETUP_MO_STRU            stSetup;
}MNCC_IE_SETUP_CONTAINER_STRU;

typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    MNCC_IE_SETUP_CONTAINER_STRU        stSetupContainer;
}MNCC_MSG_EST_STRU;

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-12, begin */
/*****************************************************************************
 枚举名    : NAS_MNCC_SRVCC_STATUS_ENUM_UINT32
 枚举说明  : cc模块通知Call模块SRVCC的状态枚举值
 1.日    期   : 2013年9月23日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum NAS_MNCC_SRVCC_STATUS_ENUM
{
    NAS_MNCC_SRVCC_STATUS_START        = 0,     /* SRVCC开始 */
    NAS_MNCC_SRVCC_STATUS_SUCCESS      = 1,     /* SRVCC成功 */
    NAS_MNCC_SRVCC_STATUS_FAIL         = 2,     /* SRVCC失败 */
    NAS_MNCC_SRVCC_STATUS_BUTT
};
typedef VOS_UINT32  NAS_MNCC_SRVCC_STATUS_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MNCC_CALL_STATUS_ENUM_UINT8
 枚举说明  : call模块通知cc模块的呼叫建立状态枚举值
  1.日    期   : 2015年8月14日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
enum MNCC_CALL_STATUS_ENUM
{
    MNCC_CALL_STATUS_SETUP_SUCC         = 0,                                    /* 呼叫建立成功 */
    MNCC_CALL_STATUS_SETUP_FAIL         = 1,                                    /* 呼叫建立失败 */
    MNCC_CALL_STATUS_BUTT
};
typedef VOS_UINT8  MNCC_CALL_STATUS_ENUM_UINT8;


/*****************************************************************************
 结构名    : MNCC_SRVCC_STATUS_IND_STRU
 结构说明  : CC模块通知CALL模块SRVCC过程中的呼叫信息通知消息结构体

  1.日    期   : 2013年9月23日
    作    者   : w00176964
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MNCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus;
    VOS_UINT8                           aucReserve1[4];    /*预留*/
}MNCC_SRVCC_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : MNCC_ENTITY_STATUS_STRU
 结构说明  : CALL模块通知CC模块的呼叫实体信息结构体

  1.日    期   : 2013年9月23日
    作    者   : w00176964
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           aucReserve1[2] ;
    NAS_CC_IE_BC_STRU                   stBC1;
    NAS_CC_IE_BC_STRU                   stBC2;
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldAuxState;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyAuxState;
    VOS_UINT8                           aucReserve2[1] ;
}MNCC_ENTITY_STATUS_STRU;

#define   MNCC_MAX_ENTITY_NUM      7

/*****************************************************************************
 结构名    : MNCC_SRVCC_CALL_INFO_NOTIFY_STRU
 结构说明  : CALL模块通知CC模块srvcc过程中从IMS域同步过来的呼叫实体信息结构体

  1.日    期   : 2013年9月23日
    作    者   : w00176964
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucTchAvail;
    VOS_UINT8                           aucReserve[2];
    MNCC_ENTITY_STATUS_STRU             astEntityStatus[MNCC_MAX_ENTITY_NUM];
}MNCC_SRVCC_CALL_INFO_NOTIFY_STRU;
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-12, end */

/*****************************************************************************
 结构名    : MNCC_CALL_STATUS_NTY_STRU
 结构说明  : CALL模块通知CC模块呼叫状态的结构体

  1.日    期   : 2015年8月14日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MNCC_CALL_STATUS_ENUM_UINT8         enCallStatus;
    VOS_UINT8                           aucReserve1[3];    /*预留*/
}MNCC_CALL_STATUS_NTY_STRU;

/* Union of parameters in MNCC primitives (MN -> CC) */
typedef union
{
    NAS_CC_MSG_SETUP_MO_STRU            stSetup;
    NAS_CC_MSG_EMERGENCY_STEUP_STRU     stEmerg;
    NAS_CC_MSG_ALERTING_MO_STRU         stAlert;
    NAS_CC_MSG_CONNECT_MO_STRU          stConn;
    NAS_CC_MSG_CALL_CNF_STRU            stCallCnf;
    NAS_CC_MSG_MODIFY_STRU              stModify;
    NAS_CC_MSG_MODIFY_COMPLETE_STRU     stModifyRes;
    NAS_CC_MSG_MODIFY_REJ_STRU          stModifyRej;
    NAS_CC_MSG_DISCONNECT_MO_STRU       stDisc;
    NAS_CC_MSG_RELEASE_MO_STRU          stRel;
    NAS_CC_MSG_FACILITY_MO_STRU         stFac;
    NAS_CC_MSG_START_DTMF_STRU          stStartDtmf;
    NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU stRelComp;
    NAS_CC_MSG_CC_EST_CNF_STRU          stCcEstCnf;

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-19, begin */
    MNCC_SRVCC_CALL_INFO_NOTIFY_STRU    stSrvccCallInfoNtf;
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-19, end */
    MNCC_CALL_STATUS_NTY_STRU           stCallStatusNtf;
} MNCC_REQ_PARAM_UNION;

/* MNCC_SYNC_IND */
enum NAS_CC_RADIO_ACCESS_MODE_ENUM
{
    NAS_CC_RA_MODE_GSM,
    NAS_CC_RA_MODE_WCDMA
};
typedef VOS_UINT32  NAS_CC_RADIO_MODE_ENUM_U32;

/* 和nasrrcinterface.h中的定义保持一致 */
/*****************************************************************************
 枚举名    : NAS_CC_TCH_TYPE_ENUM_U32
 枚举说明  : CC接口的定义，需要与RRMM接口定义一致
 1.日    期   : 2012年2月9日
   作    者   : zhoujun 40661
   修改内容   : modify
*****************************************************************************/
enum NAS_CC_CHANNEL_TYPE_ENUM
{
    NAS_CC_TCH_SINGAL_MOD,                                                      /* 仅信令模式*/
    NAS_CC_TCH_TYPE_FR,                                                         /* full rate */
    NAS_CC_TCH_TYPE_HR,                                                         /* half rate */
    NAS_CC_TCH_TYPE_EFR,                                                        /* enhanced full rate */
    NAS_CC_TCH_TYPE_AHR,                                                        /* a half rate */
    NAS_CC_TCH_TYPE_AMR,                                                        /* amr */
    NAS_CC_TCH_TYPE_AMR2,                                                       /* amr2 */
    NAS_CC_TCH_TYPE_AMRWB = 0x08,

    NAS_CC_TCH_CSD_9600,                                                        /* CSD */
    NAS_CC_TCH_CSD_4800,                                                        /* CSD */
    NAS_CC_TCH_CSD_2400,                                                        /* CSD */
    NAS_CC_TCH_CSD_14400,                                                       /* CSD */


    NAS_CC_TCH_TYPE_BUFF                                                        /* invalid value */
};
typedef VOS_UINT32  NAS_CC_TCH_TYPE_ENUM_U32;

/* 和nasrrcinterface.h中的定义保持一致 */
enum NAS_CC_SUB_CHANNEL_TYPE_ENUM
{
    NAS_CC_CHANNEL_RATE_NULL   = 0x00,                                          /* rate 0kbps/s */
    NAS_CC_CHANNEL_RATE_475    = 0x01,                                          /* rate 4.75kbps/s */
    NAS_CC_CHANNEL_RATE_515    = 0x02,                                          /* rate 5.15kbps/s */
    NAS_CC_CHANNEL_RATE_59     = 0x04,                                          /* rate 5.9kbps/s */
    NAS_CC_CHANNEL_RATE_67     = 0x08,                                          /* rate 6.7kbps/s */
    NAS_CC_CHANNEL_RATE_74     = 0x10,                                          /* rate 7.4kbps/s */
    NAS_CC_CHANNEL_RATE_795    = 0x20,                                          /* rate 7.95kbps/s */
    NAS_CC_CHANNEL_RATE_102    = 0x40,                                          /* rate 10.2kbps/s */
    NAS_CC_CHANNEL_RATE_122    = 0x80,                                          /* rate 12.2kbps/s */
    NAS_CC_CHANNEL_RATE_BUFF                                                    /* invalid value */
};
typedef VOS_UINT32  NAS_CC_RATE_TYPE_ENUM_U32;

enum NAS_CC_ALERT_IND_ENUM
{
    NAS_CC_ALERT_START,
    NAS_CC_ALERT_STOP,
    NAS_CC_ALERT_IND_BUFF
};
typedef VOS_UINT32  NAS_CC_ALERT_IND_ENUM_U32;

#define NAS_CC_MAX_UUIE_MSG_NUM         (7)
typedef struct
{
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType;
    VOS_UINT8                           aucReserved3[3];
    NAS_CC_IE_USER_USER_STRU            stUuieInfo;
}NAS_CC_UUS1_INFO_STRU;

typedef struct
{
    NAS_CC_ALERT_IND_ENUM_U32           enAlertInd;
    VOS_UINT32                          ulTchAvail;                             /*TCH available, VOS_TRUE:存在; VOS_FALSE:不存在*/
    NAS_CC_RADIO_MODE_ENUM_U32          enRaMode;
    NAS_CC_TCH_TYPE_ENUM_U32            enTchType;
}NAS_CC_SYNC_IND_STRU;

typedef struct
{
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgtype;
    VOS_UINT8                           aucReserved3[3];
    NAS_CC_MSG_USER_INFO_STRU           stUserInfo;
}NAS_CC_UUS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MNCALL_EMERGENCY_CONTENT_STRU
 结构说明  : CC上报的紧急呼
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCategoryValue;                        /* Emergency Service Category Value         */
    VOS_UINT8                           ucEmcNumLen;                            /*紧急呼号码长度，即aucEmcNum的有效长度*/
    VOS_UINT8                           aucEmergencyNum[MNCC_EMERGENCY_NUMBER_MAX_LENGTH];
}MNCC_EMERGENCY_CONTENT_STRU;

/*****************************************************************************
 结构名    : NAS_CC_EMERGENCY_LIST_STRU
 结构说明  : CC上报的紧急呼列表
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucEmergencyNumber;
    VOS_UINT8                           aucReserved[3];
    MNCC_EMERGENCY_CONTENT_STRU         astEmergencyLists[MNCC_EMERGENCY_MAX_LIST];
}MNCC_EMERGENCY_LIST_IND_STRU;

/* Union of parameters in MNCC primitives (CC -> MN) */
typedef union
{
    NAS_CC_MSG_SETUP_MT_STRU            stSetup;
    NAS_CC_MSG_ALERTING_MT_STRU         stAlert;
    NAS_CC_MSG_CONNECT_MT_STRU          stConn;
    NAS_CC_MSG_CALL_PROC_STRU           stCallProc;
    NAS_CC_MSG_MODIFY_STRU              stModify;
    NAS_CC_MSG_DISCONNECT_MT_STRU       stDisc;
    NAS_CC_MSG_RELEASE_MT_STRU          stRel;
    NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU stRelComp;
    NAS_CC_MSG_FACILITY_MT_STRU         stFac;
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause;
    VOS_UINT8                           ucInvokeId;
    NAS_CC_SYNC_IND_STRU                stSyncInd;
    MNCC_MSG_EST_STRU                   stEstInd;
    NAS_CC_MSG_RECALL_STRU              stRecall;
    NAS_CC_MSG_PROGRESS_STRU            stProgressInd;
    NAS_CC_UUS_INFO_IND_STRU            stUusInfo;

    MNCC_EMERGENCY_LIST_IND_STRU        stEmcListInd;

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-19, begin */
    MNCC_SRVCC_STATUS_IND_STRU          stSrvccStaInd;
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-19, end */
} MNCC_IND_PARAM_UNION;


/* Structure of the MNCC primitive message (MN -> CC) */
typedef struct
{
    VOS_MSG_HEADER
    MNCC_PRIM_NAME_ENUM_U16             enPrimName;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulParamLen;
    MNCC_REQ_PARAM_UNION                unParam;
    VOS_UINT8                           ucRedialFlg;
    VOS_UINT8                           aucReserve[3];
} MNCC_REQ_PRIM_MSG_STRU;

/* Structure of the MNCC primitive message (CC -> MN) */
typedef struct
{
    VOS_MSG_HEADER
    MNCC_PRIM_NAME_ENUM_U16             enPrimName;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulParamLen;
    MNCC_IND_PARAM_UNION                unParam;
} MNCC_IND_PRIM_MSG_STRU;

/*****************************************************************************
 函 数 名  : NAS_CC_ActUus1Info
 功能描述  : 激活UUS1相关信息保存的UUS1信息
 输入参数  : enMsgType   :需激活的消息类型
             pstUuieInfo :激活UUIE的信息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_ActUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
);

/*****************************************************************************
 函 数 名  : NAS_CC_GetAllUus1Info
 功能描述  : 获取所有激活UUS1信息
 输入参数  : 无
 输出参数  : pulActNum      :已激活UUS1个数
             pstUus1Info    :已激活UUS1相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_GetAllUus1Info(
    VOS_UINT32                          *pulActNum,
    NAS_CC_UUS1_INFO_STRU               *pstUus1Info
);

/*****************************************************************************
 函 数 名  : NAS_CC_DeactUus1Info
 功能描述  : 去激活UUS1信息
 输入参数  : enMsgType   :需激活的消息类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_DeactUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType
);

/* Modified by z40661 for DMT工程修改, 2013-2-01, begin */
VOS_VOID NAS_CC_InitUus1Info( VOS_VOID );
/* Modified by z40661 for DMT工程修改, 2013-2-01, end */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* NAS_MNCC_H */

