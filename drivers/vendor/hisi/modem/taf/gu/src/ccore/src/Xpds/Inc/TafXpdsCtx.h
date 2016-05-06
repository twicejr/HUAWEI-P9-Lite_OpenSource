/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsCtx.h
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年7月13日
  最近修改   :
  功能描述   : CDMA AGPS业务全局变量声明
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月13日
    作    者   : g00261581
    修改内容   : CDMA-AGPS项目新增

******************************************************************************/

#ifndef __TAFXPDSCTX_H__
#define __TAFXPDSCTX_H__

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"
#include "PsTypeDef.h"
#include "MnComm.h"
#include "XpdsCasInterface.h"
#include "AtXpdsInterface.h"
#include "TafAppXsmsInterface.h"
#include "TafXpdsTimerMgmt.h"
#include "TafSdcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
/* 状态机栈的深度 */
#define TAF_XPDS_MAX_FSM_STACK_DEPTH         (4)

/* 消息的最大长度，包括状态机保存的入口消息和CACHE消息 */
#define TAF_XPDS_MAX_MSG_BUFFER_LEN          (1600)

/* 缓存消息队列的最大个数 */
#define TAF_XPDS_MAX_CACHE_MSG_QUEUE_NUM     (8)

#define TAF_XPDS_MAX_INT_MSG_QUEUE_NUM       (8)

#define TAF_XPDS_CUR_VERSION                 (0x02)
#define TAF_XPDS_MAX_DATA_LEN                (256)

#define TAF_XPDS_MAX_DELIVER_DATA_LEN        (200)  /* IS 801 协议规定 */
#define TAF_XPDS_MAX_PDM_MSG_BUF_LEN         (256)

#define TAF_XPDS_MSID_SIZE                   (15)
#define TAF_XPDS_RL_PSUE_RANG_MAX            (64)
#define TAF_XPDS_RL_PHASE_PILREC_MAX         (10)
#define TAF_XPDS_PDE_HEADER_LEN_MIN          (3)

/* 3GPP2 C.S0022-0  v3 .0:
    If this value is less than 0,the modile station shall set this field to '000000'.
    If this value is greater than '11111' the mobile station shall set this field to '11111'*/
#define TAF_XPDS_MAX_PILOT_STRENGTH_VALUE    (63)  /* IS 801 协议规定 */
#define TAF_XPDS_MIN_PILOT_STRENGTH_VALUE    (0)   /* IS 801 协议规定 */

#define TAF_XPDS_FL_SAT_INFO_MAX              (32) /* there can be maximum of 31 satellites */
#define TAF_XPDS_FL_ALM_SAT_MAX               (32)

#define TAF_XPDS_PILOT_MEAS_BUFF_MAX          (2 * 25 * XPDS_CAS_MAX_NEIGHBOR_NUM) /* 存放CAS上报pilot Phase值:按照每80ms上报一帧，最大能存放4s数据 */

#define TAF_XPDS_PILOT_PHASE_BUFF_MAX         (2 * 25)

#define TAF_XPDS_MSID_TYPE                   (0x02) /* IMSI_M type */
#define TAF_XPDS_MSINFO_MS_LS_REV            (0x00) /* MS LS revision type */
#define TAF_XPDS_MSINFO_MS_MODE              (0x00) /* digital mode indicator */
#define TAF_XPDS_MSINFO_PIL_PH_CAP           (0x04) /* one 16th of measurement capability */

#define TAF_XPDS_MSINFO_GPSAQUI_CAP_MSA      (0x0001) /* GPS aquisition Cap for MSA mode */
#define TAF_XPDS_MSINFO_LOCCALC_CAP_MSA      (0x0000) /* location aquisition caluculation CAP for MSA mode */

#define TAF_XPDS_MSINFO_GPSAQUI_CAP_MSB      (0x000D) /* GPS aquisition Cap for MSB mode */
#define TAF_XPDS_MSINFO_LOCCALC_CAP_MSB      (0x0018) /* location aquisition caluculation CAP for MSB mode */

#define TAF_XPDS_RL_GPS_RXCAP_SIZE           (32)
#define TAF_XPDS_RL_GPS_MSBC_CAP_SIZE        (128)
#define TAF_XPDS_RL_SECID_SIZE               (16)
#define TAF_XPDS_RL_LOCMEAS_PSUERAN_REC_MAX  (31)
#define TAF_XPDS_RL_LOCMEAS_FREQ_INFO_MAX    (7)
#define TAF_XPDS_RL_LOCMEAS_OFFST_REC_MAX    (63)
#define TAF_XPDS_RL_RPTR_ID_SIZE             (64)
#define TAF_XPDS_RL_SAT_LIST_SIZE            (32)
#define TAF_XPDS_RL_ACTIVE_SET_PN_MAX        (7)
#define TAF_XPDS_RL_NEIGHBT_PN_MAX           (63)
#define TAF_XPDS_RL_SAT_INFO_MAX             (16)
#define TAF_XPDS_RL_PILOT_PN_MAX             (64)
#define TAF_XPDS_RL_FREQ_INFO_MAX            (16)
#define TAF_XPDS_FL_RPTR_ID_LEN              (64)
#define TAF_XPDS_FL_NAVBITS_MAX              (64)
#define TAF_XPDS_FL_PRN_MAX                  (16)
#define TAF_XPDS_FL_DELAY_REC_MAX            (7)
#define TAF_XPDS_FL_SUBF123_MAX              (113)
#define TAF_XPDS_FL_SUBF45_MAX               (1875)
#define TAF_XPDS_FL_EXTBITS_NAV_FRAM_SIZE    (31)
#define TAF_XPDS_FL_ASSI_PILREC_MAX          (63)
#define TAF_XPDS_FL_DATREC_NUM               (17)
#define TAF_XPDS_NAVBITS_SUB45_SIZE          (75)
#define TAF_XPDS_FL_REQ_FREQ_MAX             (7)
#define TAF_XPDS_FL_EXTBITS_NAV_SAT_SIZE     (31)
#define TAF_XPDS_RL_BITMAS_REC_MAX           (8)
#define TAF_XPDS_FL_ALM_MAX_PILOT            (511)
#define TAF_XPDS_FL_ANTEN_MAX                (7)
#define TAF_XPDS_FL_SEC_ID_LEN               (128)
#define TAF_XPDS_FL_FREQ_INFO_MAX            (16)
#define TAF_XPDS_MPC_REPORT_FAIL_MAX_TIMES   (3)
#define TAF_XPDS_MSID_DATA_LEN_IN_BYTE       (7)
#define TAF_XPDS_START_DELIVERY_DATA_LEN_IN_BYTE            (9)

#define TAF_XPDS_GetPpmTimerExpireFlag()        (g_stTafXpdsCtx.stPdePubData.ucPpmTimerExpireFlag)
#define TAF_XPDS_SetPpmTimerExpireFlag(bValue)  (g_stTafXpdsCtx.stPdePubData.ucPpmTimerExpireFlag = (bValue))

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_XPDS_FSM_ID_ENUM
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2015年08月21日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum TAF_XPDS_FSM_ID_ENUM
{
    /***********************************************************************
     * XPDS L1状态机标识
     ***********************************************************************/
    /* XPDS L1 main状态机的标识 */
    TAF_XPDS_FSM_L1_MAIN                                    =0x00,

    /***********************************************************************
     * XPDS L2状态机的标识
     ***********************************************************************/
    /* 协议栈建链状态机 */
    TAF_XPDS_FSM_LINK_CTRL                                  =0x01,

    TAF_XPDS_FSM_CP_LINK_CTRL                               =0x02,

    /* 协议栈MPC交互状态机 */
    TAF_XPDS_FSM_MPC_PROC                                   =0x03,

    /* 协议栈PDE交互状态机 */
    TAF_XPDS_FSM_PDE_PROC                                   =0x04,

    TAF_XPDS_FSM_CP_PDE_PROC                                =0x05,

    TAF_XPDS_FSM_BUTT

};
typedef VOS_UINT32 TAF_XPDS_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_XPDS_L2_MPC_PROC_STA_ENUM
 枚举说明  : L2 MPC状态机ID枚举定义
 1.日    期   : 2015年08月21日
   作    者   : c00299064
   修改内容   : 新建
*****************************************************************************/
enum TAF_XPDS_L2_MPC_PROC_STA_ENUM
{

    TAF_XPDS_L2_MPC_PROC_STA_INIT                 = 0x00,     /* 初始化状态*/
    TAF_XPDS_L2_MPC_PROC_STA_WAIT_START_POS_RESP  = 0x01,     /* 正在定位状态 */
    TAF_XPDS_L2_MPC_PROC_STA_WAIT_POS_REPORT_RESP = 0x02,     /* 正在定位状态 */

    TAF_XPDS_L2_MPC_PROC_STA_BUTT
};
typedef VOS_UINT32 TAF_XPDS_L2_MPC_PROC_STA_ENUM_UINT32;

enum TAF_XPDS_PILOT_PHASE_CAP
{
    TAF_XPDS_FULL_CHIP_CAP = 0x0,
    TAF_XPDS_HALF_CHIP_CAP,
    TAF_XPDS_QUARTER_CHIP_CAP,
    TAF_XPDS_EIGHTH_CHIP_CAP,
    TAF_XPDS_SIXTEENTH_CHIP,

    TAF_XPDS_CAP_BUTT
};
typedef VOS_UINT8 TAF_XPDS_PILOT_PHASE_CAP_ENUM_UINT8;

/*****************************************************************************
枚举名    : TAF_XPDS_USER_PLANE_LINK_STATUS_ENUM
枚举说明  : 当前数据传输的通道链路

  1.日    期   : 2015年7月20日
    作    者   : g00256031
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_XPDS_UP_LINK_STATUS_ENUM
{
    TAF_XPDS_UP_LINK_NOT_EXISTED,
    TAF_XPDS_UP_LINK_MPC_CONNECTED,
    TAF_XPDS_UP_LINK_PDE_CONNECTED,
    TAF_XPDS_UP_LINK_MPC_PDE_BOTH_CONNECTED,

    TAF_XPDS_UP_LINK_STATUS_BUTT
};
typedef VOS_UINT8 TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8;


/** ****************************************************************************
 * Name        : TAF_XPDS_MS_TO_MPC_MSG_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_MS_TO_MPC_MSG_TYPE_ENUM
{
    ID_TAF_XPDS_MS_TO_MPC_START_POS_REQ             = 1,
    ID_TAF_XPDS_MS_TO_MPC_POS_REPORT                = 2,
    ID_TAF_XPDS_MS_TO_MPC_CANCEL_TRACK_SESSION      = 3,

    ID_TAF_XPDS_MS_TO_MPC_MSG_TYPE_BUTT
};

typedef VOS_UINT8 TAF_XPDS_MS_TO_MPC_MSG_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : ID_TAF_XPDS_MPC_MS_MSG_TYPE_ENUM
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_MPC_MS_MSG_TYPE_ENUM
{
    TAF_XPDS_MPC_MS_START_POS_RSP             = 1,
    TAF_XPDS_MPC_MS_POS_REPORT_RSP            = 2,

    TAF_XPDS_MPC_MS_BUTT
};

typedef VOS_UINT8 TAF_XPDS_MPC_MS_MSG_TYPE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : XCC_SMS_PIF_MSG_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_RCV_XSMS_MSG_TYPE_ENUM
{
    TAF_XPDS_RCV_XSMS_MSG_TYPE_NI_POS_REQ                = 1,
    TAF_XPDS_RCV_XSMS_MSG_TYPE_CANCEL_NI_TRACK           = 2,
    TAF_XPDS_RCV_XSMS_MSG_TYPE_REFRESH_MR_TRACK          = 3,

    TAF_XPDS_RCV_XSMS_MSG_TYPE_BUTT
};

typedef VOS_UINT32 TAF_XPDS_RCV_XSMS_MSG_TYPE_ENUM_UINT32;


/** ****************************************************************************
 * Name        : TAF_XPDS_POS_STATUS_INDICATOR_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_POS_STATUS_INDICATOR_ENUM
{
    TAF_XPDS_POS_STATUS_INDICATOR_USE_GPSONE         = 0,
    TAF_XPDS_POS_STATUS_INDICATOR_CACHED_POS         = 1,
    TAF_XPDS_POS_STATUS_INDICATOR_WITH_CELL_SECTOR   = 2,
    TAF_XPDS_POS_STATUS_INDICATOR_REQ_NOT_AUTH       = 3,
    TAF_XPDS_POS_STATUS_INDICATOR_MPC_REFUSED        = 4,
    TAF_XPDS_POS_STATUS_INDICATOR_ACK_REQ_NO_ACTION  = 5,
    TAF_XPDS_POS_STATUS_INDICATOR_SRV_UNAVAILABLE    = 6,
    TAF_XPDS_POS_STATUS_INDICATOR_CANCEL_FIX_REQ     = 7,

    TAF_XPDS_POS_STATUS_INDICATOR_BUTT
};

typedef VOS_UINT8 TAF_XPDS_POS_STATUS_INDICATOR_ENUM_UINT8;


/** ****************************************************************************
 * Name        : TAF_XPDS_PDE_ADDR_ENCODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_PDE_ADDR_ENCODE_ENUM
{
    TAF_XPDS_PDE_ADDR_ENCODE_URL         = 0,
    TAF_XPDS_PDE_ADDR_ENCODE_IP          = 1,

    TAF_XPDS_PDE_ADDR_ENCODE_BUTT
};

typedef VOS_UINT8 TAF_XPDS_PDE_ADDR_ENCODE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_XPDS_MPC_TO_MS_MSG_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_MPC_TO_MS_MSG_TYPE_ENUM
{
    TAF_XPDS_MPC_TO_MS_START_POS_RSP             = 0,
    TAF_XPDS_MPC_TO_MS_POS_REPORT_RSP            = 1,

    TAF_XPDS_MPC_TO_MS_MSG_TYPE_BUTT
};

typedef VOS_UINT8 TAF_XPDS_MPC_TO_MS_MSG_TYPE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : TAF_XPDS_MS_POS_CAPABILITY_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_MS_POS_CAPABILITY_ENUM
{
    TAF_XPDS_MS_POS_CAPABILITY_NONE            = 0,
    TAF_XPDS_MS_POS_CAPABILITY_CELL_ID         = 1,
    TAF_XPDS_MS_POS_CAPABILITY_AFLT_ONLY       = 2,
    TAF_XPDS_MS_POS_CAPABILITY_MSA_HYBRID      = 3,
    TAF_XPDS_MS_POS_CAPABILITY_BOTH            = 4,

    TAF_XPDS_MS_POS_CAPABILITY_BUTT
};

typedef VOS_UINT8 TAF_XPDS_MS_POS_CAPABILITY_ENUM_UINT8;


/** ****************************************************************************
 * Name        : TAF_XPDS_APP_TYPE_INDICATOR_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_APP_TYPE_INDICATOR_ENUM
{
    TAF_XPDS_APP_TYPE_INDICATOR_WAP                  = 0,
    TAF_XPDS_APP_TYPE_INDICATOR_BREW                 = 1,
    TAF_XPDS_APP_TYPE_INDICATOR_JAVA                 = 2,
    TAF_XPDS_APP_TYPE_INDICATOR_MS_RESIDENT          = 3,
    TAF_XPDS_APP_TYPE_INDICATOR_NETWORK_INITIATED    = 4,
    TAF_XPDS_APP_TYPE_INDICATOR_JAVA_BASED_BREW      = 5,

    TAF_XPDS_APP_TYPE_INDICATOR_BUTT
};

typedef VOS_UINT8 TAF_XPDS_APP_TYPE_INDICATOR_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM
{
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_CANCEL                 = 0,
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_LONG_TIME_INACTIVE     = 1,
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_PDE_HANDOFF            = 2,

    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_BUTT
};

typedef VOS_UINT8 TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_REJ_POS_REASON_ENUM
{
    TAF_XPDS_REJ_POS_REASON_VERSION_NOT_SUPPORT         = 0,
    TAF_XPDS_REJ_POS_REASON_PRIVACY_RESTRICTIONS        = 1,
    TAF_XPDS_REJ_POS_REASON_IS801_IN_PROCESS            = 2,
    TAF_XPDS_REJ_POS_REASON_TCP_IP_NOT_OPEN             = 3,
    TAF_XPDS_REJ_POS_REASON_USER_DENIED_REQ             = 4,
    TAF_XPDS_REJ_POS_REASON_POP_UP_SCREEN_TIMER_OUT     = 5,
    TAF_XPDS_REJ_POS_REASON_BUTT
};

typedef VOS_UINT8 TAF_XPDS_REJ_POS_REASON_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_XPDS_CANCEL_REASON_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_CANCEL_REASON_ENUM
{
    TAF_XPDS_CANCEL_REASON_USER_CANCEL              = 0,
    TAF_XPDS_CANCEL_REASON_MPC_DISCONNECT           = 1,
    TAF_XPDS_CANCEL_REASON_MPC_RSP_TIME_OUT         = 2,
    TAF_XPDS_CANCEL_REASON_PDE_DISCONNECT           = 3,
    TAF_XPDS_CANCEL_REASON_PDE_REJ_POS_SESSION      = 4,
    TAF_XPDS_CANCEL_REASON_IS801_SESSION_TIME_OUT   = 5,
    TAF_XPDS_CANCEL_REASON_BUTT
};

typedef VOS_UINT8 TAF_XPDS_CANCEL_REASON_ENUM_UINT8;

enum TAF_XPDS_MPC_REPORT_STATUS_INDICATOR_ENUM
{
    TAF_XPDS_MPC_REPORT_STATUS_INDICATOR_ACK         = 0,
    TAF_XPDS_MPC_REPORT_STATUS_DISCON_REPORT         = 1,
    TAF_XPDS_MPC_REPORT_STATUS_PDE_HANDOFF           = 2,

    TAF_XPDS_MPC_REPORT_STATUS_INDICATOR_BUTT

};
typedef VOS_UINT8 TAF_XPDS_MPC_REPORT_STATUS_INDICATOR_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 结构说明  : 定位操作回复结果枚举
 1.日    期   : 2015年08月28日
   作    者   : g00256031
   修改内容   : 新增枚举
*****************************************************************************/
enum TAF_XPDS_POS_PROC_RSLT_ENUM
{
    TAF_XPDS_PROC_RSLT_SUCC,

    TAF_XPDS_PROC_RSLT_AT_STOP,
    TAF_XPDS_PROC_RSLT_XSMS_NI_CANCEL,
    TAF_XPDS_PROC_RSLT_XSMS_SI_CANCEL,
    TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH,
    TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE,
    TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT,
    TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT,
    TAF_XPDS_PROC_RSLT_PDE_REJECT,
    TAF_XPDS_PROC_RSLT_IS801_TIMEOUT,

    TAF_XPDS_PDE_PROC_RSLT_FAIL,
    TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT,
    TAF_XPDS_PDE_PROC_RSLT_ABORT,
    TAF_XPDS_MPC_PROC_RSLT_FAIL,
    TAF_XPDS_MPC_PROC_RSLT_TIMER_OUT,
    TAF_XPDS_MPC_PROC_RSLT_ABORT,
    TAF_XPDS_MPC_OPER_RSLT_POS_TECH_CHANGED,
    TAF_XPDS_MPC_OPER_RSLT_DISCON_REPORT,
    TAF_XPDS_MPC_OPER_RSLT_PDE_HANDOFF,
    TAF_XPDS_PROC_RSLT_BUTT,
};
typedef VOS_UINT32 TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_XPDS_RCV_PDE_DATA_MASK_ENUM
 枚举说明  : 下行PDE数据解码之后的消息类型MASK定义
 1.日    期   : 2015年8月27日
   作    者   : y00174758
   修改内容   : 新增
*****************************************************************************/
enum TAF_XPDS_RCV_PDE_DATA_MASK_ENUM
{
    TAF_XPDS_RCV_PDE_DATA_MASK_REQ_LOC_INFO             = 0x00000001,
    TAF_XPDS_RCV_PDE_DATA_MASK_REQ_MS_INFO              = 0x00000002,
    TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PSEURANGE_MEAS       = 0x00000004,
    TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PILOT_PHASE_MEAS     = 0x00000008,
    TAF_XPDS_RCV_PDE_DATA_MASK_REQ_CANCELLATION         = 0x00000010,

    TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT               = 0x00000020,
    TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP         = 0x00000040,
    TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_ACQ_ASSIST      = 0x00000080,
    TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH         = 0x00000100,
    TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM         = 0x00000200,
};
typedef VOS_UINT32 TAF_XPDS_RCV_PDE_DATA_MASK_ENUM_UINT32;

enum TAF_XPDS_PDE_SESSION_STATUS_ENUM
{
    TAF_XPDS_PDE_SESSION_STATUS_NULL,
    TAF_XPDS_PDE_SESSION_STATUS_STARTED,
    TAF_XPDS_PDE_SESSION_STATUS_ENDED,

    TAF_XPDS_PDE_SESSION_STATUS_BUTT
};

typedef VOS_UINT8 TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8;

enum TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM
{
    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_MS,
    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_NETWORK,

    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_BUTT
};

typedef VOS_UINT8 TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8;


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/

/*****************************************************************************
 结构名    : TAF_XPDS_MSG_STRU
 结构说明  : XREG消息结构，状态机保存的入口消息和CACHE消息都使用此结构
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[TAF_XPDS_MAX_MSG_BUFFER_LEN];
}TAF_XPDS_MSG_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_CACHE_MSG_INFO_STRU
 结构说明  : 缓存的消息内容
  1.日    期   : 2015年08月21日
    作    者   : g00256031
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    TAF_XPDS_MSG_STRU                  stCacheMsg;         /* 缓存的具体内容 */
}TAF_XPDS_CACHE_MSG_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_INT_MSG_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[TAF_XPDS_MAX_INT_MSG_QUEUE_NUM]; /* HSD的消息队列数组，存放消息指针 */
}TAF_XPDS_INT_MSG_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_FSM_REGISTER_CTX_STRU
 结构说明  : 存放注册状态机的上下文信息
 日    期  : 2015年08月21日
 作    者  : g00256031
 修改内容  : 新建

*****************************************************************************/
typedef struct
{
    /* 本次迭代不涉及 */
    VOS_UINT8                           aucRsved[4];
}TAF_XPDS_FSM_REGISTER_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_FSM_L1_MAIN_CTX_STRU
 结构说明  : 存放L1状态机的上下文信息
 日    期  : 2015年08月21日
 作    者  : g00256031
 修改内容  : 新建

*****************************************************************************/
typedef struct
{
    /* 本次迭代不涉及 */
    VOS_UINT8                           aucRsved[4];
}TAF_XPDS_FSM_L1_MAIN_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_FSM_EXTRA_CTX_UNION
 结构说明  : 状态机状态描述结构,状态机上下文信息
 日    期  : 2015年08月21日
 作    者  : g00256031
 修改内容  : 新建
*****************************************************************************/
typedef union
{
    TAF_XPDS_FSM_REGISTER_CTX_STRU     stRegisterCtx;

    TAF_XPDS_FSM_L1_MAIN_CTX_STRU      stL1MainCtx;

}TAF_XPDS_FSM_EXTRA_CTX_UNION;

/*****************************************************************************
 结构名    : TAF_XPDS_CAGPS_UPLINK_CTX_STRU
 结构说明  : CDMA AGPS用户面链路相关上下文
 1.日    期   : 2015年09月10日
   作    者   : g00261581
   修改内容   : CDMA AGPS项目新增结构
*****************************************************************************/
typedef struct
{
    AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32    enDataCallState;
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32  enMpcBindStatus;
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32  enPdeBindStatus;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32      enUpLinkAbortScene;
    TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8      enCurrLinkStatus;
    VOS_UINT8                               aucReserved[3];
}TAF_XPDS_CAGPS_UPLINK_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 日    期  : 2015年08月21日
 作    者  : g00256031
 修改内容  : 新建

*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    TAF_XPDS_FSM_ID_ENUM_UINT32         enFsmId;

    /* 上层状态机标识 */
    TAF_XPDS_FSM_ID_ENUM_UINT32         enParentFsmId;

    /* 上层状态机入口消息类型 */
    VOS_UINT32                          ulParentEventType;

    /* 当前状态 */
    VOS_UINT32                          ulState;

    /* 入口消息MSGID和内容  */
    TAF_XPDS_MSG_STRU                   stEntryMsg;

    /* 状态机数据 */
    TAF_XPDS_FSM_EXTRA_CTX_UNION        unFsmCtx;
}TAF_XPDS_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_FSM_STACK_STRU
 结构说明  : 状态机栈描述结构
 日    期  : 2015年08月21日
 作    者  : g00256031
 修改内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */
    VOS_UINT16                          usStackPopFlg;                          /* 当前栈pop标志 */
    TAF_XPDS_FSM_CTX_STRU               astFsmStack[TAF_XPDS_MAX_FSM_STACK_DEPTH];  /* 状态机栈的深度 */
}TAF_XPDS_FSM_STACK_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_PD_MSG_HEADER_STRU
 *
 * Description : Position Determination Data Message header fields for PDE message type 0x00
 *******************************************************************************/

typedef  struct
{
    VOS_UINT8                           ucSessStart;
    VOS_UINT8                           ucSessEnd;
    VOS_UINT8                           ucSessSrc;
    VOS_UINT8                           ucSessTag;
    VOS_UINT8                           ucPdMsgType;
    VOS_UINT8                           ucNumOfReq;
    VOS_UINT8                           ucNumOfResp;
    VOS_UINT8                           ucRegulInd;
    VOS_UINT16                          usPdMsgLen;
    VOS_UINT8                           aucReserve[2];
}TAF_XPDS_PD_MSG_HEADER_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_PDM_HEADER_CTX_STRU
 *
 * Description : PDE header fields for PDE message type 0x00 updating from BS to maintain in context
 *******************************************************************************/
typedef  struct
{
    VOS_UINT8                           ucSessStart;
    VOS_UINT8                           ucSessEnd;
    VOS_UINT8                           ucSessSrc;
    VOS_UINT8                           ucSessTag;
    VOS_UINT8                           ucPDEMsgType;
    VOS_UINT8                           aucReserve[3];
}TAF_XPDS_PDM_HEADER_CTX_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_RESP_FLAG_STRU
 *
 * Description : inroder to maintain whether response type is unsolicited or not
                 based on request recieved from BS
 *******************************************************************************/
typedef  struct
{
    VOS_UINT32                          OP_ReqLocResp           :1;       /* provide location response */
    VOS_UINT32                          OP_ReqMsInfo            :1;       /* provide MS information */
    VOS_UINT32                          OP_ReqPsuRangMeas       :1;       /* provide psuedo range measurement */
    VOS_UINT32                          OP_ReqPilotMeas         :1;       /* provide pilot phase measurement */
    VOS_UINT32                          OP_RespGpsIonInEphim    :1;   /* ION data in provide Ephimeris */
    VOS_UINT32                          OP_ReqExtLocResp        :1;       /* provide Extended location response */
    VOS_UINT32                          OP_ReqExtMsInfo         :1;       /* provide Extended MS information */
    VOS_UINT32                          OP_ReqExtCancel         :1;       /* flag to indicate extended cancel is recieved */
    VOS_UINT32                          OP_ReqGenLocMeas        :1;       /* flag to indicate gen location meas req recieved */
    VOS_UINT32                          OP_ReqGpsCoarseLoc      :1;       /* flag to indicate gps coarse loc req recieved */
    VOS_UINT32                          OP_ReqMsgDelayMeas      :1;       /* flag to indicate message delay meas req recieved */
    VOS_UINT32                          OP_ReqBearingMeas       :1;       /* flag to indicate bearing meas req recieved */
    VOS_UINT32                          OP_ReqServSysInfo       :1;       /* flag to indicate server system req recieved */

    VOS_UINT32                          OP_Reserved             :19;
}TAF_XPDS_FWDLINK_REQ_RESP_FLAG_STRU;

/*****************************************************************************
 结构名    :TAF_XPDS_MS_ID_RECORD_STRU
 结构说明  :MS ID RECORD的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMsIdRec[TAF_XPDS_MSID_DATA_LEN_IN_BYTE + 1];
}TAF_XPDS_MS_ID_RECORD_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_START_DELV_DATA_STRU
 *
 * Description : start deliver data message structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;   /* total length of the message, range [0..255] */
    VOS_UINT8                           ucMSIDType; /* message ID type */
    VOS_UINT8                           ucMSIDLen;  /* message ID length, range [0..15] */
    VOS_UINT8                           aucReserved[1]; /* padding */
    TAF_XPDS_MS_ID_RECORD_STRU          stMsIdRec; /* MSID */
}TAF_XPDS_START_DELV_DATA_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_GPS_ACQ_ASSIST_STRU
 *
 * Description : Request GPS aquisition assistance message. refer 2.2.4.1.3
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDopplerReq;       /**< whether doppler term of 0th order requested or not, range [0..1] */
    VOS_UINT8                           ucAddDopplerReq;    /**< whether additional doppler term of 0th order requested or not, range [0..1] */
    VOS_UINT8                           ucCodePhParaReq;    /**< whether code phase parameter requested or not, range [0..1] */
    VOS_UINT8                           ucAZELReq;          /**< whether azimuth and elivation angle requested or not, range [0..1] */
} TAF_XPDS_REVLINK_REQ_GPS_ACQ_ASSIST_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_LOC_RSP_STRU
 *
 * Description : Request location response message. refer 2.2.4.1.1
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHeightReq;     /**< whether height information is requested or not, range [0..1] */
    VOS_UINT8                           ucClkCorGpsReq;  /**< Clock correcction for GPS requested or not, range [0..1] */
    VOS_UINT8                           ucVelocityReq;   /**< Velocity information requested or not, range [0..1] */
    VOS_UINT8                           ucReserved;      /**< Reserved */
} TAF_XPDS_REVLINK_REQ_LOC_RSP_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_GPS_EPH_STRU
 *
 * Description : Request GPS Ephimeries message. refer 2.2.4.1.5
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAlphaBetaParaReq; /**< whether alpha and beta param requested or not, range [0..1] */
    VOS_UINT8                           aucReserved[3];     /**< Reserved */
} TAF_XPDS_REVLINK_REQ_GPS_EPH_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_MS_INFO_STRU
 *
 * Description : provide MS information message. refer 2.2.4.2.3
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                     ucMSLSRev;      /**< mobile station location standard revision number */
    VOS_UINT8                                     ucMSMode;       /**< digital mode indicator */
    VOS_UINT8                                     ucReserved;     /**< reserved */
    TAF_XPDS_PILOT_PHASE_CAP_ENUM_UINT8           enPilotPhCap;   /**< pilot phase capability */
    VOS_UINT16                                    usGpsAquiCap;   /**< GPS aquisition capability */
    VOS_UINT16                                    usLocCalcCap;   /**< position caluculation capability  */
} TAF_XPDS_REVLINK_RSP_MS_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_LOC_INFO_STRU
 *
 * Description : provide location response message. refer 2.2.4.2.2
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLongitude;     /**< longitude */
    VOS_UINT32                          ulLattitude;     /**< lattitude */
    VOS_UINT32                          ulClockBias;     /**< clock bias, range [-13000.++249143] */
    VOS_UINT16                          usTimeRefCdma;   /**< CDMA system time when the solution is valid */
    VOS_UINT16                          usVelocityHor;   /**< horizontal velocity magnitude  */
    VOS_UINT16                          usHeading;       /**< heading */
    VOS_UINT16                          usVelocityVer;   /**< vertical velocity, range [-64..+63.5]  */
    VOS_UINT16                          usClockDrift;    /**< clock drift  */
    VOS_UINT16                          usHeight;        /**< height in meters  */
    VOS_UINT8                           ucLocUncerAng;   /**< angle of axis wrt true north  */
    VOS_UINT8                           ucLocUncerA;     /**< standard deviation of angle along */
    VOS_UINT8                           ucLocUncerP;     /**< standrard deviation of angle perpendicular  */
    VOS_UINT8                           ucFixType;       /**< fix type  */
    VOS_UINT8                           ucVelocityIncl;  /**< velocity information included or not, range [0..1]  */
    VOS_UINT8                           ucClockIncl;     /**< clock bias included or not, range [0..1]  */
    VOS_UINT8                           ucHeightIncl;    /**< height information included or not, range [0..1]  */
    VOS_UINT8                           ucLocUncerV;     /**< standard deviation of vertical error  */
} TAF_XPDS_REVLINK_RSP_LOC_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_PSEUDO_RANGE_INFO_STRU
 *
 * Description : pseudo range record
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvPRNNum;     /**< satellite PRN numbere, range [1..37]*/
    VOS_UINT8                           ucSvCNO;        /**< satellite C/N , range [0..63]*/
    VOS_UINT8                           ucMulPathInd;   /**< multipath indicator */
    VOS_UINT8                           ucPsRangeRmsEr; /**< psuedorange RMS error */
    VOS_INT16                           sPsDoppler;     /**< psuedo doppler */
    VOS_UINT16                          usSvCodePhWh;   /**< satellite code phase whole chips */
    VOS_UINT16                          usSvCodePhFr;   /**< satellite code phase fractional chips */
    VOS_UINT8                           aucReserve[2];  /**< padding */
}TAF_XPDS_PSEUDO_RANGE_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU
 *
 * Description : provide pseudo range measurement message. refer 2.2.4.2.5
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPartNum;          /**< part number */
    VOS_UINT8                               ucTotalparts;       /**< total number of parts, range [1..8] */
    VOS_UINT8                               ucNumOfPS;          /**<number of pseudoranges in this part */
    VOS_UINT8                               ucTimeRefSrc;       /**< time reference source */
    VOS_UINT32                              ulTimeRef;          /**< time of validity of the parameters reported */
    VOS_UINT16                              usRefPN;            /**< time reference PN sequence offset */
    VOS_INT16                               sMobileSysOffset;  /**< mobile station system time offset */
    VOS_UINT8                               ucOffsetIncl;       /**< whether offset included or not, range [0..1] */
    VOS_UINT8                               aucReserve[3];      /**< ratio of GPS weight to total weight */
    TAF_XPDS_PSEUDO_RANGE_INFO_STRU         astPsuedoInfo[TAF_XPDS_RL_PSUE_RANG_MAX];  /**< psuedo range inforamtion */
}TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_PILOT_INFO_STRU
 *
 * Description : provide pilot phase measurement message pilot information
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPilotPnPhase;     /**< pilot PN phase */
    VOS_UINT8                           ucPilotStrgth;      /**< pilot strength */
    VOS_UINT8                           ucRmsErrPhase;      /**< RMS error phase */
    VOS_UINT16                          usPilotPN;          /**< 0~ 511 ,Pilot PN */
}TAF_XPDS_PILOT_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU
 *
 * Description : start deliver data message structure
 *******************************************************************************/
typedef struct
{
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_UINT8 enRcvCasRefLocStatus;
    VOS_UINT8                            aucReserve[3];
    VOS_UINT32                           ulPilotMeasNum;
    XPDS_CAS_PILOT_MEAS_INFO_STRU        astPilotMeasInfo[TAF_XPDS_PILOT_MEAS_BUFF_MAX]; /* message ID */
    VOS_UINT32                           ulPnPhasebuffNum;
    VOS_UINT32                           aulPnPhasebuff[TAF_XPDS_PILOT_PHASE_BUFF_MAX];
}TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU;

 /******************************************************************************
 * Name        : XPDS_CAS_REF_LOC_REQ_PID_INFO_STRU
 *
 * Description : start deliver data message structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                           ulCasRptPID;                         /* 记录当前和CAS交互PID*/
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_UINT8 enRptType;                           /* 0: start,1:stop */
    VOS_UINT8                            aucReserved[3];
} XPDS_CAS_REF_LOC_REQ_PID_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU
 *
 * Description : provide pilot phase measurement message. refer 2.2.4.2.6
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimeRefMS;         /**< time of validity of the parameters reported */
    VOS_UINT16                          usCdmaFreq;          /**< frequency assignment */
    VOS_UINT16                          usBaseId;            /**< base station identifier */
    VOS_UINT16                          usSID;               /**< system identification number */
    VOS_UINT16                          usNID;               /**< network identification number */
    VOS_UINT16                          usRefPn;             /**< reference PN sequence offset */
    VOS_UINT8                           ucTotalRxPow;        /**< total recieved power */
    VOS_UINT8                           ucPartNum;           /**< part number among total parts */
    VOS_INT16                           sMobSysTOffst;       /**< mobile station system time offset */
    VOS_UINT8                           ucOffsetIncl;        /**< whether offset included or not, range [0..1] */
    VOS_UINT8                           ucTotalParts;        /**< total number of parts */
    VOS_UINT8                           ucNumOfPilotP;       /**< number of pilots in this part */
    VOS_UINT8                           ucAddPilotIncl;      /**< additional pilots included or not, range [0..1] */
    VOS_UINT8                           ucAddBandClass;      /**< additional band class */
    VOS_UINT8                           ucAddTotRxPow;       /**< total recieved power on additional frequency */
    VOS_UINT16                          usAddCdmaFreq;       /**< additional frequency assignement */
    VOS_UINT8                           ucNumOfAddPilotP;    /**< number of additional pilots */
    VOS_UINT8                           ucRefPilotStrgth;    /**< pilot strength */
    VOS_UINT8                           ucBandClass;         /**< band class */
    VOS_UINT8                           aucReserve[3];       /**< padding */
    TAF_XPDS_PILOT_INFO_STRU            astPilotRec[TAF_XPDS_RL_PHASE_PILREC_MAX];     /**< pilot record */
    TAF_XPDS_PILOT_INFO_STRU            astAddPilotRec[TAF_XPDS_RL_PHASE_PILREC_MAX];  /**< additional pilot record */
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU    stCasRptPilotBuff;
}TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GPS_EPHM_SAT_REC_STRU
 *
 * Description : GPS ephimeries satellite record information
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAF0;              /**< apparent satellite clock correction */
    VOS_UINT32                          ulOmegaDot;         /**< rate of right asention */
    VOS_UINT32                          ulOmega;            /**< argument of perugee */
    VOS_UINT32                          ulAngle_Incli;      /**< inclination angle at the reference time  */
    VOS_UINT32                          ulA_Sqrt;           /**< square root of semi major axis */
    VOS_UINT32                          ulOmega_0;          /**< longitude of ascending node */
    VOS_UINT32                          ulEcCentricity;     /**< eccentricity */
    VOS_UINT32                          ulM0;               /**< mean anamoly of reference time */
    VOS_UINT16                          usAF1;              /**< apparent satellite clock correction */
    VOS_UINT16                          usTOC;              /**< clock date reference time  */
    VOS_UINT16                          usIdot;             /**< rate of inclination angle */
    VOS_UINT16                          usC_RC;             /**< amplitude of cosine reference */
    VOS_UINT16                          usC_IS;             /**< amplitude of sine harmonic */
    VOS_UINT16                          usC_IC;             /**< amplitude of cosine harmonic */
    VOS_UINT16                          usTOE;              /**< ephimeries reference time  */
    VOS_UINT16                          usC_US;             /**< amplitude of sine harmonic correction */
    VOS_UINT16                          usC_UC;             /**< amplitude of cosine harmonic */
    VOS_UINT16                          usDelta_N;          /**< mean motion difference */
    VOS_UINT16                          usC_RS;             /**< amplitude of sine harmonic correction */
    VOS_UINT8                           ucSv_Prn_Num;       /**< satellite PRN number */
    VOS_UINT8                           ucIODE;             /**< issue of data */
    VOS_UINT8                           ucAF2;              /**< apparent satellite clock correction */
    VOS_UINT8                           aucReserve[3];      /**< reserved */
} TAF_XPDS_GPS_EPHM_SAT_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU
 *
 * Description : provide  GPS ephimeries message. refer 3.2.4.2.10
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfSvP;     /**< number of satellites, range [0..16] */
    VOS_UINT8                           ucPartNum;      /**< part number */
    VOS_UINT8                           ucTotalParts;   /**< total number of parts */
    VOS_UINT8                           ucABParIncl;    /**< alpha and beta parameter included or not, range [0..1] */
    VOS_UINT8                           ucAlpha0;       /**< ionospheric cor parameter, alpha 0 */
    VOS_UINT8                           ucAlpha1;       /**< ionospheric cor parameter, alpha 1 */
    VOS_UINT8                           ucAlpha2;       /**< ionospheric cor parameter, alpha 2 */
    VOS_UINT8                           ucAlpha3;       /**< ionospheric cor parameter, alpha 3 */
    VOS_UINT8                           ucBeta0;        /**< ionospheric cor parameter, beta 0 */
    VOS_UINT8                           ucBeta1;        /**< ionospheric cor parameter, beta 1  */
    VOS_UINT8                           ucBeta2;        /**< ionospheric cor parameter, beta 2 */
    VOS_UINT8                           ucBeta3;        /**< ionospheric cor parameter, beta 3  */
    TAF_XPDS_GPS_EPHM_SAT_REC_STRU      astSatInfo[TAF_XPDS_FL_SAT_INFO_MAX]; /**< satellite information */
} TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_CANCEL_STRU
 *
 * Description : Request cancellation message. refer 3.2.4.1.5
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCancelType;    /**< cancel type */
    VOS_UINT8                           aucReserved[3];  /**< padding */
} TAF_XPDS_FWDLINK_REQ_CANCEL_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_PILOT_PHASE_MEAS_STRU
 *
 * Description : Request pilot phase  measurement message. refer 3.2.4.1.3
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrefRespQual;  /**< preferred response quality*/
    VOS_UINT8                           ucNumOfFixes;    /**< number of fixes, range [0..256] */
    VOS_UINT8                           ucTimeBetFix;    /**< time between fixes, range [0..255] */
    VOS_UINT8                           ucOffsetReq;     /**< whether offset information is requested or not, range [0..1] */
    VOS_UINT8                           ucDesPilPhRes;   /**< desired pilot phase resolution, range [0..1] */
    VOS_UINT8                           aucReserved[3];  /**< padding */
} TAF_XPDS_FWDLINK_REQ_PILOT_PHASE_MEAS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_LOC_RESP_STRU
 *
 * Description : Request location response message. refer 3.2.4.1.1
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrefRespQual;  /**< preferred response quality*/
    VOS_UINT8                           ucNumOfFixes;    /**< number of fixes, range [0..256] */
    VOS_UINT8                           ucTimeBetFix;    /**< time between fixes, range [0..255] */
    VOS_UINT8                           ucHeightReq;     /**< whether height information is requested or not, range [0..1] */
    VOS_UINT8                           ucClkCorGpsReq;  /**< Clock correcction for GPS requested or not, range [0..1] */
    VOS_UINT8                           ucVelocityReq;   /**< Velocity information requested or not, range [0..1] */
    VOS_UINT8                           aucReserved[2];  /**< Reserved */
} TAF_XPDS_FWDLINK_REQ_LOC_RESP_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_PSUERANGE_MEAS_STRU
 *
 * Description : Request psuedorange measurement message. refer 3.2.4.1.2
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrefRespQual;  /**< preferred response quality*/
    VOS_UINT8                           ucNumOfFixes;    /**< number of fixes, range [0..256] */
    VOS_UINT8                           ucTimeBetFix;    /**< time between fixes, range [0..255] */
    VOS_UINT8                           ucOffsetReq;     /**< whether offset information is requested or not, range [0..1] */
} TAF_XPDS_FWDLINK_REQ_PSUERANGE_MEAS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GPS_ALM_SAT_REC_STRU
 *
 * Description : GPS almanac satellite record information
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulM0;              /**< mean anomoly at reference time */
    VOS_UINT32                          ulA_Sqrt;          /**< square root of semi major axis */
    VOS_UINT32                          ulOmega_0;         /**< longitude of ascending node of orbit plane */
    VOS_UINT32                          ulOmega;           /**< argument of perigee */
    VOS_UINT16                          usDelta_Incli;     /**< apparent satellite clock correction */
    VOS_UINT16                          usEcCentricity;    /**< eccentricity  */
    VOS_UINT16                          usOmegaDot;        /**< rate of ascension */
    VOS_UINT16                          usAF0;             /**< apparant satellite clock correction af0 */
    VOS_UINT16                          usAF1;             /**< apparant satellite clock correction af1 */
    VOS_UINT8                           ucSv_Prn_Num;      /**< satellite PRN number */
    VOS_UINT8                           ucReserve;         /**< reserved */
} TAF_XPDS_GPS_ALM_SAT_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU
 *
 * Description : provide GPS almanac message. refer 3.2.4.2.9
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfSvP;     /**< number of satellites, range [0..64] */
    VOS_UINT8                           ucPartNum;      /**< part number */
    VOS_UINT8                           ucTotalParts;   /**< total number of parts */
    VOS_UINT8                           ucWeekNum;      /**< GPS week number */
    VOS_UINT8                           ucTOA;          /**< time of almanac */
    VOS_UINT8                           aucReserved[3]; /**< padding */
    TAF_XPDS_GPS_ALM_SAT_REC_STRU       astSatInfo[TAF_XPDS_FL_ALM_SAT_MAX]; /**< satellite information */
} TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_BS_PROV_GPS_SAT_INFO_STRU
 *
 * Description : provide GPS satellite message pilot information
 *******************************************************************************/
typedef struct
{
    VOS_INT16                           sDoppler0;     /**< doppler 0th order */
    VOS_UINT16                          usSvCodePh;     /**< GPS code phase */
    VOS_UINT8                           ucSvPrnNum;     /**< satellite PRN number */
    VOS_INT8                            cDoppler1;     /**< doppler 1st order */
    VOS_UINT8                           ucDopplerWin;   /**< doppler search window , range [0..4]*/
    VOS_UINT8                           ucSvCodePhInt;  /**< integer number of code periods */
    VOS_UINT8                           ucGpsBitNum;    /**< 2 least significant bits of GPS bit number */
    VOS_UINT8                           ucSvCodePhWin;  /**< total code phase window, range [0..31] */
    VOS_UINT8                           ucAzimuth;      /**< azimuth of GPS satellite */
    VOS_UINT8                           ucElevation;    /**< elevation angle of GPS satellite */
}TAF_XPDS_BS_PROV_GPS_SAT_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU
 *
 * Description : provide  GPS aquisition assistance message. refer 3.2.4.2.5
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRefPn;           /**< reference PN offset */
    VOS_UINT8                           ucNumOfSv;         /**< pnumber of satellites  */
    VOS_UINT8                           ucTimeOfApp;       /**< CDMA system time when aquisition assitence is applicable */
    VOS_UINT8                           ucDopp0Incl;        /**< doppler of 0th order included or not, range [0..1] */
    VOS_UINT8                           ucAddDoppIncl;     /**< additional doppler included or not, range [0..1]*/
    VOS_UINT8                           ucCodePhParIncl;   /**< code phase information included or not, range [0..1]*/
    VOS_UINT8                           ucAzElIncl;        /**< azimuth and elevation angle included or not, range [0..1] */
    TAF_XPDS_BS_PROV_GPS_SAT_INFO_STRU  astSatInfo[TAF_XPDS_FL_SAT_INFO_MAX];    /**< satellite information */
} TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU
 *
 * Description : provide location response message. refer 3.2.4.2.2
 *******************************************************************************/
typedef struct
{
    VOS_INT32                           lLongitude;      /**< longitude */
    VOS_INT32                           lLattitude;      /**< lattitude */
    VOS_INT32                           lClockBias;      /**< clock bias, range [-13000.++249143] */
    VOS_UINT16                          usTimeRefCdma;   /**< CDMA system time when the solution is valid */
    VOS_UINT16                          usVelocityHor;   /**< horizontal velocity magnitude  */
    VOS_UINT16                          usHeading;       /**< heading */
    VOS_INT16                           sClockDrift;     /**< clock drift  */
    VOS_INT16                           sHeight;         /**< height in meters  */
    VOS_INT8                            cVelocityVer;    /**< vertical velocity, range [-64..+63.5]  */
    VOS_UINT8                           ucLocUncerAng;   /**< angle of axis wrt true north  */
    VOS_UINT8                           ucLocUncerA;     /**< standard deviation of angle along */
    VOS_UINT8                           ucLocUncerP;     /**< standrard deviation of angle perpendicular  */
    VOS_UINT8                           ucFixType;       /**< fix type  */
    VOS_UINT8                           ucVelocityIncl;  /**< velocity information included or not, range [0..1]  */
    VOS_UINT8                           ucClockIncl;     /**< clock bias included or not, range [0..1]  */
    VOS_UINT8                           ucHeightIncl;    /**< height information included or not, range [0..1]  */
    VOS_UINT8                           ucLocUncerV;     /**< standard deviation of vertical error  */
    VOS_UINT8                           ucReserved;      /**< padding  */
} TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU;




/*****************************************************************************
 结构名    :TAF_XPDS_TIME_STAMP_STRU
 结构说明  :TIME STAMP的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWeekNum;
    VOS_UINT32                          ulSecNum;
}TAF_XPDS_TIME_STAMP_STRU;

/*****************************************************************************
 结构名    :TAF_XPDS_TIME_STAMP_STRU
 结构说明  :TIME STAMP的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAppRecLen;
    VOS_UINT8                           aucAppIdRec[10];
}TAF_XPDS_APP_ID_REC_STRU;

/*****************************************************************************
 结构名    :TAF_XPDS_PDE_ADDR_STRU
 结构说明  :TIME STAMP的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPdeAddLen;
    TAF_XPDS_PDE_ADDR_ENCODE_ENUM_UINT8                     enPdeEncoding;
    VOS_UINT16                                              usPdePortNum;
    VOS_UINT8                                               aucPdeUrlAddr[256];
    VOS_UINT32                                              ulPdeIpAddr;
}TAF_XPDS_PDE_ADDR_STRU;

/*****************************************************************************
 结构名    :TAF_XPDS_MPC_START_POS_RSP_STRU
 结构说明  :TAF_XPDS_MPC_START_POS_RSP_STRU的结构体 参考协议(gpsone user plane ms-mpc ch4.2.3.1)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    TAF_XPDS_MPC_MS_MSG_TYPE_ENUM_UINT8                     enMsgType;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucCorrelationId;
    TAF_XPDS_POS_STATUS_INDICATOR_ENUM_UINT8                 enPosStatusInd;
    VOS_UINT16                                              usPosIncFlag;
    TAF_XPDS_PDE_ADDR_STRU                                   stPdeAddr;
    TAF_XPDS_TIME_STAMP_STRU                                 stTimeStamp;
    VOS_UINT32                                              ulLat;
    VOS_UINT32                                              ulLong;
    VOS_UINT8                                               ucLocUncrtntyAng;
    VOS_UINT8                                               ucLocUncrtntyA;
    VOS_UINT8                                               ucLocUncrtntyP;
    VOS_UINT8                                               ucVelocityIncl;
    VOS_UINT16                                              usVelocityHor;
    VOS_UINT16                                              usHeading;
    VOS_UINT16                                              usVelocityVer;
    VOS_UINT16                                              usHeihtIncl;
    VOS_UINT16                                              usHeiht;
    VOS_UINT16                                              usLocUncrtntyV;
}TAF_XPDS_MPC_START_POS_RSP_STRU;


/*****************************************************************************
 结构名    :TAF_XPDS_MPC_POS_REPORT_RSP_STRU
 结构说明  :TAF_XPDS_MPC_POS_REPORT_RSP_STRU的结构体 参考协议(gpsone user plane ms-mpc ch4.2.3.1)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    TAF_XPDS_MPC_MS_MSG_TYPE_ENUM_UINT8                     enMsgType;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucCorrelationId;
    TAF_XPDS_MPC_REPORT_STATUS_INDICATOR_ENUM_UINT8         enReportStatus;
    VOS_UINT16                                              usRsv;
    TAF_XPDS_PDE_ADDR_STRU                                  stPdeAddr;
}TAF_XPDS_MPC_POS_REPORT_RSP_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_RCV_XSMS_POS_REQ_STRU
 *
 * Description : MPC Send to trigger a NI tracking. refer (gpsone user plane ms-mpc ch3.1.1.1)
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    VOS_UINT8                                               ucMsgType;
    VOS_UINT8                                               ucLen;
    TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_ENUM_UINT8         enNotificationInd;
    TAF_XPDS_POS_TECH_INDICATOR_ENUM_UINT8                  enPosTechInd;
    VOS_UINT8                                               ucPosQoSInc;
    VOS_UINT8                                               ucPosQoS;
    TAF_XPDS_IS801_MODE_ENUM_UINT8                          enIS801PosMode;
    VOS_UINT16                                              usNumOfFixs;
    VOS_UINT16                                              usTimeBetweenFixs;
    VOS_UINT8                                               ucCorrelationId;
    VOS_UINT8                                               ucReqIdEncode;
    VOS_UINT8                                               ucReqIdLen;
    VOS_UINT8                                               aucData[257];
}TAF_XPDS_RCV_XSMS_POS_REQ_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_RCV_CANCEL_NI_TRACK_STRU
 *
 * Description : MPC Send to cancel a NI tracking. refer (gpsone user plane ms-mpc ch3.1.1.1)
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    VOS_UINT8                                               ucMsgType;
    VOS_UINT8                                               ucLen;
    VOS_UINT8                                               ucCorrlationId;
}TAF_XPDS_RCV_CANCEL_NI_TRACK_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_RCV_REFRESH_MR_TRACK_STRU
 *
 * Description : MPC Send to trigger a NI tracking. refer (gpsone user plane ms-mpc ch3.1.1.2)
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    VOS_UINT8                                               ucMsgType;
    VOS_UINT8                                               ucLen;
    VOS_UINT8                                               ucCorrlationId;
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8             enCauseCode;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_RCV_REFRESH_MR_TRACK_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_XSMS_REJ_POS_REQ_STRU
 *
 * Description : XPDS send to rej pos req .refer (gpsone user plane ms-mpc ch3.2.1.1)
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    VOS_UINT8                                               ucMsgType;
    VOS_UINT8                                               ucLen;
    VOS_UINT8                                               ucCorrlationId;
    TAF_XPDS_REJ_POS_REASON_ENUM_UINT8                      enRejReason;
    VOS_UINT8                                               ucCellInc;
    VOS_UINT16                                              usSID;
    VOS_UINT16                                              usNID;
    VOS_UINT16                                              usBaseId;
    VOS_UINT32                                              ulBaseLat;
    VOS_UINT32                                              ulBaseLong;
    TAF_XPDS_TIME_STAMP_STRU                                stTimeStamp;

}TAF_XPDS_XSMS_REJ_POS_REQ_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_XSMS_CANCEL_POS_NOTIFICATION_STRU
 *
 * Description : XPDS Send to cancel pos notification. refer (gpsone user plane ms-mpc ch3.2.1.2)
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    VOS_UINT8                                               ucMsgType;
    VOS_UINT8                                               ucLen;
    VOS_UINT8                                               ucCorrlationId;
    TAF_XPDS_CANCEL_REASON_ENUM_UINT8                       enCancelReason;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XSMS_CANCEL_POS_NOTIFICATION_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_RCV_XSMS_MSG_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_XPDS_RCV_XSMS_MSG_TYPE_ENUM_UINT32               enMsgChoice;

    union
    {
        TAF_XPDS_RCV_XSMS_POS_REQ_STRU                 stPosReq;
        TAF_XPDS_RCV_CANCEL_NI_TRACK_STRU              stCancelNI;
        TAF_XPDS_RCV_REFRESH_MR_TRACK_STRU             stRefreshMR;
    }stXsmsMsgUnion;
}TAF_XPDS_RCV_XSMS_MSG_STRU;






/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_EXT_LOC_RESP_STRU
 *
 * Description : Request extended location response message. refer 2.2.4.1.8
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFixTypeReq;      /**< base station fix or mobile station fix, range [0..1] */
    VOS_UINT8                           ucHoriLocUncerReq; /**< whether BS or MS include elliptical horizontal location uncertainity, range [0..1] */
    VOS_UINT8                           ucHeightReq;       /**< whether BS or MS include height information, range [0..1] */
    VOS_UINT8                           ucClockCorrReq;    /**< whether BS or MS include clock correction, range [0..1] */
    VOS_UINT8                           ucVelocityReq;     /**< whether BS or MS include velocity information, range [0..1] */
    VOS_UINT8                           ucHoriVelUncerReq; /**< whether BS or MS include elliptical horizontal velocity uncertainity, range [0..1] */
    VOS_UINT8                           aucReserved[2];    /**< Reserved */

} TAF_XPDS_REVLINK_REQ_EXT_LOC_RESP_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_ENH_BS_ALM_FREQ_INFO_STRU
 *
 * Description : enhance base station almanac request frequency information
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usCdmaFreq;         /**< cdma frequency */
    VOS_UINT8                           ucBandClass;        /**< band class */
    VOS_UINT8                           ucModeInd;          /**< mode indicator, range [0..3] */
    VOS_UINT8                           ucPilotRecAsPrev;   /**< pilot record is as previous or not, range [0..1] */
    VOS_UINT8                           ucNumOfPilots;      /**< number of pilot pn present, range [0..63] */
    VOS_UINT8                           aucReserve[2];      /**< reserved */
    VOS_UINT16                          ausPilotPn[TAF_XPDS_RL_PILOT_PN_MAX];     /**< pilot PN */
} TAF_XPDS_REQ_ENH_BS_ALM_FREQ_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_ENH_BS_ALM_STRU
 *
 * Description : Request enhanced base station almanac message. refer 2.2.4.1.9
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPilotIdReq;         /**< pilot id information requested or not, range [0..1] */
    VOS_UINT8                               ucRepeatInfoReq;      /**< repeater information requested or not, range [0..1] */
    VOS_UINT8                               ucAntenaAngInfoReq;   /**< antena angle information requested or not, range [0..1] */
    VOS_UINT8                               ucAntenaRngInfoReq;   /**< antena range information requested or not, range [0..1] */
    VOS_UINT16                              usMaxRadius;          /**< maximal radius, range [1..515] */
    VOS_UINT8                               ucMaxRadIncl;         /**< whether max no radius included or not, range [0..1] */
    VOS_UINT8                               ucMaxNoPilotIncl;     /**< maximum no of pilots included or not, range [0..1] */
    VOS_UINT16                              usMaxNoOfPilots;      /**< maximal number of pilots, range [0..511] */
    VOS_UINT8                               ucFreqListIncl;       /**< whether freq list included or not, range [0..1] */
    VOS_UINT8                               ucNoOfFreq;           /**< number of freq included, range [0..16] */
    TAF_XPDS_REQ_ENH_BS_ALM_FREQ_INFO_STRU  astFreqInfo[TAF_XPDS_RL_FREQ_INFO_MAX];      /**< frequency information */
} TAF_XPDS_REVLINK_REQ_ENH_BS_ALM_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_GEN_AQUI_ASSI_STRU
 *
 * Description : Request general aquisition assistance message. refer 2.2.4.1.10
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLocRefReq;        /**< location reference information requested or not, range [0..1] */
    VOS_UINT8                           ucClockCorrGpsReq;  /**< clock correction for GPS time information requested or not, range [0..1] */
    VOS_UINT8                           ucSvInfoReq;        /**< GPS satellite information requested or not, range [0..1] */
    VOS_UINT8                           ucSvOptModeInfoReq; /**< satellite operating mode information requested or not, range [0..1] */
    VOS_UINT8                           ucDopp2Req;         /**< 2nd derivative of doppler requested or not, range [0..1] */
    VOS_UINT8                           ucAzElAngleReq;     /**< azimuth and elevation angle requested or not, range [0..1] */
    VOS_UINT8                           ucBSInfoReq;        /**< BS information requested or not, range [0..1] */
    VOS_UINT8                           ucRepeaterInfoReq;  /**< repeater information requested or not, range [0..1] */
    VOS_UINT8                           ucPilotAquiThrIncl; /**< pilot aquisition threshold included or not, range [0..1] */
    VOS_UINT8                           ucPilotAquiThrsh;   /**< pilot aquisition threshold, range [-42.. -14] */
    VOS_UINT8                           aucReserved[2];     /**< reserved */
} TAF_XPDS_REVLINK_REQ_GEN_AQUI_ASSI_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_SAT_BITMASK_REC_STRU
 *
 * Description : satellite bit mask record
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSvMask;        /**< satellite bit mask */
    VOS_UINT8                           ucNavMsgFormat;  /**< navigation message format, range [0..4] */
    VOS_UINT8                           ucSvMaskAsPrev;  /**< satellite bitmask msg as previous  or not, range [0..1] */
    VOS_UINT8                           ucSvMaskAllOne;  /**< satellite bitmask all ones, range [0..1] */
    VOS_UINT8                           ucReserved;      /**< reserved */
} TAF_XPDS_SAT_BITMASK_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_EXT_GPS_SENS_ASSI_STRU
 *
 * Description : Request extended GPS sensitivity assistance message. refer 2.2.4.1.11
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvMaskIncl;      /**< satellite bitmask information included or not, range [0..1] */
    VOS_UINT8                           ucNoOfSvMasks;     /**< number of bitmask records, range [0..7] */
    VOS_UINT8                           aucReserve1[2];    /**< reserved */
    TAF_XPDS_SAT_BITMASK_REC_STRU       astBitMaskRec[TAF_XPDS_RL_BITMAS_REC_MAX];  /**< bitmask record */
    VOS_UINT16                          usReqRefBitNum;    /**< request reference bit number, range [0..1499]  */
    VOS_UINT8                           ucReqRefBitIncl;   /**< request reference bit number included or not, range [0..1] */
    VOS_UINT8                           ucReqDRSizeIncl;   /**< DR size included or not, range [0..1] */
    VOS_UINT8                           ucReqDRSize;       /**< DR size, range [0..1020] */
    VOS_UINT8                           aucReserve2[3];    /**< reserved */
} TAF_XPDS_REVLINK_REQ_EXT_GPS_SENS_ASSI_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_EXT_GPS_EPH_STRU
 *
 * Description : Request extended GPS ephimeries message. refer 2.2.4.1.12
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucABparaReq;       /**< alpha and beta parameter requested or not, range [0..1] */
    VOS_UINT8                           ucSVMaskIncl;      /**< satellite bit mask include or not, range [0..1] */
    VOS_UINT8                           aucReserve[2];     /**< reserved */
    VOS_UINT32                          ulSVMask;          /**< satellite bit mask  */
} TAF_XPDS_REVLINK_REQ_EXT_GPS_EPH_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_GPS_NAV_MSGBITS_STRU
 *
 * Description : Request GPS navigation message bits message. refer 2.2.4.1.6
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSubFrame4and5Req; /**< whether subframes 4 and 5 requested or not, range [0..1] */
    VOS_UINT8                           aucReserved[3];     /**< Reserved */
} TAF_XPDS_REVLINK_REQ_GPS_NAV_MSGBITS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_SATELLITE_REC_STRU
 *
 * Description : satellite record
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIODE;        /**< issue of data */
    VOS_UINT8                           ucSvId;        /**< satellite ID */
    VOS_UINT8                           aucReserve[2]; /**< reserve */
} TAF_XPDS_SATELLITE_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_DGPS_ASSI_STRU
 *
 * Description : Request DGPS assistance message. refer 2.2.4.1.14
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfSV;       /**< number of satellite record, range [0..16] */
    VOS_UINT8                           ucTOELimitIncl;  /**< time limit of ephimeries included or not, range [0..1]  */
    VOS_UINT8                           ucTOELimit;      /**< time limit of ephimeries */
    VOS_UINT8                           ucABparaReq;     /**< alpha and beta parameter requested or not, range [0..1] */
    TAF_XPDS_SATELLITE_REC_STRU         astSatInfo[TAF_XPDS_RL_SAT_INFO_MAX];  /**< satellite record */
} TAF_XPDS_REVLINK_REQ_DGPS_ASSI_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_EXT_LOC_RESP_STRU
 *
 * Description : provide extended location response message. refer 2.2.4.2.10
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFixTypeIncl;     /**< fix type information included or not, range [0..1] */
    VOS_UINT8                           ucFixType;         /**< fix type , range [0..16] */
    VOS_UINT8                           ucTimeRefIncl;     /**< time reference included or not, range [0..1] */
    VOS_UINT8                           ucLocUncHType;     /**< horizontal location uncertainity type */
    VOS_UINT32                          ulTimeRef;         /**< time reference */
    VOS_UINT32                          ulLattitude;       /**< lattitude  */
    VOS_UINT32                          ulLongitude;       /**< longitude */
    VOS_UINT8                           ucLocUncH;         /**< horizontal location uncertainity , range [0..30]*/
    VOS_UINT8                           ucLocUncHCnf;      /**< horizontal location uncertainity confidential level */
    VOS_UINT8                           ucLocUncAng;       /**< angle of axis of standard error eclipse for horizontal location uncertainity */
    VOS_UINT8                           ucLocUncA;         /**< standard deviation of error along angle specified for Horizontal loc uncertainity */
    VOS_UINT8                           ucLocUncP;         /**< standard deviation of error perpendicular angle specified for Horizontal loc uncertainity */
    VOS_UINT8                           ucHeightIncl;      /**< height information included or not, range [0..1]*/
    VOS_UINT8                           ucLocUncV;         /**< vertical location uncertainity */
    VOS_UINT8                           ucLocUncVCnf;      /**< vertical location uncertainity confidential level */
    VOS_UINT16                          usHeight;          /**< height in meters, range [-500..15883] */
    VOS_UINT16                          usVeloHor;         /**< horizontal velocity magnitude, range [0..511.75]*/
    VOS_UINT16                          usHeading;         /**< heading */
    VOS_UINT8                           ucVeloIncl;        /**< velocity information included or not, range [0..1]*/
    VOS_UINT8                           ucVeloUncHType;    /**< Horizontal velocity uncertainity type */
    VOS_UINT8                           ucVeloUncH;        /**< horizontal velocity uncertainity */
    VOS_UINT8                           ucVeloUncHCnf;     /**< horizontal velocity uncertainity confidence */
    VOS_UINT8                           ucVeloUncAng;      /**< angle of axis of standard error eclipse for horizontal velocity uncertainity */
    VOS_UINT8                           ucVeloUncA;        /**< standard deviation of error along angle specified for Horizontal velocity uncertainity, range [0..16]*/
    VOS_UINT8                           ucVeloUncP;        /**< standard deviation of error perpendicular angle specified for Horizontal velocity uncertainity */
    VOS_UINT8                           ucVeloVertIncl;    /**< vertical velocity included or not, range [0..1] */
    VOS_UINT8                           ucVeloVert;        /**< vertical velocity */
    VOS_UINT8                           ucVeloUncV;        /**< vertical velocity uncertainity */
    VOS_UINT8                           ucVeloUncVCnf;     /**< vertical velocity uncertainity confidential level */
    VOS_UINT8                           ucClockBiasIncl;   /**< clock bias included or not, range [0..1] */
    VOS_UINT8                           ucClockDriftIncl;  /**< clock drift included or not, range [0..1] */
    VOS_UINT8                           ucImprLocSupp;     /**< improved location measurement completed or not, range [0..1]*/
    VOS_UINT32                          ulClockBias;       /**< clock bias */
    VOS_UINT32                          ulClockDrift;      /**< clock drift */
}TAF_XPDS_REVLINK_RSP_EXT_LOC_RESP_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_GLOBAL_INFO_REC_STRU
 *
 * Description : global info record structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGloInfRecLen;     /**< part number in total number of parts */
    VOS_UINT8                           ucMsgSeq;           /**< total number of parts , range [0..16]*/
    VOS_UINT8                           ucTimeRefSrc;       /**< whether global information is as previous or not, range [0..1] */
    VOS_UINT8                           ucPilotIdIncl;      /**< pilot ID included or not  , range [0..1] */
    VOS_UINT32                          ulTimeRef;          /**< time reference */
    VOS_UINT16                          usSID;              /**< sector ID */
    VOS_UINT16                          usNID;              /**< network ID */
    VOS_UINT16                          usBaseId;           /**< base station ID */
    VOS_UINT8                           ucModeInd;          /**< mode indicator */
    VOS_UINT8                           ucMscIdIncl;        /**< MSC id included or not  , range [0..1] */
    VOS_UINT32                          ulMscId;            /**< MSC id */
    VOS_UINT8                           aucSectorId[TAF_XPDS_RL_SECID_SIZE];    /**< sector ID */
}TAF_XPDS_GLOBAL_INFO_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_PSUEDO_RAND_REC_STRU
 *
 * Description : psuedorandom record structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvRecLen;              /**<  satellite record length */
    VOS_UINT8                           ucPRNNum;                /**<  PRN number */
    VOS_UINT8                           ucPRFreqAsPrev;          /**<  frequency on which PR measured as previous or not */
    VOS_UINT8                           ucPRFreq;                /**<  PR frequency */
    VOS_UINT16                          usDeltaPRTimeRef;        /**<  difference between reference for this measurement and common ref time*/
    VOS_UINT16                          usSvCodePhWh;            /**<  satellite code phase whole chips */
    VOS_UINT16                          usSvCodePhFr;            /**<  satellite code phase fractional chips */
    VOS_UINT8                           ucPRTimeRefAsPrev;       /**<  pseudorandom time refrence as previous or not, range [0..1] */
    VOS_UINT8                           ucSvCodePhIntIncl;       /**<  satellite code phase integer code included or not */
    VOS_UINT16                          usPrPsDoppler;           /**<  satellite psuedo doppler */
    VOS_UINT8                           ucSvCodePhInt;           /**<  integer number of code periods */
    VOS_UINT8                           ucPrErrInd;              /**<  psuedo random range error indicator */
    VOS_UINT8                           ucPrRmsErr;              /**<  psuedorandom RMS error */
    VOS_UINT8                           ucPrPsRmsDoppErr;        /**<  satellite psuedo doppler RMS error */
    VOS_UINT8                           ucCNO;                   /**<  satellite C/N */
    VOS_UINT8                           ucPrFalseAlarProb;       /**<  estimate psuedorange false alarm probability */
    VOS_UINT8                           ucPrFalseAlarRange;      /**<  estimate psuedorange false alarm range */
    VOS_UINT8                           aucReserved[3];          /**<  padding */
}TAF_XPDS_PSUEDO_RAND_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_PP_FREQ_PILOT_REC_STRU
 *
 * Description : pilot record structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPilotPnPh;         /**<  pilot phase */
    VOS_UINT8                           ucPilotRecLen;       /**<  pilot record length */
    VOS_UINT8                           ucRptrDetStatus;     /**<  repeater detection status range [0..7] */
    VOS_UINT8                           ucRptrType;          /**<  repeater type , range [0..7]*/
    VOS_UINT8                           ucRptrIdIncl;        /**<  repeater signal information included or not, range [0..1] */
    VOS_UINT8                           aucRptrId[TAF_XPDS_RL_RPTR_ID_SIZE];       /**<  repeater signal identification */
    VOS_UINT8                           ucPpErrInd;          /**<  pilot phase measurement error indication */
    VOS_UINT8                           ucPpRmsEr;           /**<  pilot phase RMS error */
    VOS_UINT8                           ucPpPsDoppler;       /**<  pilot phase psuedo doppler */
    VOS_UINT8                           ucPpPsDoppRmsErr;    /**<  psuedo doppler RMS error, range [0..7] */
    VOS_UINT8                           ucPilotStrngth;      /**<  pilkot strength */
    VOS_UINT8                           ucPpFalseAlmProb;    /**<  pilot phase false alarm probability, range [0..3] */
    VOS_UINT8                           ucPpFalseAlmRange;   /**<  pilot phase false alarm range, range [0..3] */
    VOS_UINT8                           ucReserved;          /**<  padding */
}TAF_XPDS_PP_FREQ_PILOT_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_PP_FREQ_INFO_STRU
 *
 * Description : PP frequency information structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usCdmaFreq;        /**<  frequency */
    VOS_UINT16                          usDeltaPpTimeRef;  /**<  reference time differemce between this measurement and common ref time */
    VOS_UINT8                           ucBandClass;       /**<  band class */
    VOS_UINT8                           ucModeInd;         /**<  mode indicator */
    VOS_UINT8                           ucTotRxPow;        /**<  total recieved power */
    VOS_UINT8                           ucPpTimeRefAsPrev; /**<  pilot phase time reference as previous */
    VOS_UINT8                           ucRptrInfoIncl;    /**<  repeator information included or not, range [0..1] */
    VOS_UINT8                           ucRptrIdLen;       /**<  repeater identification length */
    VOS_UINT8                           ucReserved;        /**<  reserved */
    VOS_UINT8                           ucNumOfPilTxF;     /**<  number of pilot records */
    TAF_XPDS_PP_FREQ_PILOT_REC_STRU     astPilotRec[TAF_XPDS_RL_PHASE_PILREC_MAX];   /**< pilot record */

}TAF_XPDS_PP_FREQ_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_OFFSET_REC_STRU
 *
 * Description : offset record structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usCdmaTxOffst;    /**<  frequency offset */
    VOS_UINT8                           ucOffstVar;       /**<  offset variable value */
    VOS_UINT8                           ucTxPower;        /**<  Tx power */
}TAF_XPDS_OFFSET_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_GEN_LOCMEAS_STRU
 *
 * Description : provide general location measurement message. refer 2.2.4.2.12
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPartNum;                 /**< part number in total number of parts */
    VOS_UINT8                           ucTotalParts;              /**< total number of parts , range [0..16]*/
    VOS_UINT8                           ucGloInfoAsPrev;           /**< whether global information is as previous or not, range [0..1] */
    VOS_UINT8                           ucReserved;                /**< retry time  , range [0..7] */
    TAF_XPDS_GLOBAL_INFO_REC_STRU       stGblInfRec;               /**< global information record if prev flag is 0 */
    VOS_UINT8                           ucPrInfIncl;               /**< pseudorandon range included or not, range [0..1] */
    VOS_UINT8                           ucIndPrTimeRefIncl;        /**< indivisual psuedorandom ref time included or not , range [0..1]*/
    VOS_UINT8                           ucNoOfPrP;                 /**< number of psuedorandom record in this request, range [0..31] */
    VOS_UINT8                           ucReserved1;               /**< padding */
    TAF_XPDS_PSUEDO_RAND_REC_STRU       astPRRecord[TAF_XPDS_RL_LOCMEAS_PSUERAN_REC_MAX];           /**< psuedo range record */
    VOS_UINT8                           ucPpInfInclP;              /**< pilot phase information included or not, range [0..1] */
    VOS_UINT8                           ucIndPpTimeRefIncl;        /**< indivisual pilot phase ref time included or not, range [0..1] */
    VOS_UINT8                           ucPpPsDopplrIncl;          /**< pilot phase psuedo doppler information included or not, range [0..1] */
    VOS_UINT8                           ucNumOfFreq;               /**< number of frequency records, range [0..7] */
    TAF_XPDS_PP_FREQ_INFO_STRU          astPPFreq[TAF_XPDS_RL_LOCMEAS_FREQ_INFO_MAX];              /**< frequency record */
    VOS_UINT16                          usOffStartRefTime;         /**< offset start reference time */
    VOS_UINT8                           ucOffstInfoInclP;          /**< offset information included or not, range [0..1] */
    VOS_UINT8                           ucOffstRefTimeInc;         /**< offset reference time included or not, range [0..1] */
    VOS_UINT8                           ucOffstVarIncl;            /**< offset variable included or not, range [0..1] */
    VOS_UINT8                           ucTxPowIncl;               /**< Tx power included or not, range [0..1] */
    VOS_UINT8                           ucNumOfOffRec;             /**< total number of offset records, range [0..63] */
    VOS_UINT8                           ucReserved2;               /**< reserved */
    TAF_XPDS_OFFSET_REC_STRU            astOffsetRec[TAF_XPDS_RL_LOCMEAS_OFFST_REC_MAX];          /**< offset record */
}TAF_XPDS_REVLINK_RSP_GEN_LOCMEAS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_EXT_CANC_ACK_STRU
 *
 * Description : provide extended cancellation acknowledgement message. refer 2.2.4.2.13
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCanclTypeAck;     /**< cancellation type */
    VOS_UINT8                           ucNoOutReq;         /**< whether outstanding req of type is there or not, range [0..1] */
    VOS_UINT8                           aucReserved[2];     /**< padding */
}TAF_XPDS_REVLINK_RSP_EXT_CANC_ACK_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_EXT_REJECT_STRU
 *
 * Description : provide extended reject message. refer 2.2.4.2.9
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRejReqType;        /**< rejected request type */
    VOS_UINT8                           ucRejReason;         /**< reject reason */
    VOS_UINT8                           ucRetryTimeIncl;     /**< whether retry time included or not, range [0..1] */
    VOS_UINT8                           ucRetryTime;         /**< retry time  , range [0..7] */
}TAF_XPDS_REVLINK_RSP_EXT_REJECT_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_EXT_MSINFO_STRU
 *
 * Description : provide extended MS information message. refer 2.2.4.2.11
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usAcqCap;          /**< aquisition capability */
    VOS_UINT16                          ucLocCalcCap;      /**< position caluculation capability */
    VOS_UINT16                          usAvailInfStatus;  /**< whether retry time included or not, range [0..1] */
    VOS_UINT8                           ucMsLsRev;         /**< MS local standard revision number */
    VOS_UINT8                           ucMsCapincl;       /**< MS capabilities included or not, range [0..1] */
    VOS_UINT8                           ucRptrDetCap;      /**< repeater detection capability */
    VOS_UINT8                           ucBearingCap;      /**< bearing measurement capability */
    VOS_UINT8                           ucGpsRxCapIncl;    /**< GPS reciever capability inclujded or not  , range [0..1] */
    VOS_UINT8                           ucGpsRxCapLen;     /**< GPS reciever capability  length */
    VOS_UINT8                           ucMsBcCapIncl;     /**< MS band class capability include or not  , range [0..1] */
    VOS_UINT8                           ucMsBcCapLen;      /**< MS band class capability length */
    VOS_UINT8                           ucReserved[2];
    VOS_UINT8                           aucGpsRxCap[TAF_XPDS_RL_GPS_RXCAP_SIZE];   /**< GPS reciever capability  */
    VOS_UINT8                           aucMsBcCap[TAF_XPDS_RL_GPS_MSBC_CAP_SIZE];   /**< MS band class capability */
    VOS_UINT8                           ucEmerOnlyLcs;     /**< position determination capability for emergency calls only */
    VOS_UINT8                           ucPilDetSensIncl;  /**< pilot detection sensitivity include or not  , range [0..1] */
    VOS_UINT8                           ucPilDetSens;      /**< pilot detection sensitivity */
    VOS_UINT8                           ucMsStatusIncl;    /**< MS status included or not  , range [0..1] */
    VOS_UINT8                           ucPRevInUse;       /**< CDMA signaling protocol in use */
    VOS_UINT8                           ucLocUncHc;        /**< horizontal location uncertainity circular */
    VOS_UINT8                           ucLocAge;          /**< location age */
    VOS_UINT8                           ucReserved2;        /**< padding */
}TAF_XPDS_REVLINK_RSP_EXT_MS_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_SAT_LIST_RECRD_STRU
 *
 * Description : satellite list record
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucInvWeiFact; /**< inverse of weighting factor */
    VOS_UINT8                           ucWeekNum;    /**< GPS week number of sub almanac */
    VOS_UINT8                           ucTOA;        /**< reference time of sub almanac */
    VOS_UINT8                           ucReserved;   /**< padding */
}TAF_XPDS_SAT_LIST_RECRD_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_GPS_COAR_LOC_STRU
 *
 * Description : provide GPS coarse location message. refer 2.2.4.2.14
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimeRef;        /**< time of reference */
    VOS_UINT32                          ulDeltaLatitude;  /**< reference lattitude correction */
    VOS_UINT32                          ulDeltaLongitude; /**< reference longitude correction */
    VOS_UINT32                          ulDeltaAltitude;  /**< reference altitude correction */
    VOS_UINT32                          ulSatsList;       /**< satellites list */
    VOS_UINT8                           ucPrErrThrsh;     /**< pseudorange prediction error threshold */
    VOS_UINT8                           aucReserved[3];   /**< padding */
    TAF_XPDS_SAT_LIST_RECRD_STRU        astSatsRec[TAF_XPDS_RL_SAT_LIST_SIZE];        /**< satellite list record */
}TAF_XPDS_REVLINK_RSP_GPS_COAR_LOC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_MSG_DELAY_MEAS_STRU
 *
 * Description : provide messaging delay measurement message. refer 2.2.4.2.15
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRxTime;        /**< recieve time */
    VOS_UINT8                           ucMsgSeq;        /**< message sequence number */
    VOS_UINT8                           ucRxTxDelayIncl; /**< whether recieve to transmit time delay included or not, range [0..1] */
    VOS_UINT8                           ucRxTxDelay;     /**< recieve to transmit time delay , range [0..7]*/
    VOS_UINT8                           aucReserved[3];  /**< padding */
}TAF_XPDS_REVLINK_RSP_MSG_DELAY_MEAS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_BEAR_MEAS_STRU
 *
 * Description : provide bearing  measurement message. refer 2.2.4.2.16
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBearHor;        /**< bearing horizontal */
    VOS_UINT8                           ucTrueNorth;      /**< whether data is true north or not, range [0..1] */
    VOS_UINT8                           ucHorUncert;      /**< horizontal uncertainity, range [0..7]*/
    VOS_UINT8                           ucVertIncl;       /**< vertical data included or not, range [0..1] */
    VOS_UINT8                           ucBearVerti;      /**< bearing vertical */
    VOS_UINT8                           ucVerUncert;      /**< vertical uncertainity */
    VOS_UINT8                           ucPitchRollCorr;  /**< pitch and roll correction */
    VOS_UINT8                           ucRollAngleIncl;  /**< roll angle included */
    VOS_UINT8                           ucRollAngle;      /**< roll angle */
    VOS_UINT8                           ucRollUncert;     /**< roll uncertainity */
    VOS_UINT8                           aucReserved[2];   /**< padding */
}TAF_XPDS_REVLINK_RSP_BEAR_MEAS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_SERSYS_INFO_STRU
 *
 * Description : provide serving system information message. refer 2.2.4.2.17
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPartNum;           /**< part number in total parts */
    VOS_UINT8                           ucTotalParts;        /**< total number of parts range [1..3] */
    VOS_UINT8                           ucModeInd;           /**< mode indicator, range [1..3]*/
    VOS_UINT8                           ucPilotIdIncl;       /**< pilot id included or not, range [0..1] */
    VOS_UINT16                          usSID;               /**< system indicator */
    VOS_UINT16                          usNID;               /**< network indicator */
    VOS_UINT16                          usBaseID;            /**< base station indicator */
    VOS_UINT8                           ucMscIdIncl;         /**< MSC identification included or not, range [0..1] */
    VOS_UINT8                           ucReserve1;          /**< padding */
    VOS_UINT32                          ulMscId;             /**< MSC identifier */
    VOS_UINT8                           aucSectorId[TAF_XPDS_RL_SECID_SIZE];     /**< sector ID */
    VOS_UINT16                          usBaseIdPn;          /**< Pn sequence offset corrospomding to base station ID */
    VOS_UINT8                           ucExtPilotIdIncl;    /**< extended pilot identification included or not, range [0..1] */
    VOS_UINT8                           ucPilotIdAge;        /**< pilot identification age, range [0..16] */
    VOS_UINT16                          usBaseIdCdmaFreq;    /**< frequency corrosponding to base station ID */
    VOS_UINT8                           ucBaseIdBandCls;     /**< band class corrosponding to base station ID */
    VOS_UINT8                           ucExtPilotIdAge;     /**< extended pilot identification age, range [0..16] */
    VOS_UINT8                           ucActiveSetIncl;     /**< active set included or not, range [0..1] */
    VOS_UINT8                           ucNumActiveSetPn;    /**< number of active set pilots , range [0..7]*/
    VOS_UINT8                           ucNeighListIncl;     /**< neighbour list  included or not, range [0..1] */
    VOS_UINT8                           ucNumOfNeighList;    /**< vnumber of neighbour list , range [0..63] */
    VOS_UINT16                          ausActiveSetPn[TAF_XPDS_RL_ACTIVE_SET_PN_MAX];   /**< active set PN */
    VOS_UINT8                           aucReserve2[2];      /**< padding */
    VOS_UINT16                          ausNeighbrPn[TAF_XPDS_RL_NEIGHBT_PN_MAX];    /**< neighbour list PN */
    VOS_UINT8                           aucReserved3[2];     /**< padding */
    VOS_UINT8                           ucBaseLocIncl;       /**< BS location included or not, range [0..1] */
    VOS_UINT8                           ucCrseLocUnc;        /**< standard deviation of coarse location, range [0..64] */
    VOS_UINT8                           ucBaseLocAge;        /**< BS location information age, range [0..16] */
    VOS_UINT8                           ucReserve4;          /**< padding */
    VOS_UINT32                          ulBaseLatitude;      /**< BS lattitude */
    VOS_UINT32                          ulBaseLongitude;     /**< BS longitude */
    VOS_UINT32                          ulBaseLocSrc;        /**< base location information source, range [0..4] */
}TAF_XPDS_REVLINK_RSP_SERSYS_INFO_STRU;

/*****************************************************************************
 结构名    :TAF_XPDS_DATA_BURST_MSG_STRU
 结构说明  :Data Burst Message 结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBurstType;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           ucNumMsgs;
    VOS_UINT8                           ucNumFields;
    VOS_UINT8                           aucData[255];
    VOS_UINT8                           ucRsv;
}TAF_XPDS_DATA_BURST_MSG_STRU;



/******************************************************************************
 * Name        : TAF_XPDS_CFG_INFO_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_XPDS_INITIAL_TYPE_ENUM_UINT32       enAgpsType; /* SI or NI */
    TAF_XPDS_CALL_TYPE_ENUM_UINT8           enCallType;
    TAF_XPDS_FIX_MODE_ENUM_UINT8            enFixMode;
    VOS_UINT16                              usFixNum;         /**< A value of 1 means is interested in only one fix. A value > 1, multiple fixes with some time in btw the attempts */
    VOS_UINT32                              ulPrecisionTimerLen;
    VOS_UINT32                              ulFixRateTime;    /**< Time, in seconds, between position fix attempts */
    VOS_UINT32                              ulQosHaccuracy;   /**< Horizontal Accuracy, in meters */
    VOS_UINT32                              ulQosVaccuracy;   /**< Vertical Acuracy, in meters */
    VOS_UINT32                              ulQosPerformance; /**< Performance response quality in terms of time, in seconds */
    VOS_UINT32                              ulMpcAddr;
    VOS_UINT32                              ulMpcPort;
    VOS_UINT32                              ulPdeAddr;
    VOS_UINT32                              ulPdePort;
    VOS_UINT16                              usGpsClientId;
    VOS_UINT16                              usApClientId;
    VOS_UINT16                              usUtsClientId;
    NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8     enOmFixRslt;
    VOS_UINT8                               ucIsOmTestMode;
    VOS_UINT8                               ucIsOmTestAborted;
    VOS_UINT8                               aucRsv[3];
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32      enOmTestPdeProcRslt;
}TAF_XPDS_CFG_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_CTRL_INFO_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    AT_XPDS_REPLY_SYNC_TIME_ENUM_UINT8  enSyncTimeActionType;        /**< 1: reply time sync info, 2: reply time sync info and GPS assist data */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOrigSysMode;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCurFixNum;                 /* 跟踪型定位中已定位的次数 */
    VOS_UINT8                           ucIsMpcAuthSucc;             /* MPC是否鉴权成功 */
    VOS_UINT8                           ucPosReportFailNum;          /* 由于MPC建链失败导致Report Fail的次数 */
}TAF_XPDS_CTRL_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_CDMA_AGPS_CTRL_INFO_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enPosProcRslt;
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU                      stProvLocRsp; /* L2 PDE */
    AT_XPDS_GPS_POS_INFO_STRU                               stCagpsPosInfo;    /* L1 */
    TAF_XPDS_REVLINK_RSP_LOC_INFO_STRU                      stRspLocInfo;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU              stPilotInfo;
}TAF_XPDS_PUBLIC_DATA_STRU;


/*****************************************************************************
 结构名    : TAF_XPDS_PDE_PUBLIC_DATA_STRU
 结构说明  : PDE流程相关的公共数据
 日    期  : 2015年08月28日
 作    者  : y00174758
 修改内容  : 新建
*****************************************************************************/
typedef struct
{
    TAF_XPDS_PD_MSG_HEADER_STRU                             stFwdPdMsgHeader;

    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU               stRspPrmInfo;           /* Get Info From GPS, And need to send to PDE */

    TAF_XPDS_FWDLINK_REQ_RESP_FLAG_STRU                     stReqRespFlag;
    TAF_XPDS_FWDLINK_REQ_CANCEL_STRU                        stFwdReqCancel;         /* FWDLINK REQ CANCEL req from the BS */
    TAF_XPDS_FWDLINK_REQ_PILOT_PHASE_MEAS_STRU              stFwdReqPilotPhaseMeas; /* Pilot phase measurement req from BS */
    TAF_XPDS_FWDLINK_REQ_PSUERANGE_MEAS_STRU                stFwdReqPsuRangeMeas;   /* Psuedo range meas req */
    TAF_XPDS_FWDLINK_REQ_LOC_RESP_STRU                      stFwdReqLocResp;        /* Location response req from BS */

    TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU                stProvAcqAssist;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU                       stProvGpsAlm;           /* GPS Almanac from the BS */
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU                       stProvGpsEph;           /* GPS ephimeries from the BS */

    VOS_UINT8                                               ucPpmTimerExpireFlag;
    VOS_UINT8                                               ucIsReceivedGpsPrmInfo;

    VOS_UINT8                                               ucIsGpsEphDataFinished;
    VOS_UINT8                                               ucIsGpsAlmDataFinished;

    TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8                  enPdeSessionStatus;
    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8            enPdeSessionTriggerType;

    VOS_UINT8                                               ucSessTagInRsvPdMsgHeader;

    VOS_UINT8                                               aucRsv[1];
}TAF_XPDS_PDE_PUBLIC_DATA_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MPC_CTX_STRU
 结构说明  : MPC流程相关的公共数据
 日    期  : 2015年08月28日
 作    者  : C00299064
 修改内容  : 新建
*****************************************************************************/
typedef struct
{
    TAF_XPDS_MPC_START_POS_RSP_STRU                    stStartPosRsp;
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU                   stPosReportRsp;
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU                     stXsmsPosReq;
    VOS_UINT8                                          ucCurCorrelationId;
    VOS_UINT8                                          ucExpectCorrelationId;
    VOS_UINT8                                          aucReserved[2];
    TAF_XSMS_ADDR_STRU                                 stXsmsAddr;
}TAF_XPDS_MPC_CTX_STRU;


typedef struct
{
    /**************************************************************************
                        XPDS状态机状态及其状态栈
     **************************************************************************/
    TAF_XPDS_FSM_CTX_STRU               stCurFsm;                               /* 状态机当前的状态机数组 */

    TAF_XPDS_FSM_STACK_STRU             stFsmStack;                             /* 状态机的状态机栈数组   */

    TAF_XPDS_INT_MSG_QUEUE_STRU         stIntMsgQueue;                          /* 内部消息队列 */

    TAF_XPDS_TIMER_CTX_STRU             astTimerCtx[TAF_XPDS_CTX_MAX_TIMER_NUM];/* XPDS定时器相关上下文 */

    TAF_XPDS_CFG_INFO_STRU              stCagpsCfg;

    TAF_XPDS_CTRL_INFO_STRU             stCtrlInfo;

    TAF_XPDS_PUBLIC_DATA_STRU           stPublicData;

    TAF_XPDS_CAGPS_UPLINK_CTX_STRU      stUplinkCtx;                            /* L2 用户面链路上下文 */

    TAF_XPDS_PDE_PUBLIC_DATA_STRU       stPdePubData;                           /* PDE流程相关数据 */

    TAF_XPDS_MPC_CTX_STRU               stMpcCtx;                               /* MPC相关的全局变量 */
}TAF_XPDS_CONTEXT_STRU;

/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/
extern     TAF_XPDS_CONTEXT_STRU            g_stTafXpdsCtx;

#define TAF_XPDS_GetFwdlinkMsgFlagAddr()      (&(g_stTafXpdsCtx.stPdePubData.stReqRespFlag))

/* Check If forward Msg contains req or resp*/
#define TAF_XPDS_GetReqLocRespFlag()                   (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqLocResp)
#define TAF_XPDS_GetReqMsInfoFlag()                    (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqMsInfo)
#define TAF_XPDS_GetReqPsuRangMeasFlag()               (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqPsuRangMeas)
#define TAF_XPDS_GetReqPilotPhaseMeasFlag()            (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqPilotMeas)
#define TAF_XPDS_GetRespGpsIonInEphimFlag()            (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_RespGpsIonInEphim)

#define TAF_XPDS_SetReqLocRespFlag(bFlag)              (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqLocResp     = (bFlag))
#define TAF_XPDS_SetReqMsInfoFlag(bFlag)               (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqMsInfo      = (bFlag))
#define TAF_XPDS_SetReqPsuRangMeasFlag(bFlag)          (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqPsuRangMeas = (bFlag))
#define TAF_XPDS_SetReqPilotPhaseMeasFlag(bFlag)       (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqPilotMeas   = (bFlag))
#define TAF_XPDS_SetRespGpsIonInEphimFlag(bFlag)       (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_RespGpsIonInEphim = (bFlag))


#define TAF_XPDS_GetReqGenLocMeasFlag()                (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqGenLocMeas)
#define TAF_XPDS_GetReqExtLocRespFlag()                (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqExtLocResp)
#define TAF_XPDS_GetReqExtCancelReqFlag()              (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqExtCancel)
#define TAF_XPDS_GetReqGpsCoarseLocReqFlag()           (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqGpsCoarseLoc)
#define TAF_XPDS_GetReqMsgDelayMeasReqFlag()           (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqMsgDelayMeas)
#define TAF_XPDS_GetReqBearingMeasReqFlag()            (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqBearingMeas)
#define TAF_XPDS_GetReqServSysInfoReqFlag()            (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqServSysInfo)
#define TAF_XPDS_GetReqExtMsInfoFlag()                 (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqExtMsInfo)

#define TAF_XPDS_SetReqGenLocMeasFlag(bFlag)           (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqGenLocMeas    = (bFlag))
#define TAF_XPDS_SetReqBearingMeasReqFlag(bFlag)       (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqBearingMeas   = (bFlag))
#define TAF_XPDS_SetReqMsgDelayMeasReqFlag(bFlag)      (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqMsgDelayMeas  = (bFlag))
#define TAF_XPDS_SetReqServSysInfoReqFlag(bFlag)       (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqServSysInfo   = (bFlag))
#define TAF_XPDS_SetReqExtLocRespFlag(bFlag)           (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqExtLocResp    = (bFlag))
#define TAF_XPDS_SetReqExtCancelReqFlag(bFlag)         (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqExtCancel     = (bFlag))
#define TAF_XPDS_SetReqGpsCoarseLocReqFlag(bFlag)      (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqGpsCoarseLoc  = (bFlag))
#define TAF_XPDS_SetReqExtMsInfoFlag(bFlag)            (g_stTafXpdsCtx.stPdePubData.stReqRespFlag.OP_ReqExtMsInfo     = (bFlag))





/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
VOS_VOID TAF_XPDS_InitCurrFsmCtx(
    TAF_XPDS_FSM_CTX_STRU              *pstCurrFsmCtx
);

VOS_VOID TAF_XPDS_InitFsmStackCtx(
    TAF_XPDS_FSM_STACK_STRU            *pstFsmStack
);

VOS_VOID TAF_XPDS_InitPosCtx(VOS_VOID);

VOS_VOID TAF_XPDS_InitCtx(VOS_VOID);

VOS_VOID TAF_XPDS_InitFsmCtx_L1Main(VOS_VOID);

VOS_VOID  TAF_XPDS_LoadSubFsm(
    TAF_XPDS_FSM_ID_ENUM_UINT32         enFsmId,
    TAF_XPDS_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID TAF_XPDS_PushFsm(
    TAF_XPDS_FSM_STACK_STRU            *pstFsmStack,
    TAF_XPDS_FSM_CTX_STRU              *pstNewFsm
);

VOS_VOID TAF_XPDS_PopFsm(VOS_VOID);

VOS_VOID TAF_XPDS_InitFsmL2(
    TAF_XPDS_FSM_ID_ENUM_UINT32         enFsmId
);

VOS_VOID TAF_XPDS_QuitFsmL2(VOS_VOID);

TAF_XPDS_CONTEXT_STRU* TAF_XPDS_GetCtxAddr(VOS_VOID);

TAF_XPDS_FSM_CTX_STRU* TAF_XPDS_GetCurFsmAddr(VOS_VOID);

TAF_XPDS_FSM_STACK_STRU* TAF_XPDS_GetFsmStackAddr(VOS_VOID);

TAF_FSM_DESC_STRU* TAF_XPDS_GetCurFsmDesc(VOS_VOID);

TAF_XPDS_MSG_STRU* TAF_XPDS_GetCurrFsmEntryMsgAddr(VOS_VOID);

TAF_XPDS_FSM_ID_ENUM_UINT32 TAF_XPDS_GetCurrFsmId(VOS_VOID);

VOS_UINT32 TAF_XPDS_GetFsmTopState(VOS_VOID);

VOS_UINT16  TAF_XPDS_GetFsmStackDepth(VOS_VOID);

VOS_VOID TAF_XPDS_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

VOS_VOID  TAF_XPDS_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);

VOS_UINT16  TAF_XPDS_GetFsmStackPopFlg(VOS_VOID);

VOS_VOID TAF_XPDS_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_XPDS_INT_MSG_QUEUE_STRU* TAF_XPDS_GetIntMsgQueueAddr(VOS_VOID);

VOS_VOID TAF_XPDS_InitInternalBuffer(
    TAF_XPDS_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

VOS_VOID  TAF_XPDS_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

VOS_UINT8 *TAF_XPDS_GetNextIntMsg(VOS_VOID);

VOS_UINT8 TAF_XPDS_GetIntMsgNum(VOS_VOID);

AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32 TAF_XPDS_GetDataCallStatus(VOS_VOID);

VOS_VOID TAF_XPDS_SetDataCallStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enDataCallState
);

TAF_XPDS_TIMER_CTX_STRU* TAF_XPDS_GetTimerCtxAddr(VOS_VOID);

TAF_XPDS_INITIAL_TYPE_ENUM_UINT32 TAF_XPDS_GetCgpsInitialType(VOS_VOID);

TAF_XPDS_FIX_MODE_ENUM_UINT8 TAF_XPDS_GetAgpsFixMode(VOS_VOID);

VOS_VOID TAF_XPDS_SetAgpsFixMode(TAF_XPDS_FIX_MODE_ENUM_UINT8 enFixMode);

TAF_XPDS_CFG_INFO_STRU* TAF_XPDS_GetAgpsCfg(VOS_VOID);

TAF_XPDS_CTRL_INFO_STRU* TAF_XPDS_GetCtrlInfoAddr(VOS_VOID);

TAF_XPDS_PUBLIC_DATA_STRU* TAF_XPDS_GetPublicDataAddr(VOS_VOID);

TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetPosProcRslt(VOS_VOID);

VOS_VOID TAF_XPDS_SetPosProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPosProcRslt
);

TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8 TAF_XPDS_GetUpLinkStatus(VOS_VOID);

VOS_VOID TAF_XPDS_UpdateUpLinkStatus(VOS_VOID);

AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetMpcServerStatus(VOS_VOID);

AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetPdeServerStatus(VOS_VOID);

VOS_VOID TAF_XPDS_SetMpcServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enMpcServerStatus
);

VOS_VOID TAF_XPDS_SetPdeServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enPdeServerStatus
);

VOS_VOID TAF_XPDS_InitDefaultCfgInfo(VOS_VOID);

VOS_VOID TAF_XPDS_InitProvGpsEph(
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph
);

VOS_VOID TAF_XPDS_InitProvGpsAlm(
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU  *pstProvAlm
);

VOS_VOID TAF_XPDS_SetFwdPdMsgHeader(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
);

VOS_UINT8  TAF_XPDS_GetCorrelationId(VOS_VOID);

extern VOS_VOID TAF_XPDS_SetTimeStamp(
    TAF_XPDS_TIME_STAMP_STRU            *pstTimeStamp
);

TAF_XPDS_PDE_PUBLIC_DATA_STRU * TAF_XPDS_GetPdePublicData(VOS_VOID);

VOS_VOID TAF_XPDS_InitPdePublicDataTaskInit(VOS_VOID);

VOS_VOID TAF_XPDS_InitPdePublicDataPdeInit(VOS_VOID);

VOS_VOID TAF_XPDS_SetUplinkAbortScene(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enUpLinkAbortScene
);

TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetUpLinkAbortScene(VOS_VOID);

VOS_VOID TAF_XPDS_SetGpsEphDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
);

VOS_UINT8 TAF_XPDS_GetGpsEphDataFinishedFlag(VOS_VOID);

VOS_VOID TAF_XPDS_SetGpsAlmDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
);

VOS_UINT8 TAF_XPDS_GetGpsAlmDataFinishedFlag(VOS_VOID);

VOS_VOID TAF_XPDS_SetPdeSessionStatus(
    TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8                  enPdeSessionStatus
);

TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8 TAF_XPDS_GetPdeSessionStatus(VOS_VOID);

VOS_VOID TAF_XPDS_SetPdeSessionTriggerType(
    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8            enPdeSessionTriggerType
);

TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8 TAF_XPDS_GetPdeSessionTriggerType(VOS_VOID);

VOS_VOID TAF_XPDS_SetSessTagInRsvPdMsgHeader(VOS_UINT8 ucSessTag);

VOS_UINT8 TAF_XPDS_GetSessTagInRsvPdMsgHeader(VOS_VOID);

VOS_VOID TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader(VOS_VOID);

VOS_UINT32 TAF_XPDS_GetPrmTimerLimitLen(VOS_VOID);

VOS_UINT32 TAF_XPDS_GetPilotPhaseTimerLimitLen(VOS_VOID);

VOS_UINT16 TAF_XPDS_GetGpsClientId(VOS_VOID);

VOS_UINT16 TAF_XPDS_GetApClientId(VOS_VOID);

VOS_UINT16 TAF_XPDS_GetUtsClientId(VOS_VOID);

VOS_VOID TAF_XPDS_SetGpsClientId(
    VOS_UINT16                          usClientId
);

VOS_VOID TAF_XPDS_SetApClientId(
    VOS_UINT16                          usClientId
);

VOS_VOID TAF_XPDS_SetUtsClientId(
    VOS_UINT16                          usClientId
);


TAF_XPDS_MPC_CTX_STRU* TAF_XPDS_GetMpcCtxAddr(VOS_VOID);

TAF_XPDS_CAGPS_UPLINK_CTX_STRU* TAF_XPDS_GetUpLinkCtxAddr(VOS_VOID);


VOS_VOID TAF_XPDS_SetOmTestFlag(VOS_UINT8 ucIsOmTestMode);

VOS_UINT8 TAF_XPDS_GetOmTestFlag(VOS_VOID);

VOS_VOID TAF_XPDS_SetOmFixRslt(VOS_UINT8 enFixRslt);

NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 TAF_XPDS_GetOmFixRslt(VOS_VOID);

VOS_VOID TAF_XPDS_SetOmTestAbortFlag(VOS_UINT8 isAborted);

VOS_UINT8 TAF_XPDS_GetOmTestAbortFlag(VOS_VOID);

VOS_VOID TAF_XPDS_SetOmTestPdeProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPdeProcRslt
);

TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetOmTestPdeProcRslt(VOS_VOID);

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

#endif


