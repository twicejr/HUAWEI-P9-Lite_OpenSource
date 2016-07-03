
#ifndef _MMA_MSCC_INTERFACE_H_
#define _MMA_MSCC_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "TafAppMma.h"
#include "NasMsccPifInterface.h"
#include "TafMmaInterface.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MSCC_MMA_SECOND_COLORCODE_MAX_LENGTH                ( 5 )
#define MSCC_MMA_SUBNET_ID_MAX_LENGTH                       ( 16 )

#define     MSCC_MMA_CAS_STA_INVALID_SUBSTA                 (0xFF)

#define     MSCC_MMA_MAX_SRCHED_LAI_NUM  (18)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/



enum MSCC_MMA_HRPD_SERVICE_STATUS_ENUM
{
    MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE         = 0,              /* HRPD is in normal service */
    MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE             = 1,              /* HRPD has no service */
    MSCC_MMA_HRPD_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32;


enum MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM
{
    MSCC_MMA_HRPD_ACQUIRED_RESULT_SUCC        = 0x00000000,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_FAIL        = 0x00000001,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_ABORTED     = 0x00000002,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_BUTT
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM_UINT32;


enum MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM
{
    MSCC_MMA_SESSION_RELEASE_TYPE_0     = 0x00,
    MSCC_MMA_SESSION_RELEASE_TYPE_A     = 0x01,
    MSCC_MMA_SESSION_RELEASE_TYPE_BUTT  = 0x02
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32;


enum MSCC_MMA_ACQ_SYS_TYPE_ENUM
{
    MSCC_MMA_ACQ_SYS_TYPE_3GPP,                                             /* GUL模式下3GPP下的搜网开始或结束指示的系统类型(包含LTE ONLY)*/
    MSCC_MMA_ACQ_SYS_TYPE_1X,                                               /* 1X的捕获开始或结束指示的系统类型 */
    MSCC_MMA_ACQ_SYS_TYPE_DO,                                               /* CL模式下且不支持LTE时,DO的捕获开始或结束指示的系统类型 */
    MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,                                           /* CL模式下支持LTE时,DO或LTE捕获开始或结束指示的系统类型 */
    MSCC_MMA_ACQ_SYS_TYPE_BUTT
};
typedef VOS_UINT32 MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32;


enum MMA_MSCC_HANDSET_INFO_TYPE_ENUM
{
    MMA_MSCC_HANDSET_INFO_TYPE_STATE,
    MMA_MSCC_HANDSET_INFO_TYPE_HVERSION,

    MMA_MSCC_HANDSET_INFO_TYPE_BUTT
};
typedef VOS_UINT32 MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8
 *
 * Description : .
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_P_REV_ENUM
{
    MSCC_MMA_1X_CAS_P_REV_JST_008               = 0x01,
    MSCC_MMA_1X_CAS_P_REV_IS_95                 = 0x02,
    MSCC_MMA_1X_CAS_P_REV_IS_95A                = 0x03,
    MSCC_MMA_1X_CAS_P_REV_IS_95B_CUSTOM         = 0x04,
    MSCC_MMA_1X_CAS_P_REV_IS_95B                = 0x05,
    MSCC_MMA_1X_CAS_P_REV_IS_2000               = 0x06,
    MSCC_MMA_1X_CAS_P_REV_IS_2000A              = 0x07,

    MSCC_MMA_1X_CAS_P_REV_ENUM_BUTT
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_STATE_ENUM_UINT8
 *
 * Description : When MS is in the different state, MS should perform
 * different actions.
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_STATE_ENUM
{
    MSCC_MMA_1X_CAS_INIT_STATE          = 0x00,
    MSCC_MMA_1X_CAS_IDLE_STATE          = 0x01,
    MSCC_MMA_1X_CAS_ACCESS_STATE        = 0x02,
    MSCC_MMA_1X_CAS_TCH_STATE           = 0x03,
    MSCC_MMA_1X_CAS_NO_SERVICE_STATE    = 0x04,
    MSCC_MMA_1X_CAS_STATE_ENUM_BUTT     = 0x05
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_STATE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_SUB_STATE_ENUM_UINT8
 *
 * Description : .
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_SUB_STATE_ENUM
{
    MSCC_MMA_1X_CAS_SUB_STATE_NULL                          = 0x00,
    MSCC_MMA_1X_CAS_INIT_DETERM_SUB_STATE                   = 0x01,
    MSCC_MMA_1X_CAS_PILOT_CH_ACQ_SUB_STATE                  = 0x02,
    MSCC_MMA_1X_CAS_SYNC_CH_ACQ_SUB_STATE                   = 0x03,
    MSCC_MMA_1X_CAS_TIMING_CHNG_SUB_STATE                   = 0x04,
    MSCC_MMA_1X_CAS_IDLE_SUB_STATE                          = 0x10,
    MSCC_MMA_1X_CAS_UPDATE_OVERHEAD_SUB_STATE               = 0x20,
    MSCC_MMA_1X_CAS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE      = 0x21,
    MSCC_MMA_1X_CAS_PAG_RESP_SUB_STATE                      = 0x22,
    MSCC_MMA_1X_CAS_MOB_STATION_ORDR_RESP_SUB_STATE         = 0x23,
    MSCC_MMA_1X_CAS_REG_ACCESS_SUB_STATE                    = 0x24,
    MSCC_MMA_1X_CAS_MOB_STATION_MSG_TRANS_SUB_STATE         = 0x25,
    MSCC_MMA_1X_CAS_TCH_INIT_SUB_STATE                      = 0x30,
    MSCC_MMA_1X_CAS_REL_SUB_STATE                           = 0x31,
    MSCC_MMA_1X_CAS_WAIT_FOR_SERVICE_SUB_STATE              = 0x40,
    MSCC_MMA_1X_CAS_SUB_STATE_ENUM_BUTT                     = 0x41
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_SUB_STATE_ENUM_UINT8;


enum MSCC_MMA_1X_CALL_STATE_ENUM
{
    MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ORDER,
    MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ANSWER,
    MSCC_MMA_1X_CALL_STATE_CONVERSATION,

    MSCC_MMA_1X_CALL_STATE_BUTT
};
typedef VOS_UINT8 MSCC_MMA_1X_CALL_STATE_ENUM_UINT8;






enum  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM
{
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_DO_SUCC,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_LTE_SUCC,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT
};
typedef VOS_UINT32  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32;



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

typedef  NAS_MSCC_PIF_RAT_PRIO_STRU MMA_MSCC_PLMN_RAT_PRIO_STRU;


typedef  NAS_MSCC_PIF_PLMN_ID_STRU MMA_MSCC_PLMN_ID_STRU;


typedef NAS_MSCC_PIF_3GPP2_RAT_STRU MMA_MSCC_3GPP2_RAT_STRU;


typedef NAS_MSCC_PIF_EPLMN_INFO_STRU MMA_MSCC_EPLMN_INFO_STRU;



typedef NAS_MSCC_PIF_CAMP_CELL_INFO_STRU MMA_MSCC_CAMP_CELL_INFO_STRU;


typedef NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU MMA_MSCC_OPERATOR_NAME_INFO_STRU;


typedef NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU MMA_MSCC_UE_SUPPORT_FREQ_BAND_STRU;


typedef NAS_MSCC_PIF_RSSI_VALUE_STRU MMA_MSCC_RSSI_VALUE_STRU;


typedef NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU MMA_MSCC_SCELL_MEAS_TYPE_STRU;


typedef NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN MMA_MSCC_SCELL_MEAS_REPORT_TYPE_UN;


typedef NAS_MSCC_PIF_RSSI_IND_STRU MSCC_MMA_RSSI_IND_STRU;


typedef NAS_MSCC_PIF_CQI_INFO_STRU MSCC_MMA_CQI_INFO_STRU;

typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU MMA_MSCC_LMM_CELL_SIGN_INFO_STRU;

typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /*_H2ASN_Skip*//* 消息头                                   */
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus;
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8              enRegDomain;        /* 在原接口新增开机允许注册的服务域 */
    NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8                     enRegCtrl;
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stRatPrio;
    VOS_UINT8                                               aucImsi[NAS_MAX_IMSI_LENGTH];
    NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8                       enCallMode;
    VOS_UINT8                                               ucIsCardChanged;    /* 卡的ICCID是否发生变化的标识 */
    VOS_UINT8                                               aucReserved[1];
}MMA_MSCC_START_REQ_STRU;


typedef NAS_MSCC_PIF_START_CNF_STRU MSCC_MMA_START_CNF_STRU;


typedef NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU MSCC_MMA_3GPP_SYS_INFO_IND_STRU;


typedef NAS_MSCC_PIF_REG_RESULT_IND_STRU MSCC_MMA_REG_RESULT_IND_STRU;


typedef NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU MSCC_MMA_USIM_AUTH_FAIL_IND_STRU;


typedef NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU MSCC_MMA_SERVICE_STATUS_IND_STRU;


typedef NAS_MSCC_PIF_MM_INFO_IND_STRU MSCC_MMA_MM_INFO_IND_STRU;


typedef NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU MMA_MSCC_SIGN_REPORT_REQ_STRU;


typedef NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU MMA_MSCC_MODE_CHANGE_REQ_STRU;


typedef NAS_MSCC_PIF_ATTACH_REQ_STRU MMA_MSCC_ATTACH_REQ_STRU;


typedef NAS_MSCC_PIF_ATTACH_CNF_STRU MSCC_MMA_ATTACH_CNF_STRU;


typedef NAS_MSCC_PIF_DETACH_REQ_STRU MMA_MSCC_DETACH_REQ_STRU;


typedef NAS_MSCC_PIF_DETACH_CNF_STRU MSCC_MMA_DETACH_CNF_STRU;


typedef NAS_MSCC_PIF_DETACH_IND_STRU MSCC_MMA_DETACH_IND_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_REQ_STRU MMA_MSCC_PLMN_LIST_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_CNF_STRU MSCC_MMA_PLMN_LIST_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_REJ_STRU MSCC_MMA_PLMN_LIST_REJ_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU MMA_MSCC_PLMN_USER_RESEL_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU MMA_MSCC_PLMN_SPECIAL_REQ_STRU;



typedef NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU MSCC_MMA_COVERAGE_AREA_IND_STRU;


typedef NAS_MSCC_PIF_POWER_OFF_REQ_STRU MMA_MSCC_POWER_OFF_REQ_STRU;


typedef NAS_MSCC_PIF_POWER_OFF_CNF_STRU MSCC_MMA_POWER_OFF_CNF_STRU;


typedef NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU;


typedef NAS_MSCC_PIF_SYSTEM_ACQUIRE_CNF_STRU MSCC_MMA_SYSTEM_ACQUIRE_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU MSCC_MMA_PLMN_RESEL_CNF_STRU;


typedef NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU MSCC_MMA_DATATRAN_ATTRI_IND_STRU;


typedef NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU MMA_MSCC_SYS_CFG_SET_REQ_STRU;


typedef NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU MSCC_MMA_SYS_CFG_SET_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MMA_MSCC_PLMN_SEARCH_REQ_STRU;



typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
}MSCC_MMA_SYSTEM_ACQUIRE_IND_STRU;



typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32      enAcqRsltType;    /* 指示系统类型为DO_LTE时系统捕获时,捕获结果类型是失败,HRPD成功还是LTE成功 */
}MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU;





typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU;


typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;


typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;


typedef NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU;


typedef NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU;


typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU;


typedef NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU MSCC_MMA_AC_INFO_CHANGE_IND_STRU;


typedef NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU;


typedef NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU MMA_MSCC_UPDATE_UPLMN_NTF_STRU;


typedef NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU MMA_MSCC_EOPLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU MSCC_MMA_EOPLMN_SET_CNF_STRU;


typedef NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU MSCC_MMA_EOPLMN_SET_ABORT_STRU;


typedef NAS_MSCC_PIF_NET_SCAN_REQ_STRU MMA_MSCC_NET_SCAN_REQ_STRU;


typedef NAS_MSCC_PIF_NET_SCAN_INFO_STRU MSCC_MMA_NET_SCAN_INFO_STRU;


typedef NAS_MSCC_PIF_NET_SCAN_CNF_STRU MSCC_MMA_NET_SCAN_CNF_STRU;


typedef NAS_MSCC_PIF_SERV_REJ_IND_STRU MSCC_MMA_SERV_REJ_IND_STRU;



typedef NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU MMA_MSCC_ABORT_NET_SCAN_REQ_STRU;


typedef NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU MSCC_MMA_ABORT_NET_SCAN_CNF_STRU;


typedef NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU;


typedef NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU MSCC_MMA_CAMP_ON_IND_STRU_STRU;


typedef NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU;


typedef NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;


typedef NAS_MSCC_PIF_TDS_NCELL_INFO_STRU MMA_MSCC_TDS_NCELL_INFO_STRU;


typedef NAS_MSCC_PIF_LTE_NCELL_INFO_STRU MMA_MSCC_LTE_NCELL_INFO_STRU;


typedef NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU MMA_MSCC_NCELL_INFO_NOTIFY_STRU;


typedef NAS_MSCC_PIF_EPLMN_INFO_IND_STRU MSCC_MMA_EPLMN_INFO_IND_STRU;


typedef NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU;


typedef NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU MMA_MSCC_PS_TRANSFER_NOTIFY_STRU;


typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MMA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU;


typedef NAS_MSCC_PIF_ACQ_REQ_STRU MMA_MSCC_ACQ_REQ_STRU;


typedef NAS_MSCC_PIF_ACQ_CNF_STRU MSCC_MMA_ACQ_CNF_STRU;


typedef NAS_MSCC_PIF_REG_CELL_INFO_STRU MMA_MSCC_REG_CELL_INFO_STRU;


typedef NAS_MSCC_PIF_REG_REQ_STRU MMA_MSCC_REG_REQ_STRU;


typedef NAS_MSCC_PIF_REG_CNF_STRU MSCC_MMA_REG_CNF_STRU;


typedef NAS_MSCC_PIF_POWER_SAVE_REQ_STRU MMA_MSCC_POWER_SAVE_REQ_STRU;


typedef NAS_MSCC_PIF_POWER_SAVE_CNF_STRU MSCC_MMA_POWER_SAVE_CNF_STRU;


typedef  NAS_MSCC_PIF_ACQ_CNF_STRU MSCC_MMA_ACQ_IND_STRU;


typedef  NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU;


typedef NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU MSCC_MMA_RF_AVAILABLE_IND_STRU;


typedef NAS_MSCC_PIF_SRV_ACQ_REQ_STRU MMA_MSCC_SRV_ACQ_REQ_STRU;


typedef NAS_MSCC_PIF_SRV_ACQ_CNF_STRU MSCC_MMA_SRV_ACQ_CNF_STRU;


typedef NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU;


typedef NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU MMA_MSCC_END_SESSION_NOTIFY_STRU;


typedef NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU;


typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MSCC_MMA_IMS_VOICE_CAP_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enSrvSta;
    VOS_UINT8                                               ucIsNewSession;
    VOS_UINT8                                               ucIsEhrpdSupport;   /* 表示当前Session类型是HRPD或EHRPD，当enSrvSta为NORMAL_SERVICE时有效 */
    VOS_UINT8                                               aucReserved[2];
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType;
} MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /*_H2ASN_Skip*//* 消息头                                   */
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT32                                  ulMcc;
    VOS_UINT8                                   ucUATIColorCode;
    VOS_UINT8                                   ucSubNetMask;
    VOS_UINT8                                   ucSecondaryColorCodeCount;
    VOS_UINT8                                   aucSecondaryColorCode[MSCC_MMA_SECOND_COLORCODE_MAX_LENGTH];
    VOS_UINT8                                   aucSectorId[MSCC_MMA_SUBNET_ID_MAX_LENGTH];
    VOS_INT32                                   lLongitude;
    VOS_INT32                                   lLatitude;
    VOS_UINT32                                  ulSector24;
} MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM_UINT32                  enSysAcqRslt;
} MSCC_MMA_HRPD_SYS_ACQ_CNF_STRU;



typedef NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU;





typedef NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU;


typedef NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU;



typedef NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU;


typedef NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU MMA_MSCC_CDMACSQ_SET_REQ_STRU;


typedef NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU MMA_MSCC_CFREQ_LOCK_NTF_STRU;


typedef NAS_MSCC_PIF_1X_SYSTEM_TIME_IND_STRU MSCC_MMA_1X_SYSTEM_TIME_IND_STRU;


typedef NAS_MSCC_PIF_1X_SYSTEM_SERVICE_INFO_IND_STRU MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU;


typedef NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU MSCC_MMA_CDMACSQ_SET_CNF_STRU;


typedef NAS_MSCC_PIF_CDMACSQ_IND_STRU MSCC_MMA_CDMACSQ_IND_STRU;





typedef NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU MMA_MSCC_CFPLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU MMA_MSCC_CFPLMN_QUERY_REQ_STRU;


typedef NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU MSCC_MMA_CFPLMN_SET_CNF_STRU;


typedef NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU MSCC_MMA_CFPLMN_QUERY_CNF_STRU;


typedef NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8 MSCC_MMA_CFPLMN_OPERATE_TYPE_ENUM_UINT8;



typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU;


typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU;


typedef NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU MMA_MSCC_PREF_PLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU MSCC_MMA_PREF_PLMN_SET_CNF_STRU;


typedef NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU;


typedef NAS_MSCC_PIF_IMS_START_REQ_STRU MMA_MSCC_IMS_START_REQ_STRU;


typedef NAS_MSCC_PIF_IMS_START_CNF_STRU MSCC_MMA_IMS_START_CNF_STRU;


typedef NAS_MSCC_PIF_IMS_STOP_REQ_STRU MMA_MSCC_IMS_STOP_REQ_STRU;


typedef NAS_MSCC_PIF_IMS_STOP_CNF_STRU MSCC_MMA_IMS_STOP_CNF_STRU;


typedef NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU MSCC_MMA_IMS_SWITCH_STATE_IND_STRU;




/** ****************************************************************************
 * Name        : MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32   enSysType;
}MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU;




typedef NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU MMA_MSCC_PS_RAT_TYPE_NTF_STRU;


typedef NAS_MSCC_PIF_AUTO_RESEL_SET_STRU MMA_MSCC_AUTO_RESEL_SET_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_REJ_STRU MSCC_MMA_CSG_LIST_REJ_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU MSCC_MMA_CSG_LIST_ABORT_CNF_STRU;

typedef NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU MMA_MSCC_CSG_LIST_ABORT_REQ_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;                              /* _H2ASN_Skip */
    MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32                  enInfoType;
}MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32                  enInfoType;         /* 请求的信息类型 */
    VOS_UINT8                                               ucCasState;         /* 主状态 */
    VOS_UINT8                                               ucCasSubSta;        /* 子状态 */
    MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8                        enHighVer;          /* cas上报的所支持的最高的版本 */
    VOS_UINT8                                               aucRsv[1];
}MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMA_UE_STATE_IND_STRU
 * Description : UE STATE indication
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    MSCC_PIF_MSG_TYPE_ENUM_UINT32                           enMsgId;    /* _H2ASN_Skip */
    VOS_UINT8                                               ucUeMainState;
    VOS_UINT8                                               ucUeSubState;
    VOS_UINT8                                               aucReserve[2];
}MSCC_MMA_UE_STATE_IND_STRU;



typedef NAS_MSCC_PIF_GET_GEO_REQ_STRU MMA_MSCC_GET_GEO_REQ_STRU;


typedef NAS_MSCC_PIF_GET_GEO_CNF_STRU MSCC_MMA_GET_GEO_CNF_STRU;


typedef NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU MMA_MSCC_STOP_GET_GEO_REQ_STRU;


typedef NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU MSCC_MMA_STOP_GET_GEO_CNF_STRU;



typedef NAS_MSCC_PIF_DPLMN_SET_REQ_STRU MMA_MSCC_DPLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_DPLMN_SET_CNF_STRU MSCC_MMA_DPLMN_SET_CNF_STRU;



typedef NAS_MSCC_PIF_SID_NID_IND_STRU MSCC_MMA_1X_SID_NID_IND_STRU;


typedef NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU MMA_MSCC_QUIT_CALL_BACK_NTF_STRU;


typedef NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU MMA_MSCC_SET_CSIDLIST_REQ_STRU;

typedef NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU MSCC_MMA_SET_CSIDLIST_CNF_STRU;


typedef NAS_MSCC_PIF_SYNC_SERVICE_AVAILABLE_IND_STRU MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU;



typedef NAS_MSCC_PIF_EMC_CALLBACK_IND_STRU MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU;

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
    MSCC_PIF_MSG_TYPE_ENUM_UINT32       enMsgID;    /*_H2ASN_MsgChoice_Export MMA_MSCC_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMA_MSCC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MMA_MSCC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMA_MSCC_MSG_DATA    stMsgData;
}MmaMsccInterface_MSG;


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

#endif
