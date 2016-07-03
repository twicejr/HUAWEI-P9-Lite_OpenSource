
#ifndef _MSCC_MMC_INTERFACE_H_
#define _MSCC_MMC_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "NasCommDef.h"
#include "NasMsccPifInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MSCC_MMC_HRPD_SUBNET_MAX_LEN             (16)
#define MSCC_MMC_BG_HRPD_MAX_SYS_NUM             (16)

#define MSCC_MMC_VERSION_LEN            (9)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : MSCC_MMC_BG_SRCH_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : BG搜索结果
*****************************************************************************/
enum MSCC_MMC_BG_SRCH_RESULT_ENUM
{
    MSCC_MMC_BG_SRCH_RESULT_SUCCESS            = 0,                /* 指定的PLMN搜索成功 */
    MSCC_MMC_BG_SRCH_RESULT_FAIL               = 1,                /* 实际发起了搜网，但是搜索失败 */
    MSCC_MMC_BG_SRCH_RESULT_ABORT              = 2,                /* 没有发起搜网，因为当前状态不允许，搜索被终止 */
    MSCC_MMC_BG_SRCH_RESULT_BUTT
};
typedef VOS_UINT32  MSCC_MMC_BG_SRCH_RESULT_ENUM_UINT32;




enum MSCC_MMC_IMS_VOICE_CAPABILITY_ENUM
{
    MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL = 0,
    MSCC_MMC_IMS_VOICE_CAPABILITY_AVAIL     = 1,
    MSCC_MMC_IMS_VOICE_CAPABILITY_BUTT
};
typedef VOS_UINT8 MSCC_MMC_IMS_VOICE_CAPABILITY_ENUM_UINT8;



enum MSCC_MMC_PERSISTENT_BEARER_STATE_ENUM
{
    MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST = 0,
    MSCC_MMC_PERSISTENT_BEARER_STATE_EXIST     = 1,
    MSCC_MMC_PERSISTENT_BEARER_STATE_BUTT
};
typedef VOS_UINT8 MSCC_MMC_PERSISTENT_BEARER_STATE_ENUM_UINT8;




enum MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM
{
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_REG_FAILURE         = 0, /* 注册失败导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SERVICE_FAILURE     = 1, /* service流程失败导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_MT_DETACH           = 2, /* 网络触发的detach导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_USER_DETACH         = 3, /* 用户触发的detach操作导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_RAT_OR_BAND_DETACH  = 4, /* system configure中RAT或band触发的detach导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SRV_DOMAIN_DETACH   = 5, /* system configure中服务域触发的detach导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_AREA_LOST           = 6, /* lte掉网导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_NO_RF               = 7, /* Lte NO RF导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_BUTT
};
typedef VOS_UINT8 MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8;


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

typedef  NAS_MSCC_PIF_RAT_PRIO_STRU MSCC_MMC_PLMN_RAT_PRIO_STRU;


typedef  NAS_MSCC_PIF_PLMN_ID_STRU MSCC_MMC_PLMN_ID_STRU;


typedef NAS_MSCC_PIF_3GPP2_RAT_STRU MSCC_MMC_3GPP2_RAT_STRU;


typedef NAS_MSCC_PIF_EPLMN_INFO_STRU MSCC_MMC_EPLMN_INFO_STRU;



typedef NAS_MSCC_PIF_CAMP_CELL_INFO_STRU MSCC_MMC_CAMP_CELL_INFO_STRU;


typedef  NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU MSCC_MMC_OPERATOR_NAME_INFO_STRU;


typedef NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU MSCC_MMC_UE_SUPPORT_FREQ_BAND_STRU;


typedef NAS_MSCC_PIF_RSSI_VALUE_STRU MSCC_MMC_RSSI_VALUE_STRU;


typedef NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU MSCC_MMC_SCELL_MEAS_TYPE_STRU;


typedef NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN;
typedef NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU;

typedef NAS_MSCC_PIF_RSSI_IND_STRU MMC_MSCC_RSSI_IND_STRU;


typedef NAS_MSCC_PIF_CQI_INFO_STRU MMC_MSCC_CQI_INFO_STRU;

typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU MSCC_MMC_LMM_CELL_SIGN_INFO_STRU;

typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;



typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */ /* 消息头                                   */
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus;
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8              enRegDomain;        /* 在原接口新增开机允许注册的服务域 */
    NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8                     enRegCtrl;
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stPlmnRatPrio;
    NAS_MSCC_PIF_3GPP2_RAT_STRU                             st3Gpp2Rat;
    VOS_UINT8                                               aucImsi[NAS_MAX_IMSI_LENGTH];
    NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8                       enCallMode;
    VOS_UINT8                                               aucReserved[2];
}MSCC_MMC_START_REQ_STRU;



typedef NAS_MSCC_PIF_START_CNF_STRU MMC_MSCC_START_CNF_STRU;


typedef NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU MMC_MSCC_SYS_INFO_IND_STRU;


typedef NAS_MSCC_PIF_REG_RESULT_IND_STRU MMC_MSCC_REG_RESULT_IND_STRU;


typedef NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU MMC_MSCC_USIM_AUTH_FAIL_IND_STRU;


typedef NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU MMC_MSCC_SERVICE_STATUS_IND_STRU;


typedef NAS_MSCC_PIF_MM_INFO_IND_STRU MMC_MSCC_MM_INFO_IND_STRU;


typedef NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU MSCC_MMC_SIGN_REPORT_REQ_STRU;


typedef NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU MSCC_MMC_MODE_CHANGE_REQ_STRU;


typedef NAS_MSCC_PIF_ATTACH_REQ_STRU MSCC_MMC_ATTACH_REQ_STRU;


typedef NAS_MSCC_PIF_ATTACH_CNF_STRU MMC_MSCC_ATTACH_CNF_STRU;


typedef NAS_MSCC_PIF_DETACH_REQ_STRU MSCC_MMC_DETACH_REQ_STRU;


typedef NAS_MSCC_PIF_DETACH_CNF_STRU MMC_MSCC_DETACH_CNF_STRU;


typedef NAS_MSCC_PIF_DETACH_IND_STRU MMC_MSCC_DETACH_IND_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU MMC_MSCC_CSG_LIST_ABORT_CNF_STRU;


typedef NAS_MSCC_PIF_CSG_LIST_REJ_STRU MMC_MSCC_CSG_LIST_REJ_STRU;

typedef NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU MSCC_MMC_CSG_LIST_ABORT_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_REQ_STRU MSCC_MMC_PLMN_LIST_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_CNF_STRU MMC_MSCC_PLMN_LIST_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_REJ_STRU MMC_MSCC_PLMN_LIST_REJ_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU MSCC_MMC_PLMN_USER_RESEL_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU MSCC_MMC_PLMN_SPECIAL_REQ_STRU;



typedef NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU MMC_MSCC_COVERAGE_AREA_IND_STRU;


typedef NAS_MSCC_PIF_POWER_OFF_REQ_STRU MSCC_MMC_POWER_OFF_REQ_STRU;


typedef NAS_MSCC_PIF_POWER_OFF_CNF_STRU MMC_MSCC_POWER_OFF_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU MMC_MSCC_PLMN_RESEL_CNF_STRU;


typedef NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU MMC_MSCC_DATATRAN_ATTRI_IND_STRU;


typedef NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU MSCC_MMC_SYS_CFG_SET_REQ_STRU;


typedef NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU MMC_MSCC_SYS_CFG_SET_CNF_STRU;


typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MSCC_MMC_PLMN_SEARCH_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU;


typedef NAS_MSCC_PIF_PLMN_SELECTION_START_IND_STRU MMC_MSCC_PLMN_SELECTION_START_IND_STRU;


typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU;


typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;


typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;


typedef NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU;


typedef NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU;


typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU;


typedef NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU MMC_MSCC_AC_INFO_CHANGE_IND_STRU;


typedef NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU;


typedef NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU MSCC_MMC_UPDATE_UPLMN_NTF_STRU;


typedef NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU MSCC_MMC_EOPLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_CL_ASSOCIATED_INFO_NTF_STRU MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;          /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause;
}MSCC_MMC_CL_INTERSYS_START_NTF_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_INTERSYS_START_IND_STRU
 *
 * Description : MMC的异系统开始指示
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode;
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode;
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause;
}MMC_MSCC_INTERSYS_START_IND_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_INTERSYS_END_IND_STRU
 *
 * Description : MMC的异系统结束指示
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_RATMODE_ENUM_UINT32             enCurrRatMode;
}MMC_MSCC_INTERSYS_END_IND_STRU;


typedef NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU MMC_MSCC_EOPLMN_SET_CNF_STRU;


typedef NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU MMC_MSCC_EOPLMN_SET_ABORT_STRU;


typedef NAS_MSCC_PIF_NET_SCAN_REQ_STRU MSCC_MMC_NET_SCAN_REQ_STRU;


typedef NAS_MSCC_PIF_NET_SCAN_INFO_STRU MMC_MSCC_NET_SCAN_INFO_STRU;


typedef NAS_MSCC_PIF_NET_SCAN_CNF_STRU MMC_MSCC_NET_SCAN_CNF_STRU;


typedef NAS_MSCC_PIF_SERV_REJ_IND_STRU MMC_MSCC_SERV_REJ_IND_STRU;


typedef NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU MSCC_MMC_ABORT_NET_SCAN_REQ_STRU;


typedef NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU MMC_MSCC_ABORT_NET_SCAN_CNF_STRU;


typedef NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU;


typedef NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU MMC_MSCC_CAMP_ON_IND_STRU_STRU;


typedef NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU;


typedef NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;


typedef NAS_MSCC_PIF_TDS_NCELL_INFO_STRU MSCC_MMC_TDS_NCELL_INFO_STRU;


typedef NAS_MSCC_PIF_LTE_NCELL_INFO_STRU MSCC_MMC_LTE_NCELL_INFO_STRU;


typedef NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU MSCC_MMC_NCELL_INFO_NOTIFY_STRU;


typedef NAS_MSCC_PIF_EPLMN_INFO_IND_STRU MMC_MSCC_EPLMN_INFO_IND_STRU;


typedef NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU;


typedef NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU MSCC_MMC_PS_TRANSFER_NOTIFY_STRU;


typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU;


typedef NAS_MSCC_PIF_ACQ_REQ_STRU MSCC_MMC_ACQ_REQ_STRU;


typedef NAS_MSCC_PIF_ACQ_CNF_STRU MMC_MSCC_ACQ_CNF_STRU;


typedef NAS_MSCC_PIF_REG_CELL_INFO_STRU MSCC_MMC_REG_CELL_INFO_STRU;


typedef NAS_MSCC_PIF_REG_REQ_STRU MSCC_MMC_REG_REQ_STRU;


typedef NAS_MSCC_PIF_REG_CNF_STRU MMC_MSCC_REG_CNF_STRU;


typedef NAS_MSCC_PIF_POWER_SAVE_REQ_STRU MSCC_MMC_POWER_SAVE_REQ_STRU;


typedef NAS_MSCC_PIF_POWER_SAVE_CNF_STRU MMC_MSCC_POWER_SAVE_CNF_STRU;


typedef  NAS_MSCC_PIF_ACQ_CNF_STRU MMC_MSCC_ACQ_IND_STRU;


typedef NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU;


typedef NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU MMC_MSCC_RF_AVAILABLE_IND_STRU;


typedef NAS_MSCC_PIF_SRV_ACQ_REQ_STRU MSCC_MMC_SRV_ACQ_REQ_STRU;


typedef NAS_MSCC_PIF_SRV_ACQ_CNF_STRU MMC_MSCC_SRV_ACQ_CNF_STRU;


typedef NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU;


typedef NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU MSCC_MMC_END_SESSION_NOTIFY_STRU;


typedef NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU;

typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MSCC_MMA_IMS_VOICE_CAP_NOTIFY_STRU;


typedef NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU MSCC_MMC_CFPLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU MSCC_MMC_CFPLMN_QUERY_REQ_STRU;

typedef NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU MMC_MSCC_CFPLMN_SET_CNF_STRU;


typedef NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU MMC_MSCC_CFPLMN_QUERY_CNF_STRU;


typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU;


typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU;

typedef NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU MSCC_MMC_PREF_PLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU MMC_MSCC_PREF_PLMN_SET_CNF_STRU;


typedef NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU MSCC_MMC_IMS_SWITCH_STATE_IND_STRU;


typedef NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU;
/*****************************************************************************
 结构名    : MSCC_MMC_HRPD_SYS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD下SubnetID
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucSubnetId[MSCC_MMC_HRPD_SUBNET_MAX_LEN];
    VOS_UINT16                              usBandClass;
    VOS_UINT16                              usFreq;
}MSCC_MMC_HRPD_SYS_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_BG_SEARCH_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
    VOS_RATMODE_ENUM_UINT32             enRatMode;
}MSCC_MMC_BG_SEARCH_REQ_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_INTERSYS_HRPD_NTF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MSCC_MMC_INTERSYS_HRPD_NTF_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_MMSS_INFO_NTF_STRU
 *
 * Description : Feature GUL MMSS needs not be support at present, the content
 * of this interface is left.
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MSCC_MMC_MMSS_INFO_NTF_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_BG_SEARCH_CNF_STRU
 *
 * Description : This message should contain all existed subnet of HRPD.
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucHrpdSysNum;
    VOS_UINT8                           aucReserve[1];
    MSCC_MMC_BG_SRCH_RESULT_ENUM_UINT32 enRslt;
    MSCC_MMC_HRPD_SYS_STRU              astHrpdSysList[MSCC_MMC_BG_HRPD_MAX_SYS_NUM];
}MMC_MSCC_BG_SEARCH_CNF_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_STOP_BG_SEARCH_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MSCC_MMC_STOP_BG_SEARCH_REQ_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_STOP_BG_SEARCH_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MMC_MSCC_STOP_BG_SEARCH_CNF_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_PREF_PLMN_INFO_IND_STRU
 *
 * Description : This message should contain pref plmn info:HPLMN/EHPLMN/UPLMN/OPLMN.
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8                  enPrefPlmnType;
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU                       stEhplmnInfo;
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                     stUplmnInfo;
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                     stOplmnInfo;
}MMC_MSCC_PREF_PLMN_INFO_IND_STRU;

/** ****************************************************************************
 * Name        : ID_MMC_MSCC_MMSS_LTE_UNAVAILABLE_STRU_IND
 *
 * Description : This message is used to notify mscc lte is not available for mmss
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8          enReason;
    VOS_UINT8                                               aucReserve[1];
}MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU;


/** ****************************************************************************
 * Name        : ID_MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ
 *
 * Description : specify the plmn list info to query each plmn pri class
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stPlmnListInfo;
}MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU;

/** ****************************************************************************
 * Name        : ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF
 *
 * Description : query the plmn list info with pri class type
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU              stPlmnPriClassList;
}MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU;


/** ****************************************************************************
 * Name        : MSCC_MMC_AUTO_RESEL_SET_REQ_STRU
 *
 * Description : send mmc auto resel set
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT8                           ucActiveFlg;
    VOS_UINT8                           aucReserved[3];
}MSCC_MMC_AUTO_RESEL_SET_REQ_STRU;


typedef NAS_MSCC_PIF_DPLMN_SET_REQ_STRU MSCC_MMC_DPLMN_SET_REQ_STRU;


typedef NAS_MSCC_PIF_DPLMN_SET_CNF_STRU MMC_MSCC_DPLMN_SET_CNF_STRU;


typedef NAS_MSCC_PIF_GET_GEO_REQ_STRU MSCC_MMC_GET_GEO_REQ_STRU;


typedef NAS_MSCC_PIF_GET_GEO_CNF_STRU MMC_MSCC_GET_GEO_CNF_STRU;


typedef NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU MSCC_MMC_STOP_GET_GEO_REQ_STRU;


typedef NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU MMC_MSCC_STOP_GET_GEO_CNF_STRU;


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
    VOS_UINT32   enMsgID;             /*_H2ASN_MsgChoice_Export MSCC_MMC_MSG_ID_ENUM_UINT32 */
    VOS_UINT8    aucMsgBlock[4];

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MSCC_MMC_MSG_ID_ENUM_UINT32
        ****************************************************************************/
}MSCC_MMC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MSCC_MMC_MSG_DATA   stMsgData;
}MsccMmcInterface_MSG;

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
