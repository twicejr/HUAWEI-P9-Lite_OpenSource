

#ifndef __TRRCERRLOGINTERFACE_H__
#define __TRRCERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "omerrorlog.h"
#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#include  "vos.h"
#include "omerrorlog.h"
#include "omringbuffer.h"
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/* TDS邻区的最大个数，上报最强3个临区 */
#define TRRC_APP_MAX_NCELL_NUM                     (3)
#define TRRC_OM_MAX_TDS_CELLS_NUM_WITHOUT_LTE_NCELL         (5)
/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : TRRC_ERRORLOG_ALARM_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : ERRORLOG ALARM_ID定义
*****************************************************************************/
enum TRRC_ERRORLOG_ALARM_ID_ENUM
{
    TRRC_ERRORLOG_ALARM_ID_EST_FAIL           =1,   /* 建连失败*/
    TRRC_ERRORLOG_ALARM_ID_RB_FAIL,                 /* RB配置失败 */
    TRRC_ERRORLOG_ALARM_ID_RBREC_FAIL,              /* RB重配置失败 */
    TRRC_ERRORLOG_ALARM_ID_CELLUPDATE_FAIL,         /* CELLUPDATE失败 */
    TRRC_ERRORLOG_ALARM_ID_AREA_LOST,               /* 丢网 */
    TRRC_ERRORLOG_ALARM_ID_INTEGRITY_FAIL,          /* 完整性验证失败*/
    TRRC_ERRORLOG_ALARM_ID_ASN_RSLT_FAIL,           /* asn解码错误 */
    TRRC_ERRORLOG_ALARM_ID_MEAS_CTRL_FAIL,          /* 测量配置错误 */
    TRRC_ERRORLOG_ALARM_ID_CS_HO_FAIL,              /* CS切换失败告警 */
    TRRC_ERRORLOG_ALARM_ID_CS_HO_EXP,               /* CS切换超时告警 */
    TRRC_ERRORLOG_ALARM_ID_RL_FAIL,                 /* 无线链路失败告警 */
    TRRC_ERRORLOG_ALARM_ID_BUFF_OVER_FLOW,          /* 缓冲溢出告警*/
    TRRC_ERRORLOG_ALARM_ID_NOT_TO_LTE,               /*长时间不回LTE告警*/
    TRRC_ERRORLOG_ALARM_ID_CS_SIGNAL_REL,               /*cs释放告警*/
    TRRC_ERRORLOG_ALARM_ID_CS_NO_RB_SETUP,                /*TRRC CS域打电话时，没有RB SETUP的情况*/
    TRRC_ERRORLOG_ALARM_ID_CS_T2G_CCO,                    /*TRRC CS域打电话时，发生了T到G的CCO流程*/
    TRRC_ERRORLOG_ALARM_ID_RSVD_MSG_MAX,                  /*TRRC在组装完RRC CONN SETUP COMPLETE后进入CNF态,此时收到多条
                                                            UM_DATA_IND致使缓存达到最大值走CONN TO IDLE流程*/
    TRRC_ERRORLOG_ALARM_ID_BUTT
};
typedef VOS_UINT16  TRRC_ERRORLOG_ALARM_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TRRC_ERRORLOG_ALARM_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 商用告警类型枚举定义
*****************************************************************************/
enum TRRC_ERRORLOG_ALARM_TYPE_ENUM
{
    TRRC_ERRORLOG_ALARM_TYPE_COMMUNICATION             = 1 ,      /* 表示通信: 产线确认从1开始，GUTL分别解码*/
    TRRC_ERRORLOG_ALARM_TYPE_TRANSACTION_QULITY            ,      /* 表示业务质量 */
    TRRC_ERRORLOG_ALARM_TYPE_PROCESS_ERROR                 ,      /* 表示处理出错 */
    TRRC_ERRORLOG_ALARM_TYPE_EQIPMENT_ERROR                ,      /* 表示设备故障 */
    TRRC_ERRORLOG_ALARM_TYPE_ENVIR_ERROR                   ,      /* 表示环境故障 */
    TRRC_ERRORLOG_ALARM_TYPE_BUTT
};
typedef VOS_UINT16  TRRC_ERRORLOG_ALARM_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : RRC_APP_ERROR_CODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRC错误码类型
*****************************************************************************/
enum TRRC_APP_ERROR_CODE_ENUM
{
    TRRC_APP_RB_PROTOCOL_CHECK_ERR            = 0,   /* RB配置失败--Protocol检查失败 */
    TRRC_APP_RB_TRANSACTION_CHECK_ERR,               /* RB配置失败--Transaction ID检查失败 */
    TRRC_APP_RB_INTEGRITY_CHECK_ERR,                 /* RB配置失败--Integrity检查失败 */

    TRRC_APP_RBREC_PROTOCOL_CHECK_ERR         = 10,  /* RB重配置失败--Protocol检查失败 */
    TRRC_APP_RBREC_TRANSACTION_CHECK_ERR,            /* RB重配置失败--Transaction ID检查失败 */
    TRRC_APP_RBREC_INTEGRITY_CHECK_ERR,              /* RB重配置失败--Integrity检查失败 */

    TRRC_APP_CELLUPDATECNF_PROTOCOL_CHECK_ERR     =20,  /* 小区更新失败--Protocol检查失败 */
    TRRC_APP_CELLUPDATECNF_TRANSACTION_CHECK_ERR,       /* 小区更新失败--Transaction ID检查失败 */
    TRRC_APP_CELLUPDATECNF_INTEGRITY_CHECK_ERR,         /* 小区更新失败--Integrity检查失败 */

    TRRC_APP_EST_T300_ERR                         =30,  /* 次数超过N300时记录 */
    TRRC_APP_EST_CS_ACC_PROBABILITY_ERR,                /* CS域建链AC等级判断失败 */
    TRRC_APP_EST_PS_ACC_PROBABILITY_ERR,                /* PS域建链AC等级判断失败 */

    TRRC_APP_EST_AREA_LOST_ERR                    =40,  /* RRC丢网 */
    TRRC_APP_ASN_RLST_ERR,                              /* ASN解析出错 */
    TRRC_APP_AM_INTEGRITY_CHECK_ERR,                    /* AM数据完整性检查失败 */
    TRRC_APP_UM_INTEGRITY_CHECK_ERR,                    /* UM数据完整性检查失败 */

    TRRC_APP_MEAS_CTRL_PROTOCOL_CHECK_ERR         =50,  /* 测量控制失败--Protocol检查失败 */
    TRRC_APP_MEAS_CTRL_TRANSACTION_CHECK_ERR,           /* 测量控制失败--Transaction ID检查失败 */

    TRRC_APP_HO_FAIL_ERR                          =60,  /* 切换失败 */
    TRRC_APP_HO_TIMER_EXP_ERR,                          /* 切换超时 */

    TRRC_APP_RL_FAIL_ERR                          =70,  /* 无线链路失败 */

    TRRC_APP_CS_SIGINAL_REL                       =80,  /* cs域链路释放 */
    TRRC_APP_CS_NORB_OUTOFSYNC                    = 90, /*TRRC CS域打电话时，由于没有收到RB SETUP，导致后来UE发生了失步流程*/
    TRRC_APP_CS_OUTOFSYNC_NORB                    = 91, /*TRRC CS域打电话时，由于UE先发生了失步流程，导致没有收到网侧下发的RB SETUP*/
    TRRC_APP_CS_NORB_RRCCONNREL                   = 92, /*TRRC CS域打电话时，UE在一段时间内 没有收到RB SETUP，然后网侧下发了RRC CONN REL*/
    TRRC_APP_CS_NORB_SIGNALCONNREL                = 93, /*TRRC CS域打电话时，UE在一段时间内 没有收到RB SETUP，然后网侧下发了SIGNAL CONN REL*/
    TRRC_APP_CS_NORB_GURELREQ                     = 94, /*TRRC CS域打电话时，UE在一段时间内 没有收到RB SETUP，然后GU 下发了REL REQ*/
    TRRC_APP_CS_NORB_GUTRANSNTFY                  = 95, /*TRRC CS域打电话时，UE在一段时间内 没有收到RB SETUP，然后GU 下发了TRANS STATUS NOTIFY，并且携带的原因值为TRANS_FAIL*/
    TRRC_APP_CS_NORB_OTHER                        = 96, /*TRRC CS域打电话时，UE在一段时间内 没有收到RB SETUP，其他的ERR CODE 原因值*/
    TRRC_APP_CS_T2G_CCO                           = 97, /*TRRC CS域打电话时，发生了T到G的CCO流程*/
    TRRC_APP_RRC_CONNSETUP_RSVD_MSG_MAX           = 98, /*TRRC在组装完RRC CONN SETUP COMPLETE后进入CNF态,此时收到多条
                                                          UM_DATA_IND致使缓存达到最大值走CONN TO IDLE流程*/

    TRRC_APP_ERR_CODE_BUTT
};
typedef VOS_UINT8 TRRC_APP_ERROR_CODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TRRC_APP_FTM_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 工程模式上报类型，分周期型上报、更新后上报型
*****************************************************************************/
enum TRRC_APP_FTM_TYPE_ENUM
 {
    TRRC_APP_FTM_PERIOD_INFO,     /* 周期型上报的工程模式信息，目前Idle状态上报周期为DRX周期，Connected状态下周期为1秒 */
    TRRC_APP_FTM_CHANGE_INFO,     /* 更新后上报型的工程模式信息，变更上报分两种类型 */
    TRRC_APP_FTM_INFO_BUIT
 };
 typedef VOS_UINT32 TRRC_APP_FTM_TYPE_ENUM_UINT32;

 /*********************************************************
 枚举名    : TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 变更上报工程模式类型定义
**********************************************************/
 enum TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 {
     TRRC_APP_FTM_CHANGE_CELL_INFO,      /* RRC驻留小区信息，变化后上报，切换或重选完成后上报 */
     TRRC_APP_FTM_CHANGE_STATE_INFO,     /* RRC状态信息，变化后上报 */

     TRRC_APP_FTM_CHANGE_BUTT
 };
  typedef VOS_UINT32 TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32;

 /*****************************************************************************
  枚举名    : TRRC_APP_PROTOCOL_STATE_ENUM
  协议表格  :
  ASN.1描述 :
  枚举说明  : TRRC协议状态
 *****************************************************************************/
 enum TRRC_APP_PROTOCOL_STATE_ENUM
 {
     TRRC_APP_PROTOCOL_STATE_IDLE                           = 0,                /* IDLE态 */
     TRRC_APP_PROTOCOL_STATE_CELL_PCH                          ,                /* CELL_PCH态 */
     TRRC_APP_PROTOCOL_STATE_URA_PCH                           ,                /* URA_PCH态 */
     TRRC_APP_PROTOCOL_STATE_CELL_FACH                         ,                /* CELL_FACH态 */
     TRRC_APP_PROTOCOL_STATE_CELL_DCH                          ,                /* CELL_DCH态 */

     TRRC_APP_PROTOCOL_STATE_BUTT
 };
 typedef VOS_UINT8 TRRC_APP_PROTOCOL_STATE_ENUM_UINT8;

 /*****************************************************************************
  枚举名     :TRRC_APP_GRR_BANDINDICATOR_ENUM
  协议表格  :
  ASN.1描述   :
  枚举说明 : 2G小区频带指示
 *****************************************************************************/
 enum TRRC_APP_GRR_BANDINDICATOR_ENUM
 {
     TRRC_APP_GRR_BANDINDICATOR_DCS1800       = 0,
     TRRC_APP_GRR_BANDINDICATOR_PCS1900       ,

     TRRC_APP_GRR_BANDINDICATOR_BUTT
 };
 typedef VOS_UINT16    TRRC_APP_GRR_BANDINDICATOR_ENUM_UINT16;

  /*****************************************************************************
  枚举名     :TRRC_APP_RRC_STATE_ENUM
  协议表格  :
  ASN.1描述   :
  枚举说明 : RRC状态，内部状态，非协议状态
 *****************************************************************************/
 enum TRRC_APP_RRC_STATE_ENUM
 {
    TRRC_APP_NUL,   // 0x00  /* TTRRC_APP_CHANGE FOR 注释: 开机前，和丢失覆盖*/
    TRRC_APP_SEL,   // 0x01
    TRRC_APP_IDL,   // 0x02
    TRRC_APP_RES,   // 0x03
    TRRC_APP_ACC,   // 0x04
    TRRC_APP_FCH,   // 0x05
    TRRC_APP_DCH,   // 0x06
    TRRC_APP_PCH,   // 0x07
    TRRC_APP_WCA,   // 0x08
    TRRC_APP_REL,   // 0x09
    TRRC_APP_CNF,   // 0x0A
    TRRC_APP_LIM,   // 0x0b
    TRRC_APP_SNW,   // 0x0c
    TRRC_APP_INACTIVE,//0x0d PDM100 200909 for dual mode
    TRRC_APP_PREDEF,  //PDM100 200909 for SIB16
    TRRC_APP_PEND,    //PDM100 200909 for inter-RAT res and CCO
    TRRC_APP_RATHO,   //PDM100 200909 for inter-RAT HO
    TRRC_APP_WAIT,
    TRRC_APP_POWEROFF
 };
typedef VOS_UINT8 TRRC_APP_RRC_STATE_ENUM_UINT8;
/*****************************************************************************
 枚举名    : TRRC_FLOW_CTRL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 流程控制类型枚举
             修改枚举时需要注意，失败类型取值 = 启动类型取值+1
 比如: LRRC_FLOW_CTRL_TYPE_G2L_RESEL_FAIL = LRRC_FLOW_CTRL_TYPE_G2L_START_RESEL + 1
*****************************************************************************/
enum TRRC_APP_FLOW_CTRL_TYPE_ENUM
{
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL            = 0,     /* TDS内流程边界 */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_IDL_SYS_UPDATA,     /* TDS内流程IDL态系统消息更新测量重配流程 */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_PCH_SYS_UPDATA,     /* TDS内流程PCH态系统消息更新测量重配流程 */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_PCH,          /* TDS内流程从其他状态，DCH/FACH->PCH态转换流程 */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_FCH,          /* TDS内流程从其他状态，IDL->FCH态转换流程 */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_DCH,          /* TDS内流程从其他状态，IDL->DCH态转换流程 */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_RES_ENTER_FCH,             /* TDS内流程重选后进入FCH状态流程 */
    /* TL RESEL PHASE2 begin */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NAS_SUSPEND,               /* TDS内流程NAS挂起流程 */
    /* TL RESEL PHASE2 end */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_END,                /* TDS内流程边界 */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_RESEL,               /* G->T开始重选 */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_RESEL_FAIL,                /* G->T重选失败 */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_RESEL,                /* G->T停止重选 */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_RESEL,               /* T->G开始重选 */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_RESEL_FAIL,                /* T->G重选失败 */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_MEAS,                      /* G->T 测量配置 */
    /* TL RESEL BEGIN */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_START_RESEL,               /* L->T开始重选 */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_RESEL_FAIL,                /* L->T重选失败 */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_RESEL,                /* L->T停止重选 */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_IDLE_MEAS,                 /* L->T IDLE测量配置 */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_CONN_MEAS,                 /* L->T CONN测量配置 */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_RELALL,                    /* L->T RELALL */

    TRRC_APP_FLOW_CTRL_TYPE_T2L_START_RESEL,               /* T->L开始重选 */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_RESEL_FAIL,                /* T->L重选失败 */

	/* TOER_HO BEGIN */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_CCO,                 /* G->T开始CCO */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_CCO_FAIL,                  /* G->T CCO失败 */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_CCO,                  /* G->T停止CCO */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_CCO,                 /* T->G开始CCO */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_CCO_FAIL,                  /* T->G CCO失败 */

    TRRC_APP_FLOW_CTRL_TYPE_T2L_START_HO,                  /* T->L开始切换 */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_HO_FAIL,                   /* T->L切换失败 */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_START_HO,                  /* L->T开始HO */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_HO_FAIL,                   /* L->T HO失败 */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_HO,                   /* L->T停止HO */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_HO,                  /* T->G开始切换 */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_HO_FAIL,                   /* T->G切换失败 */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_HO,                  /* G->T开始HO */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_HO_FAIL,                   /* G->T HO失败 */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_HO,                   /* G->T停止HO */
    /* TOER_HO END */

    TRRC_APP_FLOW_CTRL_TYPE_T2T_SYSCFG_SUSPEND,            /* TDS内流程自我挂起流程 */
    /* TL RESEL end */
    /* TL Redir begin */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_REDIR,                     /* T->L重定向 */
    /* TL Redir end */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_REDIR_FAIL,                /* L->W重定向失败 */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_REDIR,                /* L->T重定向停止 */

    /*准FR特性begin*/
    TRRC_APP_FLOW_CTRL_TYPE_T2G_REDIR,                     /* T->G重定向 */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_REDIR_FAIL,                /* G->T重定向失败 */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_REDIR,                /* G->T重定向停止 */
    /*准FR特性end*/

    TRRC_APP_FLOW_CTRL_TYPE_BUTT
};
typedef VOS_UINT16 TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16;
/*****************************************************************************
 枚举名    : TRRC_APP_EST_SIGNALLING_TYPE
 协议表格  :
 ASN.1描述 :
 枚举说明  : 链路类型
*****************************************************************************/

enum  TRRC_APP_EST_SIGNALLING_TYPE
{
  TRRC_APP_NO_SIGNALLING_CONNECTION = 0,
  TRRC_APP_SIGNALLING_CONNECTION_ESTABLISHING,
  TRRC_APP_SIGNALLING_CONNECTION_ESTABLISHED
};

typedef VOS_UINT32 TRRC_APP_EST_SIGNALLING_TYPE_UINT32;
/*****************************************************************************
 枚举名    : TRRC_APP_EST_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRMM_EST_REQ_STRU消息中的enEstCause，与25.331协议定义保持一致
*****************************************************************************/
enum TRRC_APP_EST_CAUSE_ENUM
{
    TRRC_APP_EST_CAUSE_ORIGIN_CONVERSAT_CALL             = 0,
    TRRC_APP_EST_CAUSE_ORIGIN_STREAM_CALL                = 1,
    TRRC_APP_EST_CAUSE_ORIGIN_INTERACT_CALL              = 2,
    TRRC_APP_EST_CAUSE_ORIGIN_BACKGROUND_CALL            = 3,
    TRRC_APP_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL      = 4,
    TRRC_APP_EST_CAUSE_TERMINAT_CONVERSAT_CALL           = 5,
    TRRC_APP_EST_CAUSE_TERMINAT_STREAM_CALL              = 6,
    TRRC_APP_EST_CAUSE_TERMINAT_INTERACT_CALL            = 7,
    TRRC_APP_EST_CAUSE_TERMINAT_BACKGROUND_CALL          = 8,
    TRRC_APP_EST_CAUSE_EMERGENCY_CALL                    = 9,
    TRRC_APP_EST_CAUSE_INTER_RAT_CELL_RESELECT           = 10,
    TRRC_APP_EST_CAUSE_INTER_RAT_CELL_CHANGE_ORDER       = 11,
    TRRC_APP_EST_CAUSE_REGISTRATION                      = 12,
    TRRC_APP_EST_CAUSE_DETACH                            = 13,
    TRRC_APP_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL       = 14,
    TRRC_APP_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL        = 15,
    TRRC_APP_EST_CAUSE_CALL_RE_ESTABLISH                 = 16,
    TRRC_APP_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL     = 17,
    TRRC_APP_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL      = 18,
    TRRC_APP_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN            = 19,
    TRRC_APP_EST_CAUSE_BUTT
};
typedef VOS_UINT32 TRRC_APP_EST_CAUSE_ENUM_UINT32;

/* ErrorLog新增丢网信息begin */
/*****************************************************************************
 枚举名    : TDS_APP_FREQ_BAND_LIST_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TDS band信息枚举值
*****************************************************************************/
enum TDS_APP_FREQ_BAND_LIST_ENUM
{
    TDS_APP_FREQ_BAND_NONE      = 0x00,
    TDS_APP_FREQ_BAND_A         = 0x01,         /* 频点范围: 9504~9596  10054~10121 */
    TDS_APP_FREQ_BAND_B         = 0x02,         /* 频点范围: 9254~9546  9654~9946 */
    TDS_APP_FREQ_BAND_C         = 0x04,         /* 频点范围: 9554~9646 */
    TDS_APP_FREQ_BAND_D         = 0x08,         /* 频点范围: 12854~13096 */
    TDS_APP_FREQ_BAND_E         = 0x10,         /* 频点范围: 11504~11996 */
    TDS_APP_FREQ_BAND_F         = 0x20,         /* 频点范围: 9404~9596 */
    TDS_APP_FREQ_BAND_BUTT
};
typedef VOS_UINT8  TDS_APP_FREQ_BAND_LIST_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TDS_APP_ERR_LOG_RAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接入技术枚举值，根据检视意见GUTL各自定义但保持各制式顺序一致
*****************************************************************************/
enum TDS_APP_ERR_LOG_RAT_TYPE_ENUM
{
    TDS_APP_ERR_LOG_RAT_TYPE_GSM      = 1,      /* GSM 接入技术*/
    TDS_APP_ERR_LOG_RAT_TYPE_WCDMA,             /* WCDMA 接入技术*/
    TDS_APP_ERR_LOG_RAT_TYPE_LTE,               /* LTE 接入技术*/
    TDS_APP_ERR_LOG_RAT_TYPE_TDS,               /* TDS 接入技术*/
    TDS_APP_ERR_LOG_RAT_TYPE_BUTT
};
typedef VOS_UINT8  TDS_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 丢网上报原因值
*****************************************************************************/
enum TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM
{
    TDS_APP_ERR_LOG_AREA_LOST_BUTT = 1         /* 当前预留该枚举值*/
};
typedef VOS_UINT8  TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM_UINT8;
/* ErrorLog新增丢网信息end */
/* Seattle Begin */
/*****************************************************************************
 枚举名    : TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 切换失败的原因值
*****************************************************************************/
enum TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM
{
    ERR_TRRC_GRR_HANDOVER_RESULT_FREQ_NOT_IMPLEMENTED =1,
    ERR_TRRC_GRR_HANDOVER_RESULT_CONFIG_UNKNOW,
    ERR_TRRC_GRR_HANDOVER_RESULT_INVALID_CONFIG,
    ERR_TRRC_GRR_HANDOVER_RESULT_RRC_CONNECT_FAILURE,
    ERR_TRRC_GRR_HANDOVER_RESULT_PROTOCOL_ERROR,
    ERR_TRRC_GRR_HANDOVER_RESULT_UNSUPORTED_CONFIGURATION,
    ERR_TRRC_GRR_HANDOVER_RESULT_PHY_CHANNEL_FAIL,
    ERR_TRRC_GRR_HANDOVER_RESULT_MESSAGE_INVALID,
    ERR_TRRC_GRR_HANDOVER_RESULT_UNSPECIFIC,
    ERR_TRRC_GRR_HANDOVER_RESULT_BUTT
};
typedef VOS_UINT16 TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TDS_ERR_LOG_CS_LINK_ERROR_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 无线链路失败的原因值
*****************************************************************************/
enum TDS_ERR_LOG_CS_LINK_ERROR_ENUM
{
    TDS_CS_LINK_ERROR_T312_TIMEOUT =0,
    TDS_CS_LINK_ERROR_T313_TIMEOUT,
    TDS_CS_LINK_ERROR_BUTT
};
typedef VOS_UINT16 TDS_ERR_LOG_CS_LINK_ERROR_ENUM_UINT16;

/*****************************************************************************
 枚举名     :ERR_LOG_GSM_BAND_INDICATOR_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : GSM小区频段指示枚举
*****************************************************************************/
typedef enum
{
    ERR_LOG_EN_DSC_1800_USED                    = 0,
    ERR_LOG_EN_PDS_1900_USED
}ERR_LOG_GSM_BAND_INDICATOR_ENUM;
typedef VOS_UINT32  ERR_LOG_GSM_BAND_INDICATOR_ENUM_UINT32;

/* Seattle End */
/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
                               工程模式 上报数据结构
*****************************************************************************/

/*****************************************************************************
 结构名    : TRRC_APP_CHANGE_CELL_INFO_STRU
 结构说明  : 变化上报的工程模式结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                usUlFreq;          /* 上行中心频点单位:100Khz */
    VOS_UINT16                                usDlFreq;          /* 下行中心频点单位:100Khz */
    VOS_UINT32                                ulCellId;          /* TD-SCDMA小区ID，指RRC层的小区ID，不是物理层的 */
    VOS_UINT16                                usPagingCycle;     /* 寻呼周期128,256,512,1024，单位ms*/
    VOS_UINT16                                usReserved;
}TRRC_APP_CHANGE_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_TDS_NCELL_INFO_STRU
 结构说明  : TD-SCDMA同频、异频小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usFrequency;      /* TD-SCDMA临小区下行中心频点 单位:100Khz */
    VOS_UINT16                         usCellId;         /* TD-SCDMA临小区小区ID */
    VOS_UINT8                          ucRscp;           /* TD-SCDMA临小区Rscp接收功率，真实值=ucRscp - 116；单位dbm */
    VOS_UINT8                          aucReserved[3];
}TRRC_APP_TDS_NCELL_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_TDS_NCELL_STRU
 结构说明  : TD-SCDMA同频、异频小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulNCellNumber;
    TRRC_APP_TDS_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_TDS_NCELL_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_LTE_NCELL_INFO_STRU
 结构说明  : TD-SCDMA异系统LTE小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usCellId;   /* 物理小区ID */
    VOS_INT16                           sRsrp;      /* 测量结果RSRP */
    VOS_INT16                           sRsrq;      /* 测量结果RSRQ */
}TRRC_APP_LTE_NCELL_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_LTE_NCELL_STRU
 结构说明  : TD-SCDMA异系统LTE小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulNCellNumber;
    TRRC_APP_LTE_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_LTE_NCELL_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_GERAN_NCELL_INFO_STRU
 结构说明  : TD-SCDMA异系统GSM小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    TRRC_APP_GRR_BANDINDICATOR_ENUM_UINT16                  enBandInd;          /* 保持T->G时测量请求消息中的频段指示一致 */
    VOS_INT16                                               sRssi;              /* sRssi 取值范围[-110 * 8,-48 * 8],单位:dbm,精度1/8 */
    VOS_UINT8                                               ucNcc;              /*  移动通讯GSM网络识别参数: 网络色码(NCC) */
    VOS_UINT8                                               ucBcc;              /*  移动通讯GSM网络识别参数: 基站色码(BCC) */
}TRRC_APP_GERAN_NCELL_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_GERAN_NCELL_STRU
 结构说明  : TD-SCDMA异系统GSM小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulNCellNumber;
    TRRC_APP_GERAN_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_GERAN_NCELL_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_NCELL_INFO_STRU
 结构说明  : 服务小区的同频、异频以及异系统测量结果
*****************************************************************************/
typedef struct
{
    TRRC_APP_TDS_NCELL_STRU               stIntraFreqInfo;/* 同频邻区信息*/
    TRRC_APP_TDS_NCELL_STRU               stInterFreqInfo;/* 异频邻区信息*/
    TRRC_APP_LTE_NCELL_STRU               stLTENcellInfo; /* LTE异系统邻区*/
    TRRC_APP_GERAN_NCELL_STRU             stGeranNcellInfo; /* GERAN异系统邻区 */
}TRRC_APP_NCELL_INFO_STRU;

/****************************************************************************
 结构名    : TRRC_APP_FTM_CHANGE_INFO_STRU
 结构说明  : 变化上报的工程模式结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32     ulFtmChangeInfoType;

    union
    {
        TRRC_APP_CHANGE_CELL_INFO_STRU            stCellInfo;
        TRRC_APP_PROTOCOL_STATE_ENUM_UINT8        enTrrcProtocolState;
    }uchangeInfo;
}TRRC_APP_FTM_CHANGE_INFO_STRU;
/*****************************************************************************
 结构名    : APP_RRC_SINR_INFO_STRU
 结构说明  : SINR结构
*****************************************************************************/
typedef struct
{
	VOS_UINT16                                     usModuFormat;
	VOS_UINT16                                     usTbiOut;
}TRRC_APP_CQI_INFO_STRU;
/*****************************************************************************
 结构名    : APP_RRC_SINR_INFO_STRU
 结构说明  : SINR结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                              sSinrDB;
    VOS_UINT16                             usRev;
}TRRC_APP_DPCH_SINR_INFO_STRU;
/*****************************************************************************
 结构名    : TDS_ERRLOG_UL_POWER_STRU
 结构说明  : UE上行发射功率
*****************************************************************************/
typedef struct
{
	VOS_INT16 sDpchPwr;
	VOS_INT16 sEpuchPwr;
}TDS_APP_ERRLOG_UL_POWER_STRU;
/*****************************************************************************
 结构名    : RRC_APP_FTM_PERIOD_INFO
 结构说明  : 周期上报的工程模式结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sCellRSCP;
    VOS_UINT16                          usReserved;
    TDS_APP_ERRLOG_UL_POWER_STRU        stUeTxPower;
    TRRC_APP_DPCH_SINR_INFO_STRU        stSINR;             /* SINR  RS_SNR */
    TRRC_APP_CQI_INFO_STRU              stCQI;              /* CQI两个码字 */
    TRRC_APP_NCELL_INFO_STRU            stNcellInfo;        /*邻区信息*/
}TRRC_APP_FTM_PERIOD_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_APP_FTM_INFO_STRU
 结构说明  : 工程模式上报数据结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_FTM_TYPE_ENUM_UINT32             enRrcAppFtmType;

    union
    {
        TRRC_APP_FTM_PERIOD_INFO_STRU         stPeriodInfo;  /* 工程模式下，周期上报内容， Idle状态上报周期目前为DRX周期，Connected状态下周期为1秒 */
        TRRC_APP_FTM_CHANGE_INFO_STRU         stChangInfo;   /* 工程模式下，变更后上报内容 */
    }u;
}TRRC_APP_FTM_INFO_STRU;
/*****************************************************************************
 结构名    : TRRC_OM_FTM_REPROT_CONTENT_STRU
 结构说明  : 工程模式上报数据结构
*****************************************************************************/
typedef struct
{
    /* 子模块ID */
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    ulMsgModuleID;

    /* 00：主卡, 01：副卡 ,10/11:保留  */
    VOS_UINT16                          usModemId;

    VOS_UINT16                          usProjectID;
    VOS_UINT32                          ulLength;

    TRRC_APP_FTM_INFO_STRU               stTrrcFtmInfo;

}TRRC_OM_FTM_REPROT_CONTENT_STRU;

/*****************************************************************************
 结构名    : TRRC_OM_FTM_REPROT_IND_STRU
 结构说明  : 工程模式上报数据结构
*****************************************************************************/
/* 各组件工程模式主动上报内容 各组件 -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 工程模式上报的内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    TRRC_OM_FTM_REPROT_CONTENT_STRU     stTrrcFtmContent;
}TRRC_OM_FTM_REPROT_IND_STRU;

/* Seattle Begin */
/*****************************************************************************
 结构名     :ERR_LOG_SAVE_CELL_INFO_FOR_GAS_ST
 协议表格  :
 ASN.1描述   :
 结构说明  :GSM小区的信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNCC;
    VOS_UINT32                          ulBCC;
    VOS_UINT32                          ulBcchArcfn;
    VOS_UINT32                          ulFreqBandInd;
    VOS_UINT32                          ulFlag;                                 /* 该标记用于指示lFNOffset、ulTimeAlignmt是否有数据，0:表示无数据 1: 表示有数据*/
    VOS_INT32                           lFNOffset;
    VOS_UINT32                          ulTimeAlignmt;
    VOS_INT16                           sRxlev;                                 /* G小区信号电平，单位是dBm,没有测到信号电平时赋值为RRWRR_INVALID_RXLEV */
    VOS_UINT8                           aucReserve1[2];                         /* 4字节对齐，保留 */

}ERR_LOG_SAVE_CELL_INFO_FOR_GAS_ST;

/*****************************************************************************
 结构名     :TDS_ERR_LOG_CELL_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucCellId;                   /*小区ID*/
    VOS_UINT8                                   ucRscp;                     /*能量*/
    VOS_UINT16                                  usFreqId;                   /*工作频点*/
} TDS_ERR_LOG_CELL_INFO_STRU;

/*****************************************************************************
 结构名     :TDS_ERR_LOG_GSM_CELL_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :
*****************************************************************************/
typedef struct
{
    ERR_LOG_SAVE_CELL_INFO_FOR_GAS_ST           stRrcSaveInfoForGas;        /* 注意，只有1个小区的信息，与切换接口不同s */
    ERR_LOG_GSM_BAND_INDICATOR_ENUM_UINT32      enBandIndictor;             /* Band指示 */
} TDS_ERR_LOG_GSM_CELL_INFO_STRU;

/*****************************************************************************
 结构名     :TDS_ERR_LOG_EVT_CS_HANDOVER_FAIL_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :
*****************************************************************************/
typedef struct
{
    TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM_UINT16    enHandoverFailCause;  /* 切换失败原因值*/
    VOS_UINT8                                   aucReserve[2];        /* 保留位 */
    TDS_ERR_LOG_CELL_INFO_STRU                  stTdsOrginalCell;     /* 切换的TDS源小区信息 */
    TDS_ERR_LOG_GSM_CELL_INFO_STRU              stGsmTargetCell;      /* 切换的GSM目标小区信息*/
}TDS_ERR_LOG_EVT_CS_HANDOVER_FAIL_STRU;

/*****************************************************************************
 结构名     :TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :
*****************************************************************************/
typedef struct
{
    TDS_ERR_LOG_CELL_INFO_STRU                  stTdsOrginalCell;     /* 切换的TDS源小区信息 */
    TDS_ERR_LOG_GSM_CELL_INFO_STRU              stGsmTargetCell;      /* 切换的GSM 目标小区信息*/
    VOS_UINT32                                  ulHandoverTime;       /* 切换时长*/
}TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU;

/*****************************************************************************
 结构名     :TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulStatus;           /*当前状态*/
    TDS_ERR_LOG_CELL_INFO_STRU                  stTdsOrginalCell;   /* 切换的TDS源小区信息 */
} TDS_ERR_LOG_STATUS_INFO_STRU;

/*****************************************************************************
 结构名     :TDS_ERR_LOG_EVT_CS_LINK_ERROR_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :
*****************************************************************************/
typedef struct
{
    TDS_ERR_LOG_CS_LINK_ERROR_ENUM_UINT16       enRadioLinkErrorCause;      /*无线链路异常原因*/
    VOS_UINT8                                   aucReserve[2];              /* 保留位 */
    TDS_ERR_LOG_STATUS_INFO_STRU                stTdsStatusInfo;            /* TDS 当前状态信息记录*/
}TDS_ERR_LOG_EVT_CS_LINK_ERROR_STRU;
/* Seattle End */

/*****************************************************************************
                               ERROR LOG 上报数据结构
*****************************************************************************/

/*****************************************************************************
 结构名    : RRC_APP_STATE_INFO_STRU
 结构说明  : ERROR LOG RRC状态信息，包括协议状态，内部状态，异系统过程
*****************************************************************************/
typedef struct
{
    TRRC_APP_PROTOCOL_STATE_ENUM_UINT8          enTrrcProtocolState;   /* RRC协议状态 */
    TRRC_APP_RRC_STATE_ENUM_UINT8               enRrcState;            /* RRC状态，内部状态，非协议状态 */
    TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16         enErrcFlowCtrlType;    /* TD-SCDMA发生异系统过程时，异系统过程标识 */
}TRRC_APP_STATE_INFO_STRU;
/*随机接入建连失败CHR上报 add by lilin 00297133 2015-9-16 begin******************/
/*****************************************************************************
 结构名    : TRRC_APP_ACC_FAIL_INFO_STRU
 结构说明  : ERROR LOG RRC建连失败上报信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulMcc;           /* MCC,3 bytes      */
    VOS_UINT32                                 ulMnc;           /* MNC,2 or 3 bytes */
    VOS_UINT16                                 usFrequency;     /* 随机接入失败时服务小区中心频点 单位:100Khz */
    VOS_UINT16                                 usCellId;        /* 随机接入失败时服务小区ID信息 */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8          enBandInfo;      /* 随机接入失败时服务小区所属band信息 */
    VOS_INT8                                   ucRscp;          /* 随机接入失败时服务小区测量值,实际值 - 116；单位dbm */
    VOS_INT8                                   ucQrxLevMin;     /* 随机接入失败时服务小区驻留门限*/
    VOS_UINT8                                  ucRac;           /* Rac */
    VOS_UINT16                                 usLac;           /* lac */
    VOS_UINT8                                  aucResv[2];      /*保留位*/

}TRRC_APP_ACC_FAIL_INFO_STRU;
/*随机接入建连失败CHR上报 add by lilin 00297133 2015-9-16 end******************/
/*****************************************************************************
 结构名    : TRRC_APP_EST_INFO_STRU
 结构说明  : ERROR LOG RRC建连信息
 enEstSignallingType[0]:CS;enEstSignallingType[1]:ps
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头 */
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];              /* 保留位 */
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32        enEstSignallingType[2];  /* 域建连状态信息*/
    TRRC_APP_EST_CAUSE_ENUM_UINT32             enEstCause;              /* 建连原因 */
    /*随机接入建连失败CHR上报 add by lilin 2015-9-16 begin*/
    TRRC_APP_ACC_FAIL_INFO_STRU                stRrcAppAccFailInfo;              
    /*随机接入建连失败CHR上报 add by lilin 2015-9-16 end*/
}TRRC_APP_EST_INFO_STRU;

/* ErrorLog新增丢网信息begin */

/*****************************************************************************
 结构名    : TDS_APP_AREA_LOST_INFO_STRU
 结构说明  : TDS丢网定位信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulTimeStamp;     /* 记录丢网的时刻 */
    VOS_UINT32                                 ulMcc;           /* MCC,3 bytes      */
    VOS_UINT32                                 ulMnc;           /* MNC,2 or 3 bytes */
    VOS_UINT16                                 usFrequency;     /* 丢网时服务小区中心频点 单位:100Khz */
    VOS_UINT16                                 usCellId;        /* 丢网时服务小区ID信息 */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8          enBandInfo;      /* 丢网时服务小区所属band信息 */
    VOS_INT8                                   ucRscp;          /* 丢网前服务小区测量值,实际值 - 116；单位dbm */
    VOS_INT8                                   ucQrxLevMin;     /* 丢网时服务小区驻留门限*/
    VOS_UINT8                                  ucRac;           /* Rac */
    VOS_UINT16                                 usLac;           /* lac */
    TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM_UINT8 ucSubCause;      /* 记录丢网原因值:暂时保留待后续扩展使用 */
    VOS_UINT8                                  ucResv;          /* 保留 */
}TDS_APP_AREA_LOST_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_AREA_LOST_INFO_STRU
 结构说明  : TDS丢网定位信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    TDS_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8        enRatType;               /* 丢网发生的网络制式 */
    VOS_UINT8                                  aucResv[2];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */
    TDS_APP_AREA_LOST_INFO_STRU                stTdsArealostInfo;       /* 丢网信息结构 */
}TRRC_APP_AREA_LOST_INFO_STRU;

/* ErrorLog新增丢网信息end */
/*****************************************************************************
 结构名    : TRRC_APP_CS_HO_FAIL_ERROR_INFO_STRU
 结构说明  : TDS CS切换失败
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8                  enErrorCode;             /* 错误码*/
    VOS_UINT8                                       aucResv[3];
    TRRC_APP_STATE_INFO_STRU                        stRrcAppStateInfo;       /* 发生故障时状态信息 */
    TDS_ERR_LOG_EVT_CS_HANDOVER_FAIL_STRU           stTdsHoFailInfo;         /* 切换失败*/
}TRRC_APP_CS_HO_FAIL_ERROR_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_CS_HO_EXP_ERROR_INFO_STRU
 结构说明  : TDS CS切换超时
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8                  enErrorCode;             /* 错误码*/
    VOS_UINT8                                       aucResv[3];
    TRRC_APP_STATE_INFO_STRU                        stRrcAppStateInfo;       /* 发生故障时状态信息 */
    TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU           stTdsHoTimeExpInfo;      /* CS切换超时*/
}TRRC_APP_CS_HO_EXP_ERROR_INFO_STRU;


/*****************************************************************************
 结构名    : TRRC_APP_RL_ERROR_INFO_STRU
 结构说明  : TDS无线链路失败信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */
    TDS_ERR_LOG_EVT_CS_LINK_ERROR_STRU         stTdsRLErrorInfo;        /* 无线链路失败信息结构 */
}TRRC_APP_RL_ERROR_INFO_STRU;
/* Seattle End */

/*****************************************************************************
 结构名    : TRRC_APP_RB_ERROR_INFO_STRU
 结构说明  : TDS RB配置错误信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */

}TRRC_APP_RB_ERROR_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_RBREC_ERROR_INFO_STRU
 结构说明  : TDS RB重配置错误信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */

}TRRC_APP_RBREC_ERROR_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_CELLUPDATE_ERROR_INFO_STRU
 结构说明  : TDS cellupdateconfirm错误信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */
    /*随机接入建连失败CHR上报 add by lilin 2015-9-16 begin*/
    TRRC_APP_ACC_FAIL_INFO_STRU                stRrcAppAccFailInfo;              
    /*随机接入建连失败CHR上报 add by lilin 2015-9-16 end*/
}TRRC_APP_CELLUPDATE_ERROR_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_INTEGRITY_ERROR_INFO_STRU
 结构说明  : TDS INTEGRITY fail信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */

}TRRC_APP_INTEGRITY_ERROR_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_MEAS_CTRL_ERROR_INFO_STRU
 结构说明  : TDS MEAS_CTRL错误信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */

}TRRC_APP_MEAS_CTRL_ERROR_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_APP_ASN_RLST_ERR_INFO_STRU
 结构说明  : TDS ASN解码失败信息
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */

}TRRC_APP_ASN_RLST_ERR_INFO_STRU;
/*****************************************************************************
 结构名    : TRRC_APP_BUFF_OVER_FLOW_ERR_INFO_STRU
 结构说明  : 缓冲溢出
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头*/
    VOS_UINT32                                 ulCount;                 /* 溢出计数 */
}TRRC_APP_BUFF_OVER_FLOW_ERR_INFO_STRU;

/*****************************************************************************
 结构名    : OM_ERR_LOG_REPORT_CNF_STRU
 结构说明  : ERROR LOG 数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 故障内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    VOS_UINT8                           aucContent[4]; /* 故障内容 */
} TRRC_OM_ERR_LOG_REPORT_CNF_STRU;

/*****************************************************************************
 Structure      : TRRC_OM_TDS_SERV_CELL_INFO_STRU
 Description    : 当前注册的小区信息
 修改历史 :
  1.日    期    : 2015年2月27日
    作    者    : f00272207
    修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulMcc;           /* MCC,3 bytes      */
    VOS_UINT32                                 ulMnc;           /* MNC,2 or 3 bytes */
    VOS_UINT16                                 usFrequency;     /* 务小区中心频点 单位:100Khz */
    VOS_UINT16                                 usCellId;        /* 服务小区ID信息 */
    VOS_INT8                                   ucRscp;          /* 服务小区测量值,实际值 - 116；单位dbm */
    VOS_UINT8                                  ucRac;           /* Rac */
    VOS_UINT16                                 usLac;           /* lac */

}TRRC_OM_TDS_SERV_CELL_INFO_STRU;

/*****************************************************************************
 Structure      : TRRC_ OM_TDS_CELLS_LIST_WITHOUT_LTE_NCELL_STRU
 Description    : 未配置4G邻区的小区列表结构体
 修改历史 :
  1.日    期     : 2015年2月27日
    作    者    :  f00272207
    修改内容    :  新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucTdsCellNum;                   /* 未配置4G邻区的TDS小区个数 */
    VOS_UINT8                                   aucRsv[3];                      /* 四字节对齐的保留位 */
    TRRC_OM_TDS_SERV_CELL_INFO_STRU             astCellinfo[TRRC_OM_MAX_TDS_CELLS_NUM_WITHOUT_LTE_NCELL]; /* 未配置4G邻区的小区列表 */

} TRRC_OM_TDS_CELLS_LIST_WITHOUT_LTE_NCELL_STRU;


/*****************************************************************************
 Structure      : TRRC_ERR_LOG_EVT_NO_T2L_OPERATION_ONE_CYCLE_STRU
 Description    : TRRC长时间不回LTE事件上报的结构体
 修改历史 :
  1.日    期    : 2015年2月27日
    作    者    : f00272207
    修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;
    TDS_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8                 enRatType;                       /*长时间不回LTE所属的模式*/
    VOS_UINT8                                           ucLteMeasValidFlag;              /*是否测量到LTE信号标志*/
    VOS_INT16                                           sLteMaxRsrp;                     /*T3周期内测量到的最强的LTE信号强度 */
    TRRC_OM_TDS_CELLS_LIST_WITHOUT_LTE_NCELL_STRU       stTdsCellListWithoutLteNcell;    /*未配置LTE临区的小区列表*/
    TRRC_OM_TDS_SERV_CELL_INFO_STRU                     stServCellInfo;                  /*当前注册小区信息 */

} TRRC_ERR_LOG_EVT_NO_T2L_OPERATION_ONE_CYCLE_STRU;
/*****************************************************************************
 Structure      : TRRC_APP_CS_RELEASE_CELL_INFO_STRU
 Description    : TRR CS链路释放当前服务区信息
 修改历史 :
  1.日    期    : 2015年10月25日
    作    者    : f00272207
    修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                 usCellId;                /* 服务小区ID */
    VOS_UINT16                                 usFrequency;             /* 工作频点 */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8          enBandInfo;              /* 工作频点所属BAND信息 */
    VOS_INT8                                   ucRscp;                  /* 服务小区能量 */
    VOS_UINT8                                  aucResv[2];
}TRRC_APP_CS_RELEASE_CELL_INFO_STRU;

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
Structure      : TRRC_APP_CS_NO_RBSETUP_INFO_STRU
Description    : 问题单DTS2015120803646:TRRC 在组装完RRC CONN SETUP COMPLETE后,TRRC 进入内部状态机RRC_CNF态,
                 此时收到多条UM_DATA_IND进行缓存,最后缓存达到最大值,TRRC流程走CONN TO IDLE。此CHR TRRC给CHR上报的内容。
修改历史 :
 1.日    期    : 2016年01月12日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                            stHeader;                /*Errorlog消息头*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8                    enErrorCode;             /*错误码*/

    TRRC_APP_PROTOCOL_STATE_ENUM_UINT8                enTrrcProtocolState;     /*RRC协议状态*/
    TRRC_APP_RRC_STATE_ENUM_UINT8                     enRrcState;              /*RRC状态，内部状态，非协议状态*/
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8                 enBandInfo;              /*工作频点所属BAND信息*/

    VOS_UINT16                                        usCellId;                /*服务小区ID*/
    VOS_UINT16                                        usFrequency;             /*工作频点*/
    VOS_UINT16                                        usLac;                   /*当前所在的Lac*/
    VOS_INT16                                         usRscp;                  /*服务小区能量*/
    VOS_UINT32                                        ulMcc;                   /*当前所在PLMN的Mcc*/
    VOS_UINT32                                        ulMnc;                   /*当前所在PLMN的Mnc*/

    VOS_UINT32                                        ulFlowControlBitMap;
    VOS_UINT32                                        ulMsgName;
}TRRC_APP_CONN_SETUP_RSVD_MSG_MAX_INFO_STRU;

#endif

/*****************************************************************************
 Structure      : TRRC_APP_CS_RELEASE_INFO_STRU
 Description    : TRRC CS链路释放上报的结构体
 修改历史 :
  1.日    期    : 2015年10月25日
    作    者    : f00272207
    修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog 消息头 */
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* 错误码*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU         stServCellInfo;         /* 服务小区信息 */
}TRRC_APP_CS_RELEASE_INFO_STRU;

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
Structure      : TRRC_APP_CS_NO_RBSETUP_INFO_STRU
Description    : CS域收不到网侧下发的RB SETUP时，TRRC上报给CHR的信息内容。
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                       stHeader;              /* Errorlog 消息头 */
    TRRC_APP_ERROR_CODE_ENUM_UINT8               enErrorCode;           /* 错误码*/

    TRRC_APP_PROTOCOL_STATE_ENUM_UINT8           enTrrcProtocolState;   /* RRC协议状态 */
    TRRC_APP_RRC_STATE_ENUM_UINT8                enRrcState;            /* RRC状态，内部状态，非协议状态 */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8            enBandInfo;            /* 工作频点所属BAND信息 */
    TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16          enErrcFlowCtrlType;    /* TD-SCDMA发生异系统过程时，异系统过程标识 */

    VOS_UINT16                                   usCellId;              /* 服务小区ID */
    VOS_UINT16                                   usFrequency;           /* 工作频点 */
    VOS_UINT16                                   usLac;                 /*当前所在的Lac*/
    VOS_UINT32                                   ulMcc;                 /*当前所在PLMN的Mcc*/
    VOS_UINT32                                   ulMnc;                 /*当前所在PLMN的Mnc*/
    VOS_INT16                                    usRscp;                /* 服务小区能量 */
    VOS_UINT8                                    aucResv[2];

    VOS_UINT32                                   ulTimeDiff;            /*记录没收到RB SETUP下一个流程与SMC COMPLETE之间的时间差*/
    VOS_UINT32                                   ulFlowControlBitMap;
    VOS_UINT32                                   ulErrCodeBitMap;

}TRRC_APP_CS_NO_RBSETUP_INFO_STRU;

/*****************************************************************************
Description    : CS域打电话的T2G CCO过程中，TRRC上报给CHR的信息内容。
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{

    OM_ERR_LOG_HEADER_STRU                         stHeader;             /* Errorlog 消息头 */
    TRRC_APP_ERROR_CODE_ENUM_UINT8                 enErrorCode;          /* 错误码*/

    TRRC_APP_PROTOCOL_STATE_ENUM_UINT8             enTrrcProtocolState;  /* RRC协议状态 */
    TRRC_APP_RRC_STATE_ENUM_UINT8                  enRrcState;           /* RRC状态，内部状态，非协议状态 */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8              enBandInfo;           /* 工作频点所属BAND信息 */
    TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16            enErrcFlowCtrlType;   /* TD-SCDMA发生异系统过程时，异系统过程标识 */

    VOS_UINT16                                     usCellId;             /* 服务小区ID */
    VOS_UINT16                                     usFrequency;          /* 工作频点 */
    VOS_UINT16                                     usLac;                /* 当前所在的Lac*/
    VOS_UINT32                                     ulMcc;                /* 当前所在PLMN的Mcc*/
    VOS_UINT32                                     ulMnc;                /* 当前所在PLMN的Mnc*/
    VOS_INT16                                      usRscp;               /* 服务小区能量 */
    VOS_UINT8                                      aucResv[2];

    VOS_UINT32                                     ulTimeStamp;          /* 记录流程执行到哪一步的时间戳*/
    VOS_UINT32                                     ulFlowControlBitMap;
    VOS_UINT32                                     ulErrCodeBitMap;

}TRRC_APP_CS_T2G_CCO_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS域打电话的过程中发生失步流程的有关信息
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_STATE_INFO_STRU                        stRrcAppStateInfo;    /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU              stServCellInfo;       /* 服务小区信息 */
    VOS_UINT32                                      ulTimeStamp;          /* 记录流程执行到哪一步的时间戳*/
    VOS_UINT32                                      ulCsCallChrFlowBitmap;
    VOS_UINT32                                      ulCsCallChrCodeBitmap;

}TRRC_CHR_CS_CALL_OUTOFSYNC_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS域打电话的过程中发生失步流程的有关信息
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_STATE_INFO_STRU                         stRrcAppStateInfo;    /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU               stServCellInfo;       /* 服务小区信息 */
    VOS_UINT32                                       ulTimeStamp;          /* 记录流程执行到哪一步的时间戳*/
    VOS_UINT32                                       ulCsCallChrFlowBitmap;
    VOS_UINT32                                       ulCsCallChrCodeBitmap;

}TRRC_CHR_CS_CALL_CONN_REL_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS CALL时SMC COMP 流程有关的CHR信息
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_STATE_INFO_STRU                         stRrcAppStateInfo;     /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU               stServCellInfo;        /* 服务小区信息 */
    VOS_UINT32                                       ulTimeStamp;           /* 记录流程执行到哪一步的时间戳*/
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32              enEstSignallingType[2];/* 记录当前建链的状态信息，从a_rrc_establishedSigCon[]中获取*/
    VOS_UINT32                                       ulCsCallChrFlowBitmap;
    VOS_UINT32                                       ulCsCallChrCodeBitmap;
}TRRC_CHR_CS_CALL_SMC_CPL_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS CALL时SIGNAL CONN REL时的有关CHR信息
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_STATE_INFO_STRU                         stRrcAppStateInfo;     /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU               stServCellInfo;        /* 服务小区信息 */
    VOS_UINT32                                       ulTimeStamp;           /* 记录流程执行到哪一步的时间戳*/
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32              enEstSignallingType[2];/* 记录当前建链的状态信息，从a_rrc_establishedSigCon[]中获取*/
    VOS_UINT32                                       ulCsCallChrFlowBitmap;
    VOS_UINT32                                       ulCsCallChrCodeBitmap;
}TRRC_CHR_CS_CALL_SIGNAL_REL_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS CALL过程中GU REL REQ时的有关CHR信息
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_STATE_INFO_STRU                          stRrcAppStateInfo;     /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU                stServCellInfo;        /* 服务小区信息 */
    VOS_UINT32                                        ulTimeStamp;           /*记录流程执行到哪一步的时间戳*/
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32               enEstSignallingType[2];/* 记录当前建链的状态信息，从a_rrc_establishedSigCon[]中获取*/
    VOS_UINT32                                        ulCsCallChrFlowBitmap;
    VOS_UINT32                                        ulCsCallChrCodeBitmap;
}TRRC_CHR_CS_CALL_GU_REL_REQ_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS CALL过程中GU REL REQ时的有关CHR信息
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_STATE_INFO_STRU                          stRrcAppStateInfo;      /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU                stServCellInfo;         /* 服务小区信息 */
    VOS_UINT32                                        ulTimeStamp;            /* 记录流程执行到哪一步的时间戳*/
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32               enEstSignallingType[2]; /* 记录当前建链的状态信息，从a_rrc_establishedSigCon[]中获取*/
    VOS_UINT32                                        ulCsCallChrFlowBitmap;
    VOS_UINT32                                        ulCsCallChrCodeBitmap;
}TRRC_CHR_CS_CALL_GU_TRANS_NTFY_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS域打电话EST REQ CHR信息内容。
修改历史 :
 1.日    期    : 2015年12月22日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{

    TRRC_APP_STATE_INFO_STRU                           stRrcAppStateInfo;     /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU                 stServCellInfo;        /* 服务小区信息 */
    VOS_UINT32                                         ulTimeStamp;           /* 记录流程执行到哪一步的时间戳*/
    TRRC_APP_EST_CAUSE_ENUM_UINT32                     enEstCause;            /* 记录当前建链的原因值，从v_rrc_establishmentCause获取*/
    VOS_UINT32                                         ulCsCallChrFlowBitmap;
    VOS_UINT32                                         ulCsCallChrCodeBitmap;
    VOS_UINT32                                         ulOpId;                /* 操作标识 */

}TRRC_CHR_CS_CALL_EST_REQ_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS域打电话RRC CONN REQ ERR LOG信息内容。
修改历史 :
 1.日    期    : 2015年12月22日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_STATE_INFO_STRU                           stRrcAppStateInfo;      /* 发生故障时状态信息 */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU                 stServCellInfo;         /* 服务小区信息 */
    VOS_UINT32                                         ulTimeStamp;            /* 记录流程执行到哪一步的时间戳*/
    TRRC_APP_EST_CAUSE_ENUM_UINT32                     enEstCause;             /* 记录当前建链的原因值，从v_rrc_establishmentCause获取*/

    TRRC_APP_EST_SIGNALLING_TYPE_UINT32                enEstSignallingType[2]; /* 域建链状态信息*/
    VOS_UINT32                                         ulCsCallChrFlowBitmap;
    VOS_UINT32                                         ulCsCallChrCodeBitmap;

    VOS_UINT32                                         ulMcc;                  /* 当前所在PLMN的Mcc*/
    VOS_UINT32                                         ulMnc;                  /* 当前所在PLMN的Mnc*/
    VOS_UINT16                                         usLac;                  /* 当前所在的Lac*/
    VOS_UINT8                                          aucResv[2];

}TRRC_CHR_CS_CALL_CONN_REQ_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS域打电话EST CNF ERR LOG信息内容。
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU                  stServCellInfo;        /* 服务小区信息 */
    VOS_UINT32                                          ulTimeStamp;           /*记录流程执行到哪一步的时间戳*/
    VOS_UINT32                                          ulCsCallChrFlowBitmap;
    VOS_UINT32                                          ulCsCallChrCodeBitmap;
    VOS_UINT32                                          ulOpId;                /* 操作标识 */
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32                 enEstSignallingType[2];/* 域建连状态信息*/
    RRC_NAS_EST_RESULT_ENUM_UINT32                      ulResult;              /* 该信令连接建立结果，取值见枚举定义 */
}TRRC_CHR_CS_CALL_EST_CNF_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的CS域打电话T2G CCO时的 ERR LOG信息内容。
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU                  stServCellInfo;        /* 服务小区信息 */
    TRRC_APP_STATE_INFO_STRU                            stRrcAppStateInfo;     /* 发生故障时状态信息 */
    VOS_UINT32                                          ulTimeStamp;           /*记录流程执行到哪一步的时间戳*/
    VOS_UINT32                                          ulCsCallChrFlowBitmap;
    VOS_UINT32                                          ulCsCallChrCodeBitmap;

}TRRC_CHR_CS_CALL_T2G_CCO_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的所有有关CS域打电话的一般信息内容。
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    TRRC_CHR_CS_CALL_EST_REQ_INFO_STRU                   stCsCallEstReqInfo;     /*打电话流程走到EST REQ时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_CONN_REQ_INFO_STRU                  stCsCallConnReqInfo;    /*打电话流程走到CONN REQ时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_EST_CNF_INFO_STRU                   stCsCallEstCnfInfo;     /*打电话流程走到CONN REQ时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_SMC_CPL_INFO_STRU                   stCsCallSMCCplInfo;     /*打电话流程走到SMC COMPLETE时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_OUTOFSYNC_INFO_STRU                 stCsCallOutOfSyncInfo;  /*打电话流程走到OUT OF SYNC时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_CONN_REL_INFO_STRU                  stCsCallConnRelInfo;    /*打电话流程走到RRC CONN REL时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_SIGNAL_REL_INFO_STRU                stCsCallSignalRelInfo;  /*打电话流程走到RRC SIGNAL REL时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_GU_REL_REQ_INFO_STRU                stCsCallGuRelReqInfo;   /*打电话流程走到GU REL REQ时本地保存的CHR信息*/
    TRRC_CHR_CS_CALL_GU_TRANS_NTFY_INFO_STRU             stCsCallGuTransNtfyInfo;/*打电话流程走到GU TRANS STATUS NOTIFY时本地保存的CHR信息*/
}TRRC_CHR_CS_CALL_GENERAL_INFO_STRU;

/*****************************************************************************
Description    : TRRC本地保存的所有有关CS域打电话的CHR信息内容。
修改历史 :
 1.日    期    : 2015年12月20日
   作    者    : l00280875
   修改内容    : 新建结构
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                                   enTrrcChrCsCallFlag;    /*标识是否是打电话流程的FLAG*/
    VOS_UINT8                                            aucResv[3];
    TRRC_CHR_CS_CALL_GENERAL_INFO_STRU                   stCsCallGeneralInfo;    /*打电话流程本地保存的一般CHR信息*/
    TRRC_CHR_CS_CALL_T2G_CCO_INFO_STRU                   stCsCallT2GCCOInfo;     /*打电话流程走到T2G CCO流程时本地保存的CHR信息*/
}TRRC_CHR_CS_CALL_INFO_STRU;
#endif

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
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

#endif /* end of TrrcErrLogInterface.h */


