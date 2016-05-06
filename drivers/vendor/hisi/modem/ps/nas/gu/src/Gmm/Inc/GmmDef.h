/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmDef.h
  Description : WUEPS系统NAS内部GMM功能模块宏定义
  History     :
      1.  张志勇  2003.12.05  文件作成

      2.日    期   : 2009年5月9日
        作    者   : l00130025
        修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，
                     Gmm会反复发起EST_REQ
*******************************************************************************/
#ifndef _GMMDEFINE_H_
#define _GMMDEFINE_H_

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_GMM_CTRL_STATUS_ENUM
 结构说明  : GMM模块的控制状态
*****************************************************************************/
enum NAS_GMM_CTRL_STATUS_ENUM
{
    NAS_GMM_CTRL_STATUS_NULL            = 0 ,
    NAS_GMM_CTRL_STATUS_STARTUP,
    NAS_GMM_CTRL_STATUS_INSERVICE,
    NAS_GMM_CTRL_STATUS_BUTT
};
typedef VOS_UINT8   NAS_GMM_CTRL_STATUS_ENUM_UINT8;


/*****************************************************************************
  4 宏定义
*****************************************************************************/

#define     GMM_FALSE                                       0
#define     GMM_TRUE                                        1

#define     GMM_NG                                          0
#define     GMM_OK                                          1

#define     GMM_FAILURE                                     0
#define     GMM_SUCCESS                                     1

#define     GMM_INVOKE_SUCCESS                              0
#define     GMM_INVOKE_FAILURE                              1


/*****************************************************************************/
/*******************   TIMER的宏定义   ***************************************/
/*****************************************************************************/
/* GMM TIMER 总数，增减TIMER时请同步更新 */

/* 增加CS/PS域DETACH流程保护定时器 */
#define     GMM_TIMER_NUM                               (33)                      /* GMM共使用Timer个数，目前最大64个 */

#define     GMM_TIMER_T3314_CNT                         88                      /* READY TIMER默认间隔次数，默认总长为44s */

#define     GMM_TIMER_ONE_GROUP_NUMR                    (32)

/*****************************************************************************/
/*******************   TIMER运行标志的宏定义   *******************************/
/*****************************************************************************/

#define     GMM_TIMER_T3302_FLG                 (0x00000001<<GMM_TIMER_T3302)   /* T3302定时器标志                          */
#define     GMM_TIMER_T3310_FLG                 (0x00000001<<GMM_TIMER_T3310)   /* T3310定时器标志                          */
#define     GMM_TIMER_T3311_FLG                 (0x00000001<<GMM_TIMER_T3311)   /* T3311定时器标志                          */
#define     GMM_TIMER_T3312_FLG                 (0x00000001<<GMM_TIMER_T3312)   /* T3312定时器标志                          */
#define     GMM_TIMER_T3316_FLG                 (0x00000001<<GMM_TIMER_T3316)   /* T3316定时器标志                          */
#define     GMM_TIMER_T3317_FLG                 (0x00000001<<GMM_TIMER_T3317)   /* T3317定时器标志                          */
#define     GMM_TIMER_T3318_FLG                 (0x00000001<<GMM_TIMER_T3318)   /* T3318定时器标志                          */
#define     GMM_TIMER_T3320_FLG                 (0x00000001<<GMM_TIMER_T3320)   /* T3320定时器标志                          */
#define     GMM_TIMER_T3321_FLG                 (0x00000001<<GMM_TIMER_T3321)   /* T3321定时器标志                          */
#define     GMM_TIMER_T3330_FLG                 (0x00000001<<GMM_TIMER_T3330)   /* T3330定时器标志                          */
#define     GMM_TIMER_1S_FLG                    (0x00000001<<GMM_TIMER_1S)      /* 5S定时器标志                             */
#define     GMM_TIMER_PROTECT_FLG               (0x00000001<<GMM_TIMER_PROTECT) /* 保护定时器标志                           */
#define     GMM_TIMER_PROTECT_FOR_SIGNALING_FLG\
                                  (0x00000001<<GMM_TIMER_PROTECT_FOR_SIGNALING) /* 保护定时器标志                           */
#define     GMM_TIMER_SUSPENDED_FLG             (0x00000001<<GMM_TIMER_SUSPENDED) /* 缓存队列保护定时器标志 */
#define     GMM_TIMER_T3314_FLG                 (0x00000001<<GMM_TIMER_T3314) /* GPRS READY TIMER定时器标志 */
#define     GMM_TIMER_RAU_RSP_FLG               (0x00000001<<GMM_TIMER_RAU_RSP) /* GMM RAU RSP TIMER定时器标志 */
#define     GMM_TIMER_T3319_FLG                 (0x00000001<<GMM_TIMER_T3319)   /* T3319定时器标志                          */
#define     GMM_TIMER_T3340_FLG                 (0x00000001<<GMM_TIMER_T3340)   /* T3340定时器标志                          */

#define     NAS_GMM_TIMER_T3323_FLG             (0x00000001 << GMM_TIMER_T3323) /* T3323定时器运行标志 */

#define     NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG   (0x00000001 << GMM_TIMER_HO_WAIT_SYSINFO)

/*****************************************************************************/
/*******************   TIMER时长的宏定义   ***********************************/
/*****************************************************************************/
#define     GMM_TIMER_T3302_VALUE                               720000
#define     GMM_TIMER_T3310_VALUE                               15000
#define     GMM_TIMER_T3311_VALUE                               15000
#define     GMM_TIMER_T3312_VALUE                               3240000
#define     GMM_TIMER_T3316_VALUE                               30000
#define     GMM_TIMER_T3317_VALUE                               15000
#define     GMM_TIMER_T3318_VALUE                               20000
#define     GMM_TIMER_T3320_VALUE                               15000
#define     GMM_TIMER_T3321_VALUE                               15000
#define     GMM_TIMER_T3330_VALUE                               15000
#define     GMM_TIMER_1S_VALUE                                  1000
#define     GMM_TIMER_PROTECT_VALUE                             10000
/* GMM 关机detach保护定时器时长 */
#define     GMM_TIMER_DETACH_FOR_POWER_OFF_VALUE                5000


/* GMM 保护SYSCFG触发的Detach流程的定时器时常 */
#define     GMM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE            (25000)

/* GMM 保护非SYSCFG触发的PS域的Detach流程的定时器时常,如CGCATT,CGATT */
#define     GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE        (90000)


#define     GMM_TIMER_DETACH_FOR_GCF_POWER_OFF_VALUE           8000

#define     GMM_TIMER_PROTECT_FOR_SIGNALING_VALUE               115000
#define     GMM_TIMER_SUSPENDED_VALUE                           15000           /* 缓存队列保护定时器长度 */
#define     GMM_TIMER_T3314_VALUE                               500             /* GPRS READY TIMER默认检查长度 */
#define     GMM_TIMER_RAU_RSP_VALUE                             5000            /* GMM RAU RSP TIMER定时器长度 */
#define     GMM_TIMER_PROTECT_FOR_RR_REL_VALUE                  10000
#define     GMM_TIMER_PROTECT_OLD_TLLI_VALUE                    30000
#define     GMM_TIMER_T3319_VALUE                               30000
#define     GMM_TIMER_T3340_VALUE                               10000
#define     GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF_VALUE          5000
#define     GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF_VALUE        (6000)
#define     GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_VALUE           (6000)

#define     GMM_TIMER_WAIT_REL_PS_SIGNAL_VALUE                  (20000)

#define     GMM_TIMER_WAIT_CONNECT_REL_VALUE                    (10000)

#define     GMM_TIMER_TC_DELAY_SUSPEND_RSP_VALUE                (2*1000)

#define     GMM_TIMER_T3323_VALUE                               (3240000)       /* 默认54分钟 */

#define     GMM_TIMER_WAIT_SYSINFO_VALUE                        (10000)          /* 默认10秒钟 */


#define     GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU_VALUE         (1*1000)                  /* RadioCapa修改后的延迟时间，定时器超时后检查是否触发RAU */


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
#define     GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO_VALUE         (1*1000)         /*定时器超时触发rau或attach*/
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

#define     GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU_VALUE         (1*1000)         /*voice daomain变化时暂时无法做RAU的等待时长，定时器超时触发RAU */
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

#define     GMM_TIMER_DELAY_PS_SMS_CONN_REL_VALUE               (3*1000)         /* 默认延长3s，释放PS域SMS连接 */

/* Detach Timer 最大超时次数 */
#define     GMM_MAX_DETACH_CNT_WHEN_POWER_OFF               8

#define LTE_NAS_INTER_RAT_UETRAN_CAP_LEN                   (255)  /* EUTRAN CAPBALITY 长度,最长128字节 */


/*****************************************************************************/
/************************* USIM中File ID 的宏定义 ****************************/
/*****************************************************************************/
#define     GMM_USIM_FILE_IMSI                          0x6F07
#define     GMM_USIM_FILE_PS_KEY                        0x6F09
#define     GMM_USIM_FILE_PS_LOC_INFO                   0x6F73
#define     GMM_USIM_FILE_CS_LOC_INFO                   0x6F7E

/*****************************************************************************/
/*******************   空中接口消息的宏定义   ********************************/
/*****************************************************************************/
/* 消息类型无效或UE不支持 */
#define     GMM_MSG_TYPE_INVALID                             0

#define     GMM_MSG_ATTACH_REQUEST                           1
#define     GMM_MSG_ATTACH_ACCEPT                            2
#define     GMM_MSG_ATTACH_COMPLETE                          3
#define     GMM_MSG_ATTACH_REJECT                            4
#define     GMM_MSG_DETACH_REQUEST                           5
#define     GMM_MSG_DETACH_ACCEPT                            6
#define     GMM_MSG_RAU_REQUEST                              8
#define     GMM_MSG_RAU_ACCEPT                               9
#define     GMM_MSG_RAU_COMPLETE                             10
#define     GMM_MSG_RAU_REJECT                               11
#define     GMM_MSG_SERVICE_REQUEST                          12
#define     GMM_MSG_SERVICE_ACCEPT                           13
#define     GMM_MSG_SERVICE_REJECT                           14
#define     GMM_MSG_P_TMSI_REALLOCATION_COMMAND              16
#define     GMM_MSG_P_TMSI_REALLOCATION_COMPLETE             17
#define     GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST     18
#define     GMM_MSG_AUTHENTICATION_AND_CIPHERING_RESPONSE    19
#define     GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT      20
#define     GMM_MSG_AUTHENTICATION_AND_CIPHERING_FAILURE     28
#define     GMM_MSG_IDENTITY_REQUEST                         21
#define     GMM_MSG_IDENTITY_RESPONSE                        22
#define     GMM_MSG_GMM_STATUS                               32
#define     GMM_MSG_GMM_INFORMATION                          33


/*****************************************************************************/
/******************* SIM卡状态的宏定义    ************************************/
/*****************************************************************************/

#define     GMM_SIM_ABSENT                                    0                 /* SIM卡不存在                              */
#define     GMM_SIM_VALID                                     1                 /* SIM卡存在且有效                          */
#define     GMM_SIM_INVALID                                   2                 /* SIM卡存在且无效                          */


/*****************************************************************************/
/******************* attach状态的宏定义    ***********************************/
/*****************************************************************************/
#define     GMM_STATUS_DETACHED                                   0             /* detached                                 */
#define     GMM_STATUS_ATTACHED                                   1             /* attached                                 */

/*****************************************************************************/
/******************* 网络触发detach流程的宏定义    ***************************/
/*****************************************************************************/
#define     GMM_NET_DETACH_REATTACH_REQUIRED                      1             /* re-attach required                       */
#define     GMM_NET_DETACH_REATTACH_NOT_REQUIRED                  2             /* re-attach not required                   */
#define     GMM_NET_DETACH_IMSI_DETACH                            3             /* IMSI detach                              */


/*****************************************************************************/
/******************* 原因值的宏定义    ***************************************/
/*****************************************************************************/
#if 0
#define  NAS_MM_CAUSE_NULL                                      0               /* NULL（无原因）                            */
#define  NAS_MM_CAUSE_IMSI_UNKNOWN_IN_HLR                       2               /* IMSI unknown in HLR                      */
#define  NAS_MM_CAUSE_ILLEGAL_MS                                3               /* Illegal MS                               */
#define  NAS_MM_CAUSE_IMSI_UNKNOWN_IN_VLR                       4               /* IMSI unknown in VLR                      */
#define  NAS_MM_CAUSE_IMSI_NOT_ACCEPTED                         5               /* IMSI not accepted                        */
#define  NAS_MM_CAUSE_ILLEGAL_ME                                6               /* Illegal ME                               */
#define  NAS_MM_CAUSE_GPRS_SERV_NOT_ALLOW                       7               /* GPRS services not allowed                */
#define  NAS_MM_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW     8               /* GPRS services and non-GPRS services      *
                                                                                 * not allowed                              */
#define  NAS_MM_CAUSE_MS_ID_NOT_DERIVED                         9               /* MS identity cannot be derived            *
                                                                                 * by the network                           */
#define  NAS_MM_CAUSE_IMPLICIT_DETACHED                         10              /* Implicitly detached                      */
#define  NAS_MM_CAUSE_PLMN_NOT_ALLOW                            11              /* PLMN not allowed                         */
#define  NAS_MM_CAUSE_LA_NOT_ALLOW                              12              /* Location area not allowed                */
#define  NAS_MM_CAUSE_ROAM_NOT_ALLOW                            13              /* Roaming not allowed in this location area*/
#define  NAS_MM_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN               14              /* GPRS services not allowed in this PLMN   */
#define  NAS_MM_CAUSE_NO_SUITABL_CELL                           15              /* No Suitable Cells In Location Area       */
#define  NAS_MM_CAUSE_MSC_UNREACHABLE                           16              /* MSC temporarily not reachable            */
#define  NAS_MM_CAUSE_NETWORK_FAILURE                           17              /* Network failure                          */
#define  NAS_MM_CAUSE_MAC_FAILURE                               20              /* MAC failure                              */
#define  NAS_MM_CAUSE_SYNCH_FAILURE                             21              /* Synch failure                            */
#define  NAS_MM_CAUSE_PROCEDURE_CONGESTION                      22              /* Congestion                               */
#define  NAS_MM_CAUSE_GSM_AUT_UNACCEPTABLE                      23              /* GSM authentication unacceptable          */
#define  NAS_MM_CAUSE_SERV_OPT_NOT_SUPPORT                      32              /* Service option not supported             */
#define  NAS_MM_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE                33              /* Requested service option not subscribed  */
#define  NAS_MM_CAUSE_SERV_OPT_OUT_OF_ORDER                     34              /* Service option temporarily out of order  */
#define  NAS_MM_CAUSE_CALL_CANNOT_IDENTIFY                      38              /* Call cannot be identified                */
#define  NAS_MM_CAUSE_NO_PDP_CONTEXT_ACT                        40              /* No PDP context activated                 */
#define  NAS_MM_CAUSE_RETRY_UPON_ENTRY_CELL_MIN                 48              /* retry upon entry into a new cell (min)   */
#define  NAS_MM_CAUSE_RETRY_UPON_ENTRY_CELL_MAX                 63              /* retry upon entry into a new cell (max)   */
#define  NAS_MM_CAUSE_SEMANTICALLY_INCORRECT_MSG                95              /* Semantically incorrect message           */
#define  NAS_MM_CAUSE_INVALID_MANDATORY_INF                     96              /*  Invalid mandatory information           */
#define  NAS_MM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE                97              /* Message type non-existent                *
                                                                                 * or not implemented                       */
#define  NAS_MM_CAUSE_MSG_TYPE_NOT_COMPATIBLE                   98              /* Message type not compatible              *
                                                                                 * with the protocol state                  */
#define  NAS_MM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED                99              /* Information element non-existent         *
                                                                                 * or not implemented                       */
#define  NAS_MM_CAUSE_CONDITIONAL_IE_ERROR                      100             /* Conditional IE error                     */
#define  NAS_MM_CAUSE_MSG_NOT_COMPATIBLE                        101             /* Message not compatible with              *
                                                                                 * protocol state                           */
#define  NAS_MM_CAUSE_PROTOCOL_ERROR                            111             /* Protocol error, unspecified              */

#define  NAS_MM_CAUSE_GPRS_NOT_SUPPORTED                        233
#define  NAS_MM_CAUSE_T3310_EXPIRED                             234
#define  NAS_MM_CAUSE_T3317_EXPIRED                             235
#define  NAS_MM_CAUSE_T3321_EXPIRED                             236
#define  NAS_MM_CAUSE_T3330_EXPIRED                             237
#define  NAS_MM_CAUSE_AUTHENTICATION_FAILURE                    238
#define  NAS_MM_CAUSE_COVERAGE_LOST                             239
#define  NAS_MM_CAUSE_UESR_DETACH                               240


#define  NAS_MM_CAUSE_OTHER_CAUSE                               249             /* Other cause                              */

#define  NAS_MM_CAUSE_PAGING_WITH_IMSI                          250             /* Paging with imsi                         */
#define  NAS_MM_CAUSE_TIMER_TIMEOUT                             251             /* Timer timeout                            */
#define  NAS_MM_CAUSE_RR_CONN_EST_FAIL                          252             /* RR connection establish failure          */
#define  NAS_MM_CAUSE_RR_CONN_FAIL                              253             /* RR connection failure                    */
#define  NAS_MM_CAUSE_ACCESS_BARRED                             254             /* access barred                            */
#define  NAS_MM_CAUSE_UNSUITABLE_MODE                           255             /* Unsuitable mode                          */

#endif

#define  GMM_TIMER_EXPIRED_MAX_CNT                              5               /* Timer溢出最大次数(T3310/T3330/T3321)     */
#define  GMM_AUTHEN_ATTEMPT_MAX_CNT                             3               /* Authentication attempt counter最大个数   */
#define  GMM_ATTACH_RAU_ATTEMPT_MAX_CNT                         5               /* ATTACH/RAU attempt counter最大个数       */

/*=========================paging type宏定义================================*/
#define GMM_PAGING_TYPE_PTMSI   0                                               /*寻呼的类型为P-TMSI                        */
#define GMM_PAGING_TYPE_IMSI    1                                               /*寻呼的类型为IMSI                          */



/*=========================空中接口消息中IEI的宏定义========================*/

/* MS to network */
#define GMM_IEI_ADDITIONAL_MOBILE_IDENTITY_VALUE        (0X1A)
#define GMM_IEI_ADDITIONAL_OLD_RAI_VALUE                (0X1B)
#define GMM_IEI_UE_NETWORK_CAPACITY_VALUE               (0x58)
#define GMM_IEI_P_TMSI_TYPE                             (0xE0)

#define GMM_IEI_MS_NETWORK_FEATURE_SUPPORT              (0xC0)
#define GMM_IE_MS_SUPPORT_EXTEND_PERIODIC_TIMER_IN_THIS_DOMAIN   (0x01)
#define GMM_MS_NETWORK_FEATURE_SUPPORT_IE_LEN           (0x01)

#define GMM_IEI_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING                    (0x5D)

#define GMM_IEI_REQUESTED_READY_TIMER_VALUE             0x17                    /* IEI : Requested READY timer value        */
#define GMM_IEI_P_TMSI                                  0x18                    /* IEI : P-TMSI                             */
#define GMM_IEI_P_TMSI_SIGNATURE                        0x19                    /* IEI : P-TMSI signature                   */
#define GMM_IEI_OLD_PTMSI_SIGNATURE                     0x19                    /* IEI : Old P-TMSI signature               */
#define GMM_IEI_AUTHENTICATION_PARAMETER_RESPONSE       0x22                    /* IEI : Authentication parameter Response  */
#define GMM_IEI_IMEISV                                  0x23                    /* IEI : IMEISV                             */
#define GMM_IEI_LIST_OF_RECEIVE_N_PDU_NUMBERS           0x26                    /* IEI : List of Receive N PDU Numbers      */
#define GMM_IEI_DRX_PARAMETER                           0x27                    /* IEI : DRX parameter                      */
#define GMM_IEI_AUTHENTICATION_RESPONSE_PARAMETER       0x29                    /* IEI : Authentication Response parameter  */
#define GMM_IEI_AUTHENTICATION_FAILURE_PARAMETER        0x30                    /* IEI : Authentication Failure parameter   */
#define GMM_IEI_MS_NETWORK_CAPABILITY                   0x31                    /* IEI : MS network capability              */
#define GMM_IEI_PDP_CONTEXT_STATUS                      0x32                    /* IEI : PDP context status                 */
#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
#define GMM_IEI_UPLINK_DATA_STATUS                      0x36                    /* IEI:  Uplink data status                  */
#endif
#define GMM_IEI_TMSI_STATUS                             0x9-                    /* IEI : TMSI status (此宏不使用)           */
#define GMM_IEI_TMSI_STATUS_NO_VALID                    0x90                    /* IEI : TMSI status + TMSI flag : FALSE    */
#define GMM_IEI_TMSI_STATUS_VALID                       0x91                    /* IEI : TMSI status + TMSI flag : TRUE     */

#define GMM_IEI_CLASSMARK2                              0X11
#define GMM_IEI_CLASSMARK3                              0X20
#define GMM_IEI_SUPPORTED_CODEC_LIST                    0x40

/* NETWORK TO MS */

#define GMM_IEI_NEGOTIATED_READY_TIMER_VALUE            0x17                    /* IEI : Negotiated READY timer value       */
#define GMM_IEI_ALLOCATED_PTMSI                         0x18                    /* IEI : Allocated P-TMSI                   */
#define GMM_IEI_P_TMSI_SIGNATURE                        0x19                    /* IEI : P-TMSI signature                   */
#define GMM_IEI_AUTHENTICATION_PARAMETER_RAND           0x21                    /* IEI : Authentication parameter RAND      */
#define GMM_IEI_MS_IDENTITY                             0x23                    /* IEI : MS identity                        */
#define GMM_IEI_GMM_CAUSE                               0x25                    /* IEI : GMM cause                          */
#define GMM_IEI_LIST_OF_RECEIVE_N_PDU_NUMBERS           0x26                    /* IEI : List of Receive N PDU Numbers      */
#define GMM_IEI_INTER_RAT_HANDOVER_INFORMATION          0x27                    /* IEI : Inter RAT handover information     */
#define GMM_IEI_AUTHENTICATION_PARAMETER_AUTN           0x28                    /* IEI : Authentication parameter AUTN      */
#define GMM_IEI_T3302_VALUE                             0x2A                    /* IEI : T3302 value                        */

#define GMM_IEI_E_UTRAN_INTER_RAT_HANDOVER_INFORMATION  0x2B                    /* IEI : E-UTRAN Inter RAT handover information     */

#define GMM_IEI_FULL_NAME_FOR_NETWORK                   0x43                    /* IEI : Full name for network              */
#define GMM_IEI_SHORT_NAME_FOR_NETWORK                  0x45                    /* IEI : Short name for network             */
#define GMM_IEI_LOCAL_TIME_ZONE                         0x46                    /* IEI : Local time zone                    */
#define GMM_IEI_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE      0x47                    /* IEI : Universal time and local time zone */
#define GMM_IEI_LSA_IDENTITY                            0x48                    /* IEI : LSA Identity                       */
#define GMM_IEI_NETWORK_DAYLIGHT_SAVING_TIME            0x49                    /* IEI : Network Daylight Saving Time       */
#define GMM_IEI_EQUIVALENT_PLMNS                        0x4A                    /* IEI : Equivalent PLMNs                   */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER      0x8-                    /* IEI : GPRS CKSN(此宏不使用)              */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER0     0x80                    /* IEI : GPRS CKSN + Possible value : 0     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER1     0x81                    /* IEI : GPRS CKSN + Possible value : 1     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER2     0x82                    /* IEI : GPRS CKSN + Possible value : 2     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER3     0x83                    /* IEI : GPRS CKSN + Possible value : 3     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER4     0x84                    /* IEI : GPRS CKSN + Possible value : 4     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER5     0x85                    /* IEI : GPRS CKSN + Possible value : 5     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER6     0x86                    /* IEI : GPRS CKSN + Possible value : 6     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER7     0x87                    /* IEI : GPRS CKSN +  invalid value : 7     */
#define GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1      0x08                    /* IEI : GPRS CKSN +  invalid value : 7     */
#define GMM_IEI_CELL_NOTIFICATION                       0x8C                    /* IEI : Cell Notification(GSM only)        */
#define GMM_IEI_NETWORK_FEATURE_SUPPORT                 0xB0                    /* IEI : Network feature support            */
#define GMM_IEI_EMERGENCY_NUMBER_LIST                   0x34                    /* IEI : Emergency Number List              */
#define GMM_IEI_REQUESTED_MS_INFORMATION                0xA0                    /* IEI : Requested MS information           */
#define GMM_IEI_COMPREHENSION_REQUIRED                  0x00                    /* IEI : comrehension required */
#define GMM_IEI_FORMAT_T_TYPE                           0x80                    /* IEI : 1:TLV type */
#define GMM_IEI_FORMAT_TYPE_INFO                        0x80                    /* IEI : 0:TV type; 1:TLV type */

#define GMM_NSAPI_MAX_VALUE                             0x0F                    /* NSAPI MAX value */
#define GMM_NSAPI_MIN_VALUE                             0x05                    /* NSAPI MIN value */

#define GMM_NPDU_MAX_LENGTH                             0x11                    /* NPDU */


#define NAS_GMM_IEI_T3323_VALUE                         (0x38)                  /* IEI : T3323 Value */

#define NAS_GMM_IEI_T3312_EXTENDED_VALUE                (0x39)
#define NAS_GMM_IEI_OLD_LOCATION_AREA_IDENTIFICATION    (0x14)
#define NAS_GMM_IEI_TMSI_BASED_NRI_CONTAINER            (0x10)
#define NAS_GMM_IE_TMSI_BASED_NRI_CONTAINER_LEN        (0x02)
#define NAS_GMM_IE_OLD_LOCATION_AREA_IDENTIFICATION_LEN (0x05)

/*====================空中接口消息中各IE取值的宏定义=========================*/

/* 消息首字节：Protocol discriminator + Skip indicator */
#define GMM_PD_GCC                          0x00                                /* group call control                       */
#define GMM_PD_BCC                          0x01                                /* broadcast call control                   */
#define GMM_PD_RESERVED                     0x02                                /* Reserved: was allocated                  *
                                                                                 * in earlier phases of the protocol        */
#define GMM_PD_SCC                          0x03                                /* call control; call related SS messages   */
#define GMM_PD_GTTP                         0x04                                /* GPRS Transparent Transport Protocol(GTTP)*/
#define GMM_PD_MM                           0x05                                /* mobility management messages             */
#define GMM_PD_RRM                          0x06                                /* radio resources management messages      */
#define GMM_PD_GMM                          0x08                                /* GPRS mobility management messages        */
#define GMM_PD_SMS                          0x09                                /* SMS messages                             */
#define GMM_PD_SM                           0x0A                                /* GPRS session management messages         */
#define GMM_PD_NCSS                         0x0B                                /* non call related SS messages             */
#define GMM_PD_LS                           0x0C                                /* Location services                        */
#define GMM_PD_RSV_FOR_EXT_PD               0x0E                                /* reserved for extension of the PD         *
                                                                                 * to one octet length                      */
#define GMM_PD_RSV_FOR_TEST                 0x0F                                /* reserved for tests procedures            */

/* Message type ：见“空中接口消息的宏定义”*/

/* MS network capability：暂无 */

/* Attach type */
                                                                                /* 3  2  1  (bit)                           */
#define GMM_GPRS_ATTACH                     0x01                                /* 0  0  1  GPRS attach                     */
#define GMM_GPRS_ATTACH_WHILE_IMSI_ATTACH   0x02                                /* 0  1  0  GPRS attach while IMSI attached */
#define GMM_COMBINED_GPRS_IMSI_ATTACH       0x03                                /* 0  1  1  Combined GPRS/IMSI attach       */

/* GPRS ciphering key sequence number：见空中接口消息中IEI的宏定义 */

/* DRX parameter：暂无 */

/* Mobile Identity or Identity type */
                                                                                /* 3  2  1  (bit)                           */
#define GMM_MOBILE_ID_NONE                  0x00                                /* 0  0  0  No Identity                     */
#define GMM_MOBILE_ID_IMSI                  0x01                                /* 0  0  1  IMSI                            */
#define GMM_MOBILE_ID_IMEI                  0x02                                /* 0  1  0  IMEI                            */
#define GMM_MOBILE_ID_IMEISV                0x03                                /* 0  1  1  IMEISV                          */
#define GMM_MOBILE_ID_TMSI_PTMSI            0x04                                /* 1  0  0  TMSI/P-TMSI                     */

/* odd/evenindic */
                                                                                /* 4  (bit)                                 */
#define GMM_EVEN_NUM_OF_ID_DIGITS           0x00                                /* 0  even number of identity digits        *
                                                                                 * and also when the TMSI/P-TMSI is used    */
#define GMM_ODD_NUM_OF_ID_DIGITS            0x08                                /* 1  odd number of identity digits         */

/* Routing area identification */

#define GMM_LAC_INVALID_SPECAL_IN_SIM       0x00                                /* SIM中被删除的RAI中LAC的取值              */
#define GMM_LAC0_INVALID                    0xFF                                /* 消息中被删除的RAI中LAC首字节的取值       */
#define GMM_LAC1_INVALID                    0xFE                                /* 消息中被删除的RAI中LAC次字节的取值       */


/* MS Radio Access capability：暂无 */

/* P-TMSI signature */
#define GMM_PTMSI_SIGNATURE_INVALID         0xFF                                /* P-TMSI signature的无效取值               */

/* GPRS Timer：暂无 */

/* TMSI status */
                                                                                /* 1  (bit)                                 */
#define GMM_NO_VALID_TMSI_AVAILABLE         0x00                                /* 0  no valid TMSI available               */
#define GMM_VALID_TMSI_AVAILABLE            0x01                                /* 1  valid TMSI available                  */

/* Attach result + Force to standby not indicated */
                                                                                /* 3  2  1  (bit)                           */
#define GMM_GPRS_ONLY_ATTACHED              0x01                                /* 0  0  1  GPRS only attached              */
#define GMM_COMBINED_GPRS_IMSI_ATTACHED     0x03                                /* 0  1  1  Combined GPRS/IMSI attached     */

/* Force to standby：暂无 */

/* Radio priority：暂无 */

/* GMM cause：见“原因值的宏定义”*/

/* PLMN List：暂无 */

/* Detach type */
        /* MS TO NETWORK */                                                     /* 4  3  2  1  (bit)                        */
#define GMM_GPRS_DETACH_NORMAL              0x01                                /* 0  0  0  1  GPRS detach                  */
#define GMM_IMSI_DETACH_MS_TO_NET           0x02                                /* 0  0  1  0  IMSI detach                  */
#define GMM_COMBINED_DETACH_NORMAL          0x03                                /* 0  0  1  1  Combined GPRS/IMSI detach    */
#define GMM_GPRS_DETACH_POWEROFF            0x09                                /* 1  0  0  1  GPRS detach                  */
#define GMM_COMBINED_DETACH_POWEROFF        0x0B                                /* 1  0  1  1  Combined GPRS/IMSI detach    */
#define GMM_INVALID_DETACH_TYPE             0xFF                                /* 0  0  0  1  GPRS detach                  */

        /* NETWORK TO MS */                                                     /* 3  2  1  (bit)                           */
#define GMM_REATTACH_REQUIRED               0x01                                /* 0  0  1  re-attach required              */
#define GMM_REATTACH_NOT_REQUIRED           0x02                                /* 0  1  0  re-attach not required          */
#define GMM_IMSI_DETACH_NET_TO_MS           0x03                                /* 0  1  1  IMSI detach (after VLR failure) */

/* Update type */
                                                                                /* 3  2  1  (bit)                           */
#define GMM_RA_UPDATING                     0x00                                /* 0  0  0  RA updating                     */
#define GMM_COMBINED_RALA_UPDATING          0x01                                /* 0  0  1  combined RA/LA updating         */
#define GMM_COMBINED_RALAU_WITH_IMSI_ATTACH 0x02                                /* 0  1  0  combined RAU with IMSI attach   */
#define GMM_PERIODC_UPDATING                0x03                                /* 0  1  1  Periodic updating               */
#define GMM_UPDATING_TYPE_INVALID           0x04                                /* RAU类型无效,作为                         *
                                                                                 * Gmm_RoutingAreaUpdateInitiate()参数使用  */

/* Update result */
                                                                                /* 3  2  1  (bit)                           */
#define GMM_RA_UPDATED                          (0x00)                          /* 0  0  0  RA updated                      */
#define GMM_COMBINED_RALA_UPDATED               (0x01)                          /* 0  0  1  combined RA/LA updated          */
#define GMM_RA_UPDATED_ISR_ACTIVE               (0x04)                          /* 1  0  0  RA updated and ISR Active          */
#define GMM_COMBINED_RALA_UPDATED_ISR_ACTIVE    (0x05)                          /* 1  0  1  combined RA/LA updated and ISR activated         */

/* Service type */
                                                                                /* 3  2  1  (bit)                           */
#define GMM_SERVICE_TYPE_SIGNALLING         0x00                                /* 0  0  0  Signalling                      */
#define GMM_SERVICE_TYPE_DATA               0x01                                /* 0  0  1  Data                            */
#define GMM_SERVICE_TYPE_PAGING_RSP         0x02                                /* 0  1  0  Paging Response                 */

/* Follow-on request */
                                                                                /* 4  (bit)                                 */
#define GMM_NO_FOLLOW_ON_REQ_PENDING        0x00                                /* 0  No follow-on request pending          */
#define GMM_FOLLOW_ON_REQ_PENDING           0x08                                /* 1  Follow-on request pending             */

/* IMEISV request */
                                                                                /* 3  2  1  (bit)                           */
#define GMM_IMEISV_NOT_REQUESTED            0x00                                /* 0  0  0  IMEISV not requested            */
#define GMM_IMEISV_REQUESTED                0x01                                /* 0  0  1  IMEISV requested                */



/*==================ATTACH ACCEPT消息中可选IE的宏定义========================*/
#define GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE                    0
#define GMM_ATTACH_ACCEPT_IE_READY_TIMER                        1
#define GMM_ATTACH_ACCEPT_IE_PTMSI                              2
#define GMM_ATTACH_ACCEPT_IE_MS_IDENTITY                        3
#define GMM_ATTACH_ACCEPT_IE_GMM_CAUSE                          4
#define GMM_ATTACH_ACCEPT_IE_T3302_VALUE                        5
#define GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION                  6
#define GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN                    7
#define GMM_ATTACH_ACCEPT_IE_EMERGENCY_NUMBER_LIST              8
#define GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION           9

#define NAS_GMM_ATTACH_ACCEPT_IE_T3323_VALUE                    (12)

#define NAS_GMM_ATTACH_ACCEPT_IE_T3312_EXTENDED_VALUE           (13)
#define NAS_GMM_IE_T3323_VALUE_LEN                              (3)             /* 注册结果中T3323 value IE 的长度 */
#define NAS_GMM_IE_T3312_EXTENDED_VALUE_LEN                     (3)             /* 注册结果中T3312 extended value IE */
#define NAS_GMM_SPEC_PROC_TYPE_RAU                              (0x20)          /* 当前gmm的专有流程为RAU */
#define NAS_GMM_SPEC_PROC_TYPE_DETACH                           (0x30)          /* 当前gmm的专有流程为detach */

/*==================RAU ACCEPT消息中可选IE的宏定义============================*/
#define GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE                    0
#define GMM_RAU_ACCEPT_IE_PTMSI                              1
#define GMM_RAU_ACCEPT_IE_MS_IDENTITY                        2
#define GMM_RAU_ACCEPT_IE_NPDU_NUMBER                        3
#define GMM_RAU_ACCEPT_IE_READY_TIMER                        4
#define GMM_RAU_ACCEPT_IE_GMM_CAUSE                          5
#define GMM_RAU_ACCEPT_IE_T3302_VALUE                        6
#define GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION                  7
#define GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN                    8
#define GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS                 9
#define GMM_RAU_ACCEPT_IE_NETWORK_FEATURE_SURPORT            10
#define GMM_RAU_ACCEPT_IE_EMERGENCY_NUMBER_LIST              11
#define GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION           12
#define GMM_SR_ACCEPT_IE_PDP_CONTEXT_STATUS                  2


/* IE LENGTH define */
#define NAS_GMM_IE_LEN_PDP_STATUS                       0x04

#define NAS_GMM_RAU_ACCEPT_IE_T3323_VALUE                   (15)

#define NAS_GMM_RAU_ACCEPT_IE_T3312_EXTENDED_VALUE          (16)

/*=============================idnns的未知的宏定义============================
 *describe:RRMM_EST_REQ发送函数传参idnns的未知的宏定义,
 *         此种情况有负发送函数内部自行判断idnns的取值
 ===========================================================================*/
#define GMM_RRC_IDNNS_UNKNOWN                                6                  /* RRMM_EST_REQ发送函数传参idnns未知宏定义  */

/*===============================无效值的宏定义==============================*/
#define GMM_CK_INVALID                                     (VOS_UINT8)0             /* CK无效值的宏定义                         */
#define GMM_IK_INVALID                                     (VOS_UINT8)0             /* IK无效值的宏定义                         */
#define GMM_PTMSI_INVALID                                  0xFF                 /* P-TMSI无效值的宏定义                     */

/*==================ATTACH ACCEPT消息中可选IE是否存在的宏定义=================*/
#define GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE_FLG   \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE)
#define GMM_ATTACH_ACCEPT_IE_READY_TIMER_FLG       \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_READY_TIMER)
#define GMM_ATTACH_ACCEPT_IE_PTMSI_FLG             \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_PTMSI)
#define GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG       \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_MS_IDENTITY)
#define GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG         \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_GMM_CAUSE)
#define GMM_ATTACH_ACCEPT_IE_T3302_VALUE_FLG       \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_T3302_VALUE)
#define GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION_FLG \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION)
#define GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG   \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN)
#define GMM_ATTACH_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG   \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_EMERGENCY_NUMBER_LIST)
#define GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG   \
      (VOS_UINT32)(0x01<<GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION)

#define GMM_ATTACH_ACCEPT_IE_T3323_VALUE_FLG   \
      (VOS_UINT32)(0x01 << NAS_GMM_ATTACH_ACCEPT_IE_T3323_VALUE)


#define NAS_GMM_ATTACH_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG \
     (VOS_UINT32)(0x01 << NAS_GMM_ATTACH_ACCEPT_IE_T3312_EXTENDED_VALUE)
/*==================RAU ACCEPT消息中可选IE是否存在的宏定义====================*/
#define GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE_FLG      \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE)
#define GMM_RAU_ACCEPT_IE_PTMSI_FLG                \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_PTMSI)
#define GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG          \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_MS_IDENTITY)
#define GMM_RAU_ACCEPT_IE_NPDU_NUMBER_FLG          \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_NPDU_NUMBER)
#define GMM_RAU_ACCEPT_IE_READY_TIMER_FLG          \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_READY_TIMER)
#define GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG            \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_GMM_CAUSE)
#define GMM_RAU_ACCEPT_IE_T3302_VALUE_FLG          \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_T3302_VALUE)
#define GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION_FLG    \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION)
#define GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG      \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN)

#define GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS_FLG      \
      (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS)
#define GMM_RAU_ACCEPT_IE_NETWORK_FEATURE_SURPORT_FLG      \
          (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_NETWORK_FEATURE_SURPORT)
#define GMM_RAU_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG      \
          (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_EMERGENCY_NUMBER_LIST)
#define GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG      \
          (VOS_UINT32)(0x01<<GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION)

#define GMM_RAU_ACCEPT_IE_T3323_VALUE_FLG          \
      (VOS_UINT32)(0x01<<NAS_GMM_RAU_ACCEPT_IE_T3323_VALUE)


#define NAS_GMM_RAU_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG          \
      (VOS_UINT32)(0x01 << NAS_GMM_RAU_ACCEPT_IE_T3312_EXTENDED_VALUE)

/*===============函数Gmm_AuthenAndCipherResponseMsgMake传参宏定义============*/
#define GMM_AUTH_AND_CIPH_RES_UNNEEDED                  0                       /* AuthenAndCipherResponseMsg无需回传RES    */
#define GMM_AUTH_AND_CIPH_RES_NEEDED                    1                       /* AuthenAndCipherResponseMsg需要回传RES    */

/*==============================MNC[3]无效宏定义=============================*/
#define GMM_PLMNID_MNC3_INVALID                      0x0F                       /* MNC Digit3无效宏定义                     */

/*=======================空口消息必选项有效长度宏定义========================*/
#define     GMM_MSG_LEN_ATTACH_REQUEST                           81
#define     GMM_MSG_LEN_ATTACH_ACCEPT                            11
#define     GMM_MSG_LEN_ATTACH_COMPLETE                          2
#define     GMM_MSG_LEN_ATTACH_REJECT                            3
#define     GMM_MSG_LEN_DETACH_REQUEST                           3
#define     GMM_MSG_LEN_DETACH_ACCEPT                            2
#define     GMM_MSG_LEN_DETACH_ACCEPT_MO                         3
#define     GMM_MSG_LEN_RAU_REQUEST                              61
#define     GMM_MSG_LEN_RAU_ACCEPT                               10
#define     GMM_MSG_LEN_RAU_COMPLETE                             2
#define     GMM_MSG_LEN_RAU_REJECT                               4
#define     GMM_MSG_LEN_SERVICE_REQUEST                          9
#define     GMM_MSG_LEN_SERVICE_ACCEPT                           2
#define     GMM_MSG_LEN_SERVICE_REJECT                           3
#define     GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND              15
#define     GMM_MSG_LEN_P_TMSI_REALLOCATION_COMPLETE             2
#define     GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REQUEST     4
#define     GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_RESPONSE    3
#define     GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REJECT      2
#define     GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_FAILURE     3
#define     GMM_MSG_LEN_IDENTITY_REQUEST                         3
#define     GMM_MSG_LEN_IDENTITY_RESPONSE                        12
#define     GMM_MSG_LEN_GMM_STATUS                               3
#define     GMM_MSG_LEN_GMM_INFORMATION                          2


#define     GMM_INFO_LOCK_SUCCESS                                0
#define     GMM_INFO_LOCK_FAILURE                                1

#define     GMM_INFO_UNLOCK_SUCCESS                              0
#define     GMM_INFO_UNLOCK_FAILURE                              1


#define     GMM_NOT_SUPPORT_GPRS_RAC                             0xFF

#define     GMM_MAX_OPID                                         255
#define     GMM_REQUESTED_READY_TIMER_VALUE                      0x16  /* uints is 2 seconds */

/*=======================空口消息IE长度宏定义========================*/
#define     GMM_MSG_LEN_TLV_PTMSI                                (7)
#define     GMM_MSG_LEN_LV_PTMSI                                 (6)
#define     GMM_MSG_LEN_OLD_RAI                                  (6)
#define     GMM_MSG_LEN_ADDITIONAL_MOBILE_IDENTITY               (7)
#define     GMM_MSG_LEN_ADDITIONAL_OLD_RAI                       (8)
#define     GMM_MGS_LEN_UE_NETWORK_CAPACILITY_LEN                (6)
#define     GMM_MSG_LEN_PTMSI_SIGNATURE                          (4)
#define     GMM_MSG_LEN_TV_PTMSITYPE                             (1)

#define     GMM_MSG_LEN_TLV_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING_LEN    (3)
#define     GMM_MSG_LEN_V_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING_LEN      (1)

#define     GMM_MSG_LEN_CLASSMARK2                              (5)


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
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
#endif/* __cpluscplus */

#endif /* _GMMDEFINE_H_ */
