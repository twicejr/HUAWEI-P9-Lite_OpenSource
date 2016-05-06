/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasGlobal.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-08-25
  Description : 定义了GMM模块公共接入层全局共享的数据结构
  History     :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  3.日    期   : 2007年12月14日
    作    者   : s46746
    修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
  4.日    期   : 2009年05月14日
    作    者   : h44270
    修改内容   : 问题单号:AT2D11898/AT2D11828,在IDLE态下发送PS域短信，没有按照ATTACH ACCEPT消息中Radio Priority for SMS来请求资源
  5.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  6.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
************************************************************************/

#ifndef _GMM_CAS_DEF_H_
#define _GMM_CAS_DEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#pragma pack(4)                         /* 1字节对齐，数据结构定义保证4字节对齐 */
                                        /* 放在include后，不影响其他头文件的pack参数 */
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     GMM_TIMER_NOT_RESUME            0
#define     GMM_TIMER_RESUME                1

/*----------2.3 GMM消息矩阵宏定义 ------------*/
#define     GMM_MATRIX_STATE_MAX            25              /* GMM消息矩阵状态的最大数目 */
#define     GMM_MATRIX_EVENT_MAX            73              /* GMM消息矩阵事件的最大数目 */
#define     GMM_STATE_TAB_RESERVED          255             /* GMM内部状态映射表保留项 */

#define     GMM_NAS_MSG_HEADER_MIN          2               /* GMM消息头最短长度 */
#define     GMM_NAS_MSG_DATA_MAX            2048            /* GMM消息内容的最大长度 */

/*----------2.4 GMM消息事件名称宏定义 ------------*/
#define     GMM_EVENT_ID_TIMER_T3302                        1
#define     GMM_EVENT_ID_TIMER_T3310                        2
#define     GMM_EVENT_ID_TIMER_T3311                        3
#define     GMM_EVENT_ID_TIMER_T3312                        4
#define     GMM_EVENT_ID_TIMER_T3316                        5
#define     GMM_EVENT_ID_TIMER_T3317                        6
#define     GMM_EVENT_ID_TIMER_T3318                        7
#define     GMM_EVENT_ID_TIMER_T3320                        8
#define     GMM_EVENT_ID_TIMER_T3321                        9
#define     GMM_EVENT_ID_TIMER_T3330                        10
#define     GMM_EVENT_ID_TIMER_5S                           11
#define     GMM_EVENT_ID_TIMER_PROT                         12
#define     GMM_EVENT_ID_TIMER_PROT_SIGNAL                  13
#define     GMM_EVENT_ID_TIMER_BUF_QUEUE                    14
#define     GMM_EVENT_ID_TIMER_T3314                        15
#define     GMM_EVENT_ID_PS_USIM_AUTN_CNF                   16
#define     GMM_EVENT_ID_RRMM_PAGING_IND                    17
#define     GMM_EVENT_ID_RRMM_EST_CNF                       18
#define     GMM_EVENT_ID_RRMM_DATA_IND                      19
#define     GMM_EVENT_ID_RRMM_REL_IND                       20
#define     GMM_EVENT_ID_RRMM_SECUR_IND                     21
#define     GMM_EVENT_ID_RRMM_AC_CH_IND                     22
#define     GMM_EVENT_ID_GMMRABM_REEST_REQ                  23
#define     GMM_EVENT_ID_MMCGMM_SYS_INFO_IND                24
#define     GMM_EVENT_ID_MMCGMM_COVER_LOST_IND              25
#define     GMM_EVENT_ID_MMCGMM_POWER_OFF_REQ               26
#define     GMM_EVENT_ID_MMCGMM_LU_RESULT_IND               27          /* GMM暂不使用 */
#define     GMM_EVENT_ID_MMCGMM_CM_SERVICE_IND              28
#define     GMM_EVENT_ID_MMCGMM_CM_SRV_REJ_IND              29
#define     GMM_EVENT_ID_MMCGMM_PLMN_SEARCH_INIT            30
#define     GMM_EVENT_ID_MMCGMM_START_REQ                   31
#define     GMM_EVENT_ID_MMCGMM_PLMN_USER_SEL_REQ           32
#define     GMM_EVENT_ID_MMCGMM_DETACH_REQ                  33
#define     GMM_EVENT_ID_MMCGMM_AUTN_FAIL_IND               34
#define     GMM_EVENT_ID_MMCGMM_REGISTER_INIT               35
#define     GMM_EVENT_ID_MMCGMM_MODE_CH_REQ                 36
#define     GMM_EVENT_ID_MMCGMM_ATTACH_REQ                  37
#define     GMM_EVENT_ID_GMMSM_ESTABLISH_REQ                38
#define     GMM_EVENT_ID_GMMSM_DATA_REQ                     39
#define     GMM_EVENT_ID_GMMSM_PDP_STATUS_IND               40
#define     GMM_EVENT_ID_PMMSMS_EST_REQ                     41
#define     GMM_EVENT_ID_PMMSMS_UNITDATA_REQ                42
#define     GMM_EVENT_ID_TCGMM_DATA_REQ                     43
#define     GMM_EVENT_ID_TCGMM_TEST_REQ                     44
#define     GMM_EVENT_ID_LL_GMM_STATUS_IND                  45
#define     GMM_EVENT_ID_LL_UNITDATA_IND                    46
#define     GMM_EVENT_ID_GMMRABM_RAU_RSP                    47
#define     GMM_EVENT_ID_GRRMM_PAGING_IND                   48
#define     GMM_EVENT_ID_MMCGMM_GAS_SYS_IND                 49
#define     GMM_EVENT_ID_MMCGMM_SUSPEND_IND                 50
#define     GMM_EVENT_ID_MMCGMM_RESUME_IND                  51
#define     GMM_EVENT_ID_MMCGMM_SUSPEND_CNF                 52

#define     GMM_EVENT_ID_MSG_ATTACH_ACCEPT                  53
#define     GMM_EVENT_ID_MSG_ATTACH_REJECT                  54
#define     GMM_EVENT_ID_MSG_DETACH_REQUEST                 55
#define     GMM_EVENT_ID_MSG_DETACH_ACCEPT                  56
#define     GMM_EVENT_ID_MSG_RAU_ACCEPT                     57
#define     GMM_EVENT_ID_MSG_RAU_REJECT                     58
#define     GMM_EVENT_ID_MSG_SERVICE_ACCEPT                 59
#define     GMM_EVENT_ID_MSG_SERVICE_REJECT                 60
#define     GMM_EVENT_ID_MSG_PTMSI_REALLOC                  61
#define     GMM_EVENT_ID_MSG_AUTH_AND_CIPH_REQ              62
#define     GMM_EVENT_ID_MSG_AUTH_AND_CIPH_REJ              63
#define     GMM_EVENT_ID_MSG_IDENTITY_REQUEST               64
#define     GMM_EVENT_ID_MSG_GMM_STATUS                     65
#define     GMM_EVENT_ID_MSG_GMM_INFORMATION                66
#define     GMM_EVENT_ID_MSG_NONEXIST                       67          /* 未定义的消息事件 */
#define     GMM_EVENT_ID_SM_DATA_IND                        68
#define     GMM_EVENT_ID_SMS_DATA_IND                       69
#define     GMM_EVENT_ID_TC_DATA_IND                        70
#define     GMM_EVENT_ID_NONE_DATA_IND                      71          /* 未定义模块发送的data ind事件 */
#define     GMM_EVENT_ID_GRRMM_GPRS_SUSPENED_IND            72
#define     GMM_EVENT_ID_GRRMM_GPRS_RESUME_IND              73

#define     GMM_EVENT_ID_AGENT_PMM_INQUIRE                  128         /* OM消息AGENT_PMM_INQUIRE*/
#define     GMM_EVENT_ID_WUEPS_RESET_REQ                    129         /* ADMIN消息WUEPS_RESET_REQ*/

#define     GMM_EVENT_ID_INVALID                            255

/*----------2.5 GMM内部新增数据类型定义 ------------*/
/* GMM消息矩阵的单元处理函数指针 */
typedef     VOS_UINT32    (*GMM_CELL_FUN_TYPE)(VOS_VOID *);

/* RAU reject原因值处理结果类型 */
typedef     VOS_UINT32      GMM_RAU_REJ_RESULT_TYPE;
#define     GMM_RAU_REJ_NULL_FLG                            0x00        /* 无特殊操作标志 */
#define     GMM_RAU_REJ_ABNORMAL_FLG                        0x01        /* 异常情况标志 */
#define     GMM_RAU_REJ_ATTACH_FLG                          0x02        /* 进行ATTACH标志 */


/*----------2.6 GMM消息处理SIM文件号宏值 ------------*/
#define     GMM_USIM_FILE_PS_KEY_GPRS                       0x4F52      /* 2G access in 3G USIM */
#define     GMM_USIM_FILE_KC_KEY_GPRS                       0x6F52      /* GPRS Kc Key in 2G SIM */
#define     GMM_USIM_FILE_LOC_INFO_GPRS                     0x6F53      /* GPRS location info in 2G SIM */

/* LLC data req消息内容最大长度 */
#define     GMM_LLC_MSG_PDULEN_MAX                          4096
/* DRX参数中Split pg cycle code对应表最大长度 */
#define     GMM_DRX_CYCLE_CODE_TAB_MAX                      34
#define     GMM_DRX_CYCLE_CODE_NUMBER                       (GMM_DRX_CYCLE_CODE_TAB_MAX+64)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
typedef enum
{
    GMM_NULL_STAT = 0,          /* s0 : GMM-NULL */
    GMM_DER_NRM_SRV_STAT,       /* s1 : GMM-DEREGISTERED.NORMAL-SERVICE */
    GMM_DER_LMT_SRV_STAT,       /* s2 : GMM-DEREGISTERED.LIMITED-SERVICE */
    GMM_DER_ACH_NED_STAT,       /* s3 : GMM-DEREGISTERED.ATTACH-NEEDED */
    GMM_DER_ATMPT_ACH_STAT,     /* s4 : GMM-DEREGISTERED.ATTEMPTING-TO-ATTACH */
    GMM_DER_NO_IMSI_STAT,       /* s5 : GMM-DEREGISTERED.NO-IMSI */
    GMM_DER_NO_CELL_STAT,       /* s6 : GMM-DEREGISTERED.NO-CELL-AVAILABLE */
    GMM_DER_PLMN_SRCH_STAT,     /* s7 : GMM-DEREGISTERED.PLMN-SEARCH */
    GMM_REG_INIT_STAT,          /* s8 : GMM-REGISTERED-INITIATED */
    GMM_REG_NRM_SRV_STAT,       /* s9 : GMM-REGISTERED.NORMAL-SERVICE */
    GMM_REG_UPDT_NED_STAT,      /* s10: GMM-REGISTERED.UPDATE-NEEDED */
    GMM_REG_ATMPT_UPDT_STAT,    /* s11: GMM-REGISTERED.ATTEMPTING-TO-UPDATE */
    GMM_REG_NO_CELL_STAT,       /* s12: GMM-REGISTERED.NO-CELL-AVAILABLE */
    GMM_REG_LMT_SRV_STAT,       /* s13: GMM-REGISTERED.LIMITED-SERVICE */
    GMM_REG_ATMPT_UPDT_MM_STAT, /* s14: GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM */
    GMM_REG_PLMN_SRCH_STAT,     /* s15: GMM-REGISTERED.PLMN-SEARCH */
    GMM_REG_IMSI_DCH_INIT_STAT, /* s16: GMM-REGISTERED.IMSI-DETACH-INITIATED */
    GMM_REG_WAIT_RAU_STAT,      /* s17: GMM-REGISTERED-WAIT-FOR-RAU */
    GMM_DER_INIT_STAT,          /* s18: GMM-DEREGISTERED-INITIATED */
    GMM_RAU_INIT_STAT,          /* s19: GMM-ROUTING-AREA-UPDATING-INITIATED */
    GMM_SRV_REQ_INIT_STAT,      /* s20: GMM-SERVICE-REQUEST-INITIATED (UMTS only) */
    GMM_TC_ACT_STAT,            /* s21: GMM-TC-ACTIVE */
    GMM_CAS_SUSPN_STAT,         /* s22: GMM-CAS-SUSPEND */
    GMM_REG_SUSPN_STAT,         /* s23: GMM-REGISTERED.SUSPENDED (GSM only) */
    GMM_DER_SUSPN_STAT          /* s24: GMM-DEREGISTERED-SUSPENDED (GSM only) */
}GMM_STATE_ID_ENUM;

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------7.1 GMM全局共享数据结构 -------------*/
/*=======================================================*/

/*----------7.1.1 GMM_CAS_CTRL_STRU ------------*/
/* GMM CAS过程参数临时记录结构 */
typedef struct
{
    VOS_UINT8       ucRaiChgFlg;
    VOS_UINT8       ucLaiChgFlg;
    VOS_UINT8       ucDrxLengthChgFlg;
    VOS_UINT8       ucGsmCellChgFlg;        /* GSM cell ID更新标志 */

    VOS_UINT8       ucSuspendCause;         /* 挂起原因 */
    VOS_UINT8       ucSuspendOrigen;        /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA*/
    VOS_UINT8       ucCsResumeResult;       /* CS域切换结果 */
    VOS_UINT8       ucPsResumeResult;       /* PS域切换结果 */

    VOS_UINT8       ucResumeOrigen;         /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8       aucReserve[3];
}GMM_CAS_PARAM_TEMP_ST;

/*----------7.1.2 GMM_CAS_CTRL_STRU ------------*/
/*
 GMM公用接入层控制数据结构
 1.GMM挂起状态下公用标志量记录
 2.GMM挂起状态下共享参数传递
*/
/* V200R001版本新增 */

/*===== 参数宏定义 =====*/
#define     GMM_AUTN_KC_LENGTH              16          /* GSM鉴权密钥Kc的长度 */
#define     GMM_MAX_SIZE_SRES               4           /* SRES长度 */

/* GPRS服务的GMM状态 */
typedef VOS_UINT8   GMM_GPRS_SRV_STATE;
#define GMM_AGB_GPRS_IDLE                   0x00        /* A/Gb模式下GPRS空闲态*/
#define GMM_AGB_GPRS_STANDBY                0x01        /* A/Gb模式下GPRS等待态*/
#define GMM_AGB_GPRS_READY                  0x02        /* A/Gb模式下GPRS可用态*/
#define GMM_IU_PMM_DETACHED                 GMM_AGB_GPRS_IDLE        /* Iu模式下GPRS无效态*/
#define GMM_IU_PMM_IDLE                     GMM_AGB_GPRS_STANDBY     /* Iu模式下GPRS空闲等待态*/
#define GMM_IU_PMM_CONNECTED                GMM_AGB_GPRS_READY       /* Iu模式下GPRS连接态*/

/* ulGmmCasState参数值 */
typedef VOS_UINT8  GMM_CAS_STATE;
#define     GMM_CAS_SUSPEND                 1           /* GMM CAS中消息挂起方式 */
/*
    #define     GMM_CAS_WCDMA_DETACHED          2
    #define     GMM_CAS_WCDMA_CONNECTED         3
    #define     GMM_CAS_WCDMA_IDLE              4
    #define     GMM_CAS_GSM_IDLE                5
    #define     GMM_CAS_GSM_READY               6
    #define     GMM_CAS_GSM_STANDBY             7
*/
#define     GMM_CAS_WCDMA_AS                8           /* GMM CAS中的WCDMA接入方式 */
#define     GMM_CAS_GSM_AS                  9           /* GMM CAS中的GSM接入方式 */

/* TLLI类型值定义 */
typedef VOS_UINT8   GMM_TLLI_TYPE;
#define GMM_RANDOM_TLLI                     0
#define GMM_LOCAL_TLLI                      1
#define GMM_FOREIGN_TLLI                    2
#define GMM_AUXILIARY_TLLI                  3
#define GMM_OTHERS_TLLI                     4
#define GMM_INVALID_TLLI                    5

#define GMM_NOT_SUSPEND_LLC                 0
#define GMM_SUSPEND_LLC_FOR_CS              1
#define GMM_SUSPEND_LLC_FOR_RAU             2
#define GMM_SUSPEND_LLC_FOR_CELL_RESEL      4
#define GMM_SUSPEND_LLC_FOR_OUT_OF_SERVICE  8
#define GMM_SUSPEND_LLC_FOR_INTER_SYS       16
#define GMM_SUSPEND_LLC_FOR_DETACH          32

#define GMM_ABORT_LLC_TRUE                  0
#define GMM_ABORT_LLC_FALSE                 1

enum GMM_RA_PRIO_LEV_ENUM
{
    GMM_RA_PRIO_LEV_1                   = 1,
    GMM_RA_PRIO_LEV_2,
    GMM_RA_PRIO_LEV_3,
    GMM_RA_PRIO_LEV_4,
    GMM_RA_PRIO_LEV_BUTT
};
typedef VOS_UINT8 GMM_RA_PRIO_LEV_ENUM_U8;

/*===== 结构体定义 =====*/
typedef struct
{
    VOS_UINT32              ulReadyTimerValue;              /* READY TIMER协商值,以秒单位计 */
    VOS_UINT32              ulTLLI;                         /* 系统当前TLLI值 */
    VOS_UINT32              ulOldTLLI;                      /* 准备删除，无用的TLLI值 */

    GMM_CAS_STATE           ucGmmCasState;                  /* GMM CAS当前工作状态 */
    GMM_CAS_STATE           ucGmmCasPreState;               /* GMM CAS前个工作状态 */
    GMM_GPRS_SRV_STATE      GmmSrvState;                    /* 当前GMM GPRS服务状态 */
    VOS_UINT8               ucTlliAssignFlg;                /* GSM网络模式TLLI指配完成标志 */

    GMM_CAS_PARAM_TEMP_ST   TempMsgPara;                    /* 消息参数临时记录 */

    VOS_UINT8               ucBufMsgResFlg;                 /* 挂起消息恢复允许标志,1:允许;0:不允许 */
    VOS_UINT8               ucReadyTimerNgtFlg;             /* READY TIMER协商允许标志 */
    VOS_UINT8               ucRabmResumeFlg;                /* RABM从2G切换到3G恢复完成标志 */
    VOS_UINT8               ucRauCmpFlg;                    /* RAU过程完成后，是否需要等待RABM或WRR回复后，再发送RAU cmp消息
                                                                   RABM: ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP
                                                                   WRR : RRMM_INTER_RAT_HANDOVER_INFO_CNF     */

    VOS_UINT8               ucWaitRabmRauRspFlg;            /* 是否需要等待RABM: ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP 消息 */
    VOS_UINT8               ucRabmRauRspRcvdFlg;            /* 是否已收到RABM: ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP 消息 */
    GMM_RA_PRIO_LEV_ENUM_U8 enRaPrioLevFosSms;              /* 当前Radio priority for SMS值 */
    GMM_TLLI_TYPE           ucflgTLLI;                      /* 当前TLLI值类型标志 */

    VOS_UINT8               ucGprsCipherAlg;                /* GPRS加密算法 */
    VOS_UINT8               ucGprsCipher;                   /* VOS_TRUE:加密启动,VOS_FALSE:加密不启动。
                                                               指示在GSM模式下是否开始进行加密，在收到LL的LL_NAS_UNITDATA_IND消息时，
                                                               如果ucCiphInd指示加密，设置加密启动标志 */
    VOS_UINT8               ucGprsCipherAssign;             /* GPRS加密是否指配标志.VOS_TRUE:已经指配;VOS_FALSE:没有指配*/
    VOS_UINT8               ucCellNotifyFlg;                /* 2G网络下cell notification有效标志 */

    VOS_UINT8               ucFtsFlg;                       /* 2G网络下force to standby有效标志 */
    VOS_UINT8               ucCellUpdateFlg;                /* 2G网络下cell update执行标志 */
    VOS_UINT8               ucSysRauFlg;                    /* 系统信息要求RAU执行标志 */
    VOS_UINT8               ucLastDataSender;               /* 前次上行信令或数据传输发送方的网络接入模式 */

    VOS_UINT8               ucSuspendLlcCause;              /* 挂起LLC原因                                */
    VOS_UINT8               ucCellReselFlg;                 /* 指示当前是否在进行小区重选VOS_TRUE:在重选过程中;VOS_FALSE:不在重选过程       */
    VOS_UINT8               ucReadyTimerChgFlg;
    VOS_UINT8               aucReserve1[1];

    VOS_UINT16              usMui;
    VOS_UINT16              usPowerOffDetachPsMui;
}GMM_CAS_CTRL_STRU, *PGMM_CAS_CTRL_STRU;

/*----------7.1.3 GMM_LLC_MSG ------------*/
/* GMM和LLC的接口消息数据结构 */
/* V200R001版本新增 */

/*===== 结构体定义 =====*/
typedef struct
{
    VOS_MSG_HEADER                      /* VOS消息头*/
    VOS_UINT16  usMsgType;              /*消息类型*/
    VOS_UINT16  usTransId;              /*子进程，这里填SAPI*/
    VOS_UINT32  aulMsgData[1];          /*消息体结构头*/
}GMM_LLC_MSG;

/*=======================================================*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------7.2 挂起消息缓存队列     ---------------*/
/*=======================================================*/

/*----------7.2.1 GMM_CAS_CTRL_STRU ------------*/
/*
 GMM公用接入层控制数据结构
 1.GMM挂起状态下公用标志量记录
 2.GMM挂起状态下共享参数传递
*/
/* V200R001版本新增 */

/*===== 参数宏定义 =====*/
#define         GMM_CAS_MSG_NUMBER_MAX              10         /* 缓存消息数目最大值 */
/* 缓存消息处理标志 */
#define         GMM_MSG_BUFFER_FLAG_IDLE            0           /* 缓存消息为空 */
#define         GMM_MSG_BUFFER_FLAG_USED            1           /* 缓存消息已用 */

/*===== 结构体定义 =====*/
typedef struct
{
    VOS_VOID           *apBufMsg[GMM_CAS_MSG_NUMBER_MAX];       /* 缓存消息队列 */

    VOS_UINT8           ucBufMsgTotal;                          /* 缓存队列中消息个数 */
    VOS_UINT8           aucBufMsgFlg[GMM_CAS_MSG_NUMBER_MAX];   /* 缓存消息队列处理标志 */
} GMM_CAS_MSG_BUFFER_STRU, *PGMM_CAS_MSG_BUFFER_STRU;

#define GMM_AUTH_UMTS                   0
#define GMM_AUTH_GSM                    1
#define GMM_AUTH_GSM_AUTH_UNACCEPTABLE  2
#define GMM_AUTH_FAILURE                3

/*=======================================================*/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of GmmCasDef.h*/
