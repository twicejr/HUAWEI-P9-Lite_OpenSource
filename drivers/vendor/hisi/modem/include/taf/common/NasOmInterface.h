
#ifndef __NASOMINTERFACE_H__
#define __NASOMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define LEN_LAI                                             5
#define LEN_RAI                                             6

#define NAS_OM_EVENT_NO_PARA                                0
#define NAS_OM_EVENT_SERVICE_REJ_LEN                        2
#define NAS_OM_EVENT_ATTACH_REQ_LEN                         1
#define NAS_OM_EVENT_ATTACH_FAIL_LEN                        2
#define NAS_OM_EVENT_PDP_ACTIVE_REQ_LEN                     1
#define NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN                    1
#define NAS_OM_EVENT_PDP_DEACTIVE_REQ_LEN                   1
#define NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ_LEN             1
#define NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL_LEN            1
#define NAS_OM_EVENT_RAU_REQ_LEN                            1
#define NAS_OM_EVENT_RAU_FAIL_LEN                           2
#define NAS_OM_EVENT_AUTH_AND_CIPHER_FAIL_LEN               1
#define NAS_OM_EVENT_LAU_REQ_LEN                            1
#define NAS_OM_EVENT_LAU_FAIL_LEN                           2
#define NAS_OM_EVENT_AUTH_FAIL_LEN                          1
#define NAS_OM_EVENT_SMS_MO_REPORT_LEN                      2
#define NAS_OM_EVENT_SMS_RECEIVE_LEN                        1
#define NAS_OM_EVENT_SMS_MT_NOTIFY_LEN                      1
#define NAS_OM_EVENT_HPLMN_TIMER_START_LEN                  4
#define NAS_OM_EVENT_STK_ACCESS_TECHNOLOGY_CHANGE_LEN       1
#define NAS_OM_EVENT_STK_NETWORK_SEARCH_MODE_CHANGE_LEN     1

/*OTA相关: 需要与OM确定具体的值*/
#define OM_NAS_OTA_REQ    0xC101
#define NAS_OM_OTA_CNF    0xC102
#define NAS_OM_OTA_IND    0xC103

#define VOS_MSG_HEADER  VOS_UINT32 ulSenderCpuId;  \
                        VOS_UINT32 ulSenderPid;    \
                        VOS_UINT32 ulReceiverCpuId;\
                        VOS_UINT32 ulReceiverPid;  \
                        VOS_UINT32 ulLength;

/* sizeof(VOS_MSG_HEADER) + sizeof(usTransPrimId) + sizeof(usRsv1)
 + sizeof(ucFuncType)     + sizeof(ucReserve)    + sizeof(usLength)*/
#define NAS_OM_TRANS_MSG_OM_HEADER_LEN    28

#define ID_NAS_OM_TRANS_MSG               0x5001                /* NAS到OM 的透传消息原语 */



#define SM_OM_PDP_ACTIVATED               0
#define SM_OM_PDP_NOT_ACTIVATED           1

/* 双卡双待项目中空口消息与trans消息区分modem0和modem1 */
#define NAS_OM_FUNCTION_TYPE_MODEM_MASK   (0xc0)
#define NAS_OM_FUNCTION_TYPE_VALUE_MASK   (0x3f)
/* Added by z00301431 for OM融合, 2015-6-27 begin */
#define NAS_MAX_TIMER_EVENT               (100)
/* Added by z00301431 for OM融合, 2015-6-27 end */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    NAS_OM_EVENT_DATA_SERVICE_REQ,
    NAS_OM_EVENT_DATA_SERVICE_ACC,
    NAS_OM_EVENT_DATA_SERVICE_REJ,                /*_H2ASN_MsgChoice NAS_OM_MM_CAUSE_ENUM*/
    NAS_OM_EVENT_LOCATION_UPDATE_REQ,             /*_H2ASN_MsgChoice NAS_OM_MM_LAU_TYPE_ENUM*/
    NAS_OM_EVENT_LOCATION_UPDATE_SUCCESS,
    NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,         /*_H2ASN_MsgChoice NAS_OM_MM_CAUSE_ENUM*/
    NAS_OM_EVENT_ATTACH_REQ,                      /*_H2ASN_MsgChoice NAS_OM_GMM_ATTACH_TYPE_ENUM*/
    NAS_OM_EVENT_ATTACH_SUCC,
    NAS_OM_EVENT_ATTACH_FAIL,                     /*_H2ASN_MsgChoice NAS_OM_MM_CAUSE_ENUM*/
    NAS_OM_EVENT_PDP_ACTIVE_REQ,                  /*_H2ASN_MsgChoice NAS_OM_SM_ACTIVE_REQUEST_TYPE*/
    NAS_OM_EVENT_PDP_ACTIVE_SUCC,
    NAS_OM_EVENT_PDP_ACTIVE_FAIL,                 /*_H2ASN_MsgChoice NAS_OM_SM_CAUSE_ENUM*/
    NAS_OM_EVENT_PDP_DEACTIVE_REQ,                /*_H2ASN_MsgChoice NAS_OM_SM_DEACTIVE_REQUEST_TYPE*/
    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ,          /*_H2ASN_MsgChoice NAS_OM_SM_MODIFY_REQUEST_TYPE*/
    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_SUCC,
    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL,         /*_H2ASN_MsgChoice NAS_OM_SM_CAUSE_ENUM*/
    NAS_OM_EVENT_RAU_REQ,                         /*_H2ASN_MsgChoice NAS_OM_GMM_RAU_TYPE_ENUM*/
    NAS_OM_EVENT_RAU_SUCC,
    NAS_OM_EVENT_RAU_FAIL,                        /*_H2ASN_MsgChoice NAS_OM_MM_CAUSE_ENUM*/
    NAS_OM_EVENT_DETACH_FINISH,
    NAS_OM_EVENT_AUTH_REQ,
    NAS_OM_EVENT_AUTH_SUCCESS,
    NAS_OM_EVENT_AUTH_FAILURE,                    /*_H2ASN_MsgChoice NAS_OM_MM_CAUSE_ENUM*/
    NAS_OM_EVENT_AUTH_REJECT,
    NAS_OM_EVENT_AUTH_AND_CIPHER_REQ,
    NAS_OM_EVENT_AUTH_AND_CIPHER_SUCC,
    NAS_OM_EVENT_AUTH_AND_CIPHER_FAIL,            /*_H2ASN_MsgChoice NAS_OM_MM_CAUSE_ENUM*/
    NAS_OM_EVENT_AUTH_AND_CIPHER_REJ,
    NAS_OM_EVENT_PLMN_SELECTION_START,
    NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
    NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
    NAS_OM_EVENT_COVERAGE_LOST,
    NAS_OM_EVENT_SMS_RECEIVE,
    NAS_OM_EVENT_SMS_SENT,
    /*短消息发送确认    */
    NAS_OM_EVENT_SMS_MO_SUCC,                   /*_H2ASN_MsgChoice NAS_OM_SMS_MO_REPORT_STRU*/
    NAS_OM_EVENT_SMS_MO_FAIL,                   /*_H2ASN_MsgChoice NAS_OM_SMS_MO_REPORT_STRU*/
    /*短消息状态报告    */
    NAS_OM_EVENT_SMS_MT_NOTIFY,
    /*短消息存储状态报告*/
    NAS_OM_EVENT_SMS_STATICS,                   /*_H2ASN_MsgChoice NAS_OM_SMS_STATICS_STRU*/
    NAS_OM_EVENT_READY_TIMER_START,
    NAS_OM_EVENT_READY_TIMER_STOP,
    NAS_OM_EVENT_IMSI_DETACH_IND,
    NAS_OM_EVENT_CS_SERVICE,
    NAS_OM_EVENT_PS_SERVICE,
    NAS_OM_EVENT_CS_PS_SERVICE,
    NAS_OM_EVENT_LIMITED_SERVICE,
    NAS_OM_EVENT_EPLMN_LIST,
    NAS_OM_EVENT_FPLMN_LIST,
    NAS_OM_EVENT_CC_MO_ATTEMPT,
    NAS_OM_EVENT_CC_MO_ALERTING,
    NAS_OM_EVENT_CC_MO_ANSWERED,
    NAS_OM_EVENT_CC_MO_DISCONNECT,
    NAS_OM_EVENT_CC_MT_ATTEMPT,
    NAS_OM_EVENT_CC_MT_ALERTING,
    NAS_OM_EVENT_CC_MT_ANSWERED,
    NAS_OM_EVENT_CC_MT_DISCONNECT,
    NAS_OM_EVENT_HPLMN_TIMER_START,
    NAS_OM_EVENT_HPLMN_TIMER_STOP,
    NAS_OM_EVENT_HPLMN_TIMER_EXPIRE,
    NAS_OM_EVENT_DTE_UP_DTR,
    NAS_OM_EVENT_DTE_DOWN_DTR,
    NAS_OM_EVENT_DCE_UP_DSR,
    NAS_OM_EVENT_DCE_DOWN_DSR,
    NAS_OM_EVENT_DCE_UP_DCD,
    NAS_OM_EVENT_DCE_DOWN_DCD,
    NAS_OM_EVENT_DCE_UP_CTS,
    NAS_OM_EVENT_DCE_DOWN_CTS,
    NAS_OM_EVENT_DCE_UP_RI,
    NAS_OM_EVENT_DCE_DOWN_RI,
    NAS_OM_EVENT_DCE_CREATE_PPP,
    NAS_OM_EVENT_DTE_RELEASE_PPP,
    NAS_OM_EVENT_DTE_DOWN_DTR_RELEASE_PPP_IP_TYPE,
    NAS_OM_EVENT_DTE_DOWN_DTR_RELEASE_PPP_PPP_TYPE,

    NAS_OM_EVENT_LOCATION_STATUS_EVENT,
    NAS_OM_EVENT_STK_ACCESS_TECHNOLOGY_CHANGE_EVENT,
    NAS_OM_EVENT_STK_NETWORK_SEARCH_MODE_CHANGE_EVENT,

    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    NAS_OM_EVENT_TIMER_OPERATION_START,
    NAS_OM_EVENT_TIMER_OPERATION_STOP,
    NAS_OM_EVENT_TIMER_OPERATION_EXPIRED,
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

    NAS_OM_EVENT_PA_STAR_ABNORMAL,

    NAS_OM_EVENT_SMS_MT_FAIL,

    NAS_OM_EVENT_1X_SYS_ACQUIRE_SUCCESS,
    NAS_OM_EVENT_1X_SYS_LOST,
    NAS_OM_EVENT_HRPD_SYS_ACQUIRE_SUCCESS,
    NAS_OM_EVENT_HRPD_SYS_LOST,
    NAS_OM_EVENT_HRPD_SESSION_OPEN,
    NAS_OM_EVENT_1X_POWER_SAVE,
    NAS_OM_EVENT_HRPD_POWER_SAVE,
    NAS_OM_EVENT_HRPD_SESSION_CLOSE,
    NAS_OM_EVENT_HRPD_SESSION_SUPPORT_EHRPD,
    NAS_OM_EVENT_HRPD_SESSION_NOT_SUPPORT_EHRPD,

    NAS_OM_EVENT_ID_BUTT
}NAS_OM_EVENT_ID_ENUM;

typedef VOS_UINT16 NAS_OM_EVENT_ID_ENUM_UINT16;

typedef enum
{
    NAS_OM_MM_CAUSE_NULL                                  = 0,
    NAS_OM_MM_CAUSE_IMSI_UNKNOWN_IN_HLR                   = 2,
    NAS_OM_MM_CAUSE_ILLEGAL_MS                            = 3,
    NAS_OM_MM_CAUSE_IMSI_UNKNOWN_IN_VLR                   = 4,
    NAS_OM_MM_CAUSE_IMSI_NOT_ACCEPTED                     = 5,
    NAS_OM_MM_CAUSE_ILLEGAL_ME                            = 6,
    NAS_OM_MM_CAUSE_GPRS_SERV_NOT_ALLOW                   = 7,
    NAS_OM_MM_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW = 8,
    NAS_OM_MM_CAUSE_MS_ID_NOT_DERIVED                     = 9,
    NAS_OM_MM_CAUSE_IMPLICIT_DETACHED                     = 10,
    NAS_OM_MM_CAUSE_PLMN_NOT_ALLOW                        = 11,
    NAS_OM_MM_CAUSE_LA_NOT_ALLOW                          = 12,
    NAS_OM_MM_CAUSE_ROAM_NOT_ALLOW                        = 13,
    NAS_OM_MM_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN           = 14,
    NAS_OM_MM_CAUSE_NO_SUITABL_CELL                       = 15,
    NAS_OM_MM_CAUSE_MSC_UNREACHABLE                       = 16,
    NAS_OM_MM_CAUSE_NETWORK_FAILURE                       = 17,
    NAS_OM_MM_CAUSE_MAC_FAILURE                           = 20,
    NAS_OM_MM_CAUSE_SYNCH_FAILURE                         = 21,
    NAS_OM_MM_CAUSE_PROCEDURE_CONGESTION                  = 22,
    NAS_OM_MM_CAUSE_GSM_AUT_UNACCEPTABLE                  = 23,
    NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT                    = 24,
    NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE                = 25,
    NAS_OM_MM_CAUSE_AUT_GSM_OTHER_FAILURE                 = 26,
    NAS_OM_MM_CAUSE_SERV_OPT_NOT_SUPPORT                  = 32,
    NAS_OM_MM_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE            = 33,
    NAS_OM_MM_CAUSE_SERV_OPT_OUT_OF_ORDER                 = 34,
    NAS_OM_MM_CAUSE_CALL_CANNOT_IDENTIFY                  = 38,
    NAS_OM_MM_CAUSE_NO_PDP_CONTEXT_ACT                    = 40,
    NAS_OM_MM_CAUSE_RETRY_UPON_ENTRY_CELL                 = 60,
    NAS_OM_MM_CAUSE_RETRY_UPON_ENTRY_CELL_MIN             = 48,
    NAS_OM_MM_CAUSE_RETRY_UPON_ENTRY_CELL_MAX             = 63,
    NAS_OM_MM_CAUSE_SEMANTICALLY_INCORRECT_MSG            = 95,
    NAS_OM_MM_CAUSE_INVALID_MANDATORY_INF                 = 96,
    NAS_OM_MM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE            = 97,
    NAS_OM_MM_CAUSE_MSG_TYPE_NOT_COMPATIBLE               = 98,
    NAS_OM_MM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED            = 99,
    NAS_OM_MM_CAUSE_CONDITIONAL_IE_ERROR                  = 100,
    NAS_OM_MM_CAUSE_MSG_NOT_COMPATIBLE                    = 101,
    NAS_OM_MM_CAUSE_PROTOCOL_ERROR                        = 111,
    NAS_OM_MM_CAUSE_TIMER_TIMEOUT                         = 251,
    NAS_OM_MM_CAUSE_RR_CONN_EST_FAIL                      = 252,
    NAS_OM_MM_CAUSE_RR_CONN_FAIL                          = 253,
    NAS_OM_MM_CAUSE_ACCESS_BARRED                         = 254,
    NAS_OM_MM_CAUSE_UNSUITABLE_MODE                       = 255,
    NAS_OM_MM_CAUSE_BUTT
}NAS_OM_MM_CAUSE_ENUM;

typedef enum
{
    NAS_OM_SM_REJ_CAUSE_INSUFF_RESOURCE                   = 26,
    NAS_OM_SM_REJ_CAUSE_MISS_OR_UNKNOWN_APN               = 27,
    NAS_OM_SM_REJ_CAUSE_UNKNOWN_PDP_ADDR_OR_TYPE          = 28,
    NAS_OM_SM_REJ_CAUSE_USER_AUTHEN_FAIL                  = 29,
    NAS_OM_SM_REJ_CAUSE_ACT_REJ_BY_GGSN                   = 30,
    NAS_OM_SM_REJ_CAUSE_ACT_REJ_UNSPEC                    = 31,
    NAS_OM_SM_REJ_CAUSE_SERV_OPT_NOT_SUPP                 = 32,
    NAS_OM_SM_REJ_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIB         = 33,
    NAS_OM_SM_REJ_CAUSE_SERV_OPT_TEMP_OUT_ORDER           = 34,
    NAS_OM_SM_REJ_CAUSE_NSAPI_USED                        = 35,
    NAS_OM_SM_REJ_CAUSE_SEMANTIC_ERR_IN_TFT               = 41,
    NAS_OM_SM_REJ_CAUSE_SYNTACTIC_ERR_IN_TFT              = 42,
    NAS_OM_SM_REJ_CAUSE_UNKNOWN_PDP_CONTEXT               = 43,
    NAS_OM_SM_REJ_CAUSE_SEMANTIC_ERR_IN_PF                = 44,
    NAS_OM_SM_REJ_CAUSE_SYNTACTIC_ERR_IN_PF               = 45,
    NAS_OM_SM_REJ_CAUSE_PDP_CONT_WITHOUT_TFT_ACT          = 46,
    NAS_OM_SM_REJ_CAUSE_INVALID_TI                        = 81,
    NAS_OM_SM_REJ_CAUSE_INVALID_MANDATORY_IE              = 96,
    NAS_OM_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT                  = 97,
    NAS_OM_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE       = 98,
    NAS_OM_SM_REJ_CAUSE_STATE_ERR                         = 101,
    NAS_OM_SM_REJ_CAUSE_PROTOCOL_ERR                      = 111,
    NAS_OM_SM_REJ_CAUSE_TIMER_TIMEOUT                     = 201,
    NAS_OM_SM_REJ_CAUSE_GPRS_ATTACH_FAIL                  = 202,
    NAS_OM_SM_REJ_CAUSE_OTHER_PDP_CONT_EXIST              = 203,
    NAS_OM_SM_REJ_CAUSE_NSAPI_IN_USE                      = 204,
    NAS_OM_SM_REJ_CAUSE_COLLISION_WITH_NW                 = 205,
    NAS_OM_SM_REJ_CAUSE_GMM_INIT                          = 206,
    NAS_OM_SM_REJ_CAUSE_BUTT
}NAS_OM_SM_CAUSE_ENUM;

enum NAS_OM_SM_ACTIVE_REQUEST_TYPE
{
    ACTIVE_REQUEST_INIT_TYPE_MO                           = 0x00,
    ACTIVE_REQUEST_INIT_TYPE_MT                           = 0x01,
    ACTIVE_REQUEST_INIT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_SM_ACTIVE_REQUEST_INIT_TYPE_UINT8;

enum NAS_OM_SM_DEACTIVE_REQUEST_TYPE
{
    DEACTIVE_REQUEST_INIT_TYPE_MO                         = 0x00,
    DEACTIVE_REQUEST_INIT_TYPE_MT                         = 0x01,
    DEACTIVE_REQUEST_INIT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_SM_DEACTIVE_REQUEST_INIT_TYPE_UINT8;

enum NAS_OM_SM_MODIFY_REQUEST_TYPE
{
    MODIFY_REQUEST_INIT_TYPE_MO                           = 0x00,
    MODIFY_REQUEST_INIT_TYPE_MT                           = 0x01,
    MODIFY_REQUEST_INIT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_SM_MODIFY_REQUEST_INIT_TYPE_UINT8;

enum NAS_OM_GMM_ATTACH_TYPE_ENUM
{
    NAS_OM_GMM_GPRS_ATTACH                                = 1,
    NAS_OM_GMM_GPRS_ATTACH_WHILE_IMSI_ATTACH              = 2,
    NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH                  = 3,
    NAS_OM_GMM_ATTACH_TYPE_BUTT
};
typedef VOS_UINT8 NAS_GMM_ATTACH_TYPE_ENUM_UINT8;

enum NAS_OM_GMM_RAU_TYPE_ENUM
{
    NAS_OM_GMM_RA_UPDATING                                = 0,
    NAS_OM_GMM_COMBINED_RALA_UPDATING                     = 1,
    NAS_OM_GMM_COMBINED_RALAU_WITH_IMSI_ATTACH            = 2,
    NAS_OM_GMM_PERIODC_UPDATING                           = 3,
    NAS_OM_GMM_UPDATING_TYPE_INVALID
};
typedef VOS_UINT8 NAS_GMM_RAU_TYPE_ENUM_UINT8;

enum NAS_OM_SMS_SAVE_AREA_ENUM
{
    NAS_SMS_SAVE_AREA_SM,
    NAS_SMS_SAVE_AREA_ME,
    NAS_SMS_SAVE_AREA_BUTT
};
typedef VOS_UINT8 NAS_OM_SMS_SAVE_AREA_ENUM_UINT8;

enum NAS_OM_MM_LAU_TYPE_ENUM
{
    NAS_OM_MM_LUT_NORMAL_LU                               = 0,
    NAS_OM_MM_LUT_PERIODIC_UPDATING                       = 1,
    NAS_OM_MM_LUT_IMSI_ATTACH                             = 2,
    NAS_OM_MM_LUT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_OM_MM_LAU_TYPE_ENUM_UINT8;














enum NAS_OM_MMC_STATE_ENUM
{
    SWITCH_ON_END                                 = 0,                          /* 上电或重启时，在此状态下等待ATTACH要求   */
    TRYING_PLMN                                   = 1,                          /* 尝试注册状态                             */
    WAIT_FOR_PLMN_LIST                            = 2,                          /* 等待搜索PLMN list结果                    */
    WAIT_FOR_AS_RESULT                            = 3,                          /* 等待指定搜索PLMN或suitable cell结果      */
    ON_PLMN                                       = 4,                          /* 指示PS域或CS域至少有一个成功注册         */
    LIMIT_SERVICE                                 = 5,                          /* 此时MS只能提供受限服务                   */
    WAIT_FOR_PLMNS                                = 6,                          /* 覆盖区丢失后进入此状态                   */
    NOT_ON_PLMN                                   = 7,                          /* 仅用于手动模式，等待用户选择PLMN         */
    NULL_STATE                                    = 8,                          /* MMC关机时进入次状态                      */
    SWITCH_ON_INIT                                = 9,                          /* 在此状态下初始化MM层和AS层               */
    TC_STATE                                      = 10,                         /* TC测试时迁入此状态                       */
    SUSPEND                                       = 11,
    MMC_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_MMC_STATE_ENUM_UINT8;



/*OTA相关*/
enum OM_NAS_OTA_SWITCH_ENUM
{
    NAS_OTA_SWITCH_OFF   = 0,     /* 停止上报空口消息 */
    NAS_OTA_SWITCH_ON    = 1      /* 开始上报空口消息 */
};
typedef VOS_UINT32   NAS_OTA_SWITCH_ENUM_UINT32;

enum NAS_OM_OTA_CNF_RESULT_ENUM
{
    NAS_OTA_DIRECTION_UP     = 0,     /* 空口配置方向: 上行(MS-->Network) */
    NAS_OTA_DIRECTION_DOWN   = 1      /* 空口配置方向: 下行(Network-->MS) */
};

enum NAS_OTA_CNF_ERRCODE_ENUM
{
    NAS_OTA_CNF_ERRCODE_NO    = 0,     /* 空口配置成功 */
    NAS_OTA_CNF_ERRCODE_YES   = 1      /* 空口配置失败 */
};
typedef VOS_UINT32   NAS_OTA_CNF_ERRCODE_ENUM_UINT32;

typedef VOS_UINT8   NSM_OTA_DIRECTION_ENUM_UINT8;

typedef enum
{
    /*GMM Event*/
    NAS_OTA_MSG_DATA_SERVICE_REQ                =  0x0000,
    NAS_OTA_MSG_DATA_SERVICE_ACC,
    NAS_OTA_MSG_DATA_SERVICE_REJ,
    NAS_OTA_MSG_ATTACH_REQ,
    NAS_OTA_MSG_ATTACH_ACCEPT,
    NAS_OTA_MSG_ATTACH_REJECT,
    NAS_OTA_MSG_ATTACH_COMPLETE,
    NAS_OTA_MSG_RAU_REQ,
    NAS_OTA_MSG_RAU_ACCEPT,
    NAS_OTA_MSG_RAU_REJECT,
    NAS_OTA_MSG_RAU_COMPLETE,
    NAS_OTA_MSG_DETACH_REQ,
    NAS_OTA_MSG_DETACH_REQ_BY_NET,
    NAS_OTA_MSG_DETACH_ACCEPT,
    NAS_OTA_MSG_DETACH_ACCEPT_BY_MS,
    NAS_OTA_MSG_AUTH_AND_CIPHER_REQ,
    NAS_OTA_MSG_AUTH_AND_CIPHER_RESPONSE,
    NAS_OTA_MSG_AUTH_AND_CIPHER_FAIL,
    NAS_OTA_MSG_AUTH_AND_CIPHER_REJ,
    NAS_OTA_MSG_READY_TIMER_START,
    NAS_OTA_MSG_READY_TIMER_STOP,
    NAS_OTA_MSG_P_TMSI_REALLOCATION,
    NAS_OTA_MSG_P_TMSI_REALLOCATION_COMPLETE,
    NAS_OTA_MSG_IDENTITY_REQUEST,
    NAS_OTA_MSG_IDENTITY_RESPONSE,
    NAS_OTA_MSG_GMM_STATUS,
    NAS_OTA_MSG_GMM_STATUS_BY_MS,
    NAS_OTA_MSG_GMM_INFORMATION,

    /*MM Event*/
    NAS_OTA_MSG_IMSI_DETACH_INDICATION          = 0x0100,
    NAS_OTA_MSG_LOCATION_UPDATE_REQUEST,
    NAS_OTA_MSG_LOCATION_UPDATE_ACCEPT,
    NAS_OTA_MSG_LOCATION_UPDATE_REJECT,
    NAS_OTA_MSG_AUTH_REQ,
    NAS_OTA_MSG_AUTH_RSP,
    NAS_OTA_MSG_AUTH_FAILURE,
    NAS_OTA_MSG_AUTH_REJECT,
    NAS_OTA_MSG_ID_REQ,
    NAS_OTA_MSG_ID_RES,
    NAS_OTA_MSG_TMSI_REALLOC_CMD,
    NAS_OTA_MSG_TMSI_REALLOC_CPL,
    NAS_OTA_MSG_CM_SERV_ACCEPT,
    NAS_OTA_MSG_CM_SERV_REJECT,
    NAS_OTA_MSG_CM_SERV_ABORT,
    NAS_OTA_MSG_CM_SERV_REQUEST,
    NAS_OTA_MSG_PAGING_RSP,
    NAS_OTA_MSG_ABORT,
    NAS_OTA_MSG_MM_STA_N2M,
    NAS_OTA_MSG_MM_INFO,
    NAS_OTA_MSG_MM_RR_CONNECTION,
    NAS_OTA_MSG_REEST_REQ,

    NAS_OTA_MSG_MM_STA_M2N,

    /*SM Event*/
    NAS_OTA_MSG_ACT_PDP_CONTEXT_REQ                  = 0x0200,
    NAS_OTA_MSG_ACT_PDP_CONTEXT_ACC,
    NAS_OTA_MSG_ACT_PDP_CONTEXT_REJ,
    NAS_OTA_MSG_REQ_PDP_CONTEXT_ACT,
    NAS_OTA_MSG_REQ_PDP_CONTEXT_REJ,
    NAS_OTA_MSG_DEACT_PDP_CONTEXT_REQ,
    NAS_OTA_MSG_DEACT_PDP_CONTEXT_NET_REQ,
    NAS_OTA_MSG_DEACT_PDP_CONTEXT_ACC,
    NAS_OTA_MSG_DEACT_PDP_CONTEXT_MS_ACC,
    NAS_OTA_MSG_MOD_PDP_CONTEXT_REQ_N2M,
    NAS_OTA_MSG_MOD_PDP_CONTEXT_ACC_M2N,
    NAS_OTA_MSG_MOD_PDP_CONTEXT_REQ_M2N,
    NAS_OTA_MSG_MOD_PDP_CONTEXT_ACC_N2M,
    NAS_OTA_MSG_MOD_PDP_CONTEXT_REJ,
    NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_REQ,
    NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_ACC,
    NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_REJ,
    NAS_OTA_MSG_SM_STATUS,
    NAS_OTA_MSG_SM_MS_STATUS,

    /*SMS Event*/
    NAS_OTA_MSG_SMS_DATA_TYPE_CP_DATA_UP         = 0x0300,
    NAS_OTA_MSG_SMS_DATA_TYPE_CP_ACK_UP,
    NAS_OTA_MSG_SMS_DATA_TYPE_CP_ERROR_UP,
    NAS_OTA_MSG_SMS_DATA_TYPE_CP_DATA_DOWN,
    NAS_OTA_MSG_SMS_DATA_TYPE_CP_ACK_DOWN,
    NAS_OTA_MSG_SMS_DATA_TYPE_CP_ERROR_DOWN,

    /*CC Event*/
    NAS_OTA_MSG_CC_SETUP_DOWN                     = 0x0400,
    NAS_OTA_MSG_CC_SETUP_UP                       = 0x0401,
    NAS_OTA_MSG_CC_EMERGENCY_UP                   = 0x0402,
    NAS_OTA_MSG_CC_RELEASE_DOWN                   = 0x0403,
    NAS_OTA_MSG_CC_RELEASE_UP                     = 0x0404,
    NAS_OTA_MSG_CC_RELEASE_COMPLETE_DOWN          = 0x0405,
    NAS_OTA_MSG_CC_RELEASE_COMPLETE_UP            = 0x0406,
    NAS_OTA_MSG_CC_CALL_PROCEEDING                = 0x0407,
    NAS_OTA_MSG_CC_ALERTING_DOWN                  = 0x0408,
    NAS_OTA_MSG_CC_ALERTING_UP                    = 0x0409,
    NAS_OTA_MSG_CC_CONNECT_DOWN                   = 0x040A,
    NAS_OTA_MSG_CC_CONNECT_UP                     = 0x040B,
    NAS_OTA_MSG_CC_CONNECT_ACK_UP                 = 0x040C,
    NAS_OTA_MSG_CC_CONNECT_ACK_DOWN               = 0x040D,
    NAS_OTA_MSG_CC_DISCONNECT_DOWN                = 0x040E,
    NAS_OTA_MSG_CC_DISCONNECT_UP                  = 0x040F,
    NAS_OTA_MSG_CC_NOTIFY                         = 0x0410,
    NAS_OTA_MSG_CC_HOLD_ACK                       = 0x0411,
    NAS_OTA_MSG_CC_HOLD_REJ                       = 0x0412,
    NAS_OTA_MSG_CC_RETREIVE_ACK                   = 0x0413,
    NAS_OTA_MSG_CC_RETREIVE_REJ                   = 0x0414,
    NAS_OTA_MSG_CC_MODIFY_DOWN                    = 0x0415,
    NAS_OTA_MSG_CC_MODIFY_UP                      = 0x0416,
    NAS_OTA_MSG_CC_MODIFY_COMPLETE_DOWN           = 0x0417,
    NAS_OTA_MSG_CC_MODIFY_COMPLETE_UP             = 0x0418,
    NAS_OTA_MSG_CC_MODIFY_REJ_DOWN                = 0x0419,
    NAS_OTA_MSG_CC_MODIFY_REJ_UP                  = 0x041A,
    NAS_OTA_MSG_CC_PROGRESS                       = 0x041B,
    NAS_OTA_MSG_CC_FACILITY_DOWN                  = 0x041C,
    NAS_OTA_MSG_CC_FACILITY_UP                    = 0x041D,
    NAS_OTA_MSG_CC_START_DTMF_ACK                 = 0x041E,
    NAS_OTA_MSG_CC_START_DTMF_REJ                 = 0x041F,
    NAS_OTA_MSG_CC_STOP_DTMF_ACK                  = 0x0420,
    NAS_OTA_MSG_CC_STATUS_ENQUIRY                 = 0x0421,
    NAS_OTA_MSG_CC_STATUS_DOWN                    = 0x0422,
    NAS_OTA_MSG_CC_STATUS_UP                      = 0x0423,
    NAS_OTA_MSG_CC_START_DTMF                     = 0x0424,
    NAS_OTA_MSG_CC_STOP_DTMF                      = 0x0425,
    NAS_OTA_MSG_CC_CALL_CONFIRM                   = 0x0426,
    NAS_OTA_MSG_CC_HOLD                           = 0x0427,
    NAS_OTA_MSG_CC_RETREIVE                       = 0x0428,
    NAS_OTA_MSG_CC_CCBS_ESTABLISHMENT             = 0x0429,
    NAS_OTA_MSG_CC_CCBS_EST_CNF                   = 0x042A,
    NAS_OTA_MSG_CC_CCBS_RECALL                    = 0x042B,

    /* SS Event */
    NAS_OTA_MSG_SS_REGISTER_DOWN                  = 0x0500,
    NAS_OTA_MSG_SS_REGISTER_UP                    = 0x0501,
    NAS_OTA_MSG_SS_FACILITY_DOWN                  = 0x0502,
    NAS_OTA_MSG_SS_FACILITY_UP                    = 0x0503,
    NAS_OTA_MSG_SS_RELCMPL_DOWN                   = 0x0504,
    NAS_OTA_MSG_SS_RELCMPL_UP                     = 0x0505,

    NAS_OTA_MSG_HLU_LOC_REQUEST                   = 0x0600,
    NAS_OTA_MSG_HLU_LOC_NOTIFICATION              = 0x0601,

    NAS_OTA_MSG_HLU_LOC_ASSIGNMENT                = 0x0603,
    NAS_OTA_MSG_HLU_LOC_COMPLETE_UP               = 0x0604,
    NAS_OTA_MSG_HLU_LOC_COMPLETE_DOWN             = 0x0605,
    NAS_OTA_MSG_HLU_BLOB_REQUEST                  = 0x0606,
    NAS_OTA_MSG_HLU_BLOB_NOTIFICATION             = 0x0607,

    NAS_OTA_MSG_HLU_BLOB_ASSIGNMENT               = 0x0609,
    NAS_OTA_MSG_HLU_BLOB_COMPLETE_UP              = 0x060A,
    NAS_OTA_MSG_HLU_BLOB_COMPLETE_DOWN            = 0x060B,

    NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_REQ         = 0x060C,
    NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_ASSIGN      = 0x060D,
    NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_COMPLETE    = 0x060E,
    NAS_OTA_MSG_HSM_AMP_MSG_TYPE_HARDWAREID_REQ   = 0x060F,
    NAS_OTA_MSG_HSM_AMP_MSG_TYPE_HARDWAREID_RESP  = 0x0610,

    NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_SESSION_CLOSE_UP          = 0x0611,
    NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_SESSION_CLOSE_DOWN        = 0x0612,
    NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_REQ_UP         = 0x0613,
    NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_REQ_DOWN       = 0x0614,
    NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_RESP_UP        = 0x0615,
    NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_RESP_DOWN      = 0x0616,

    NAS_OTA_MSG_ID_BUTT
}NAS_OTA_MSG_ID_ENUM;

typedef VOS_UINT16 NAS_OTA_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名    : NAS_OM_REGISTER_STATE_ENUM
 结构说明  : NAS提供给OM点灯任务的当前注册状态枚举
*****************************************************************************/
enum NAS_OM_REGISTER_STATE_ENUM
{
    NAS_OM_REGISTER_STATE_POWEROFF          = 0,
    NAS_OM_REGISTER_STATE_NOT_REGISTER      = 1,
    NAS_OM_REGISTER_STATE_REGISTER_2G       = 2,
    NAS_OM_REGISTER_STATE_REGISTER_3G       = 3,
    NAS_OM_REGISTER_STATE_REGISTER_4G       = 4,
    NAS_OM_REGISTER_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_REGISTER_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_OM_SERVICE_TYPE_ENUM
 结构说明  : NAS提供给OM点灯任务当前进行的业务类型枚举
*****************************************************************************/
enum NAS_OM_SERVICE_TYPE_ENUM
{
    NAS_OM_SERVICE_TYPE_NO_SERVICE          = 0,
    NAS_OM_SERVICE_TYPE_GSM                 = 1,
    NAS_OM_SERVICE_TYPE_WCDMA               = 2,
    NAS_OM_SERVICE_TYPE_HSPA                = 3,
    NAS_OM_SERVICE_TYPE_LTE                 = 4,
    NAS_OM_SERVICE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_OM_SERVICE_TYPE_ENUM_UINT8;

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
    VOS_UINT8                           ucSmsMr;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulCause;
}NAS_OM_SMS_MO_REPORT_STRU;

typedef struct
{
    NAS_OM_SMS_SAVE_AREA_ENUM_UINT8 ucMemType;
    VOS_UINT8 ucMemCap;
    VOS_UINT8 ucMemUsed;
}NAS_OM_SMS_STATICS_STRU;

typedef struct
{
    NAS_OM_EVENT_ID_ENUM_UINT16         usEventId;          /*_H2ASN_MsgChoice_Export NAS_OM_EVENT_ID_ENUM_UINT16*/
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulModuleId;         /*发送模块PID ，工具根据PID可以屏蔽消息*/
    VOS_UINT8                           aucData[4];

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_OM_EVENT_ID_ENUM_UINT16
    ****************************************************************************/

}NAS_OM_EVENT_IND_STRUCT;















#define NAS_OM_DATA_PTR_LEN          4                                          /* NAS_OM之间传输数据的指针长度*/

/* Modified by wx270776 for OM融合, 2015-7-25, begin */
/*****************************************************************************
 结构名    : ID_NAS_OM_INQUIRE_STRU
 结构说明  : OM发给NAS的REQ消息结构
 1.日    期   : 2015年07月23日
   作    者   : wx270776
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    VOS_UINT8                           aucData[NAS_OM_DATA_PTR_LEN];           /* 传输的消息内容                         */
}ID_NAS_OM_INQUIRE_STRU;
/* Modified by wx270776 for OM融合, 2015-7-25, end */

/* Added by z00301431 for OM融合, 2015-6-27 begin */
/*****************************************************************************
 结构名    : OAM_MMA_TIMER_REPORT_CFG_IND_STRU
 结构说明  : OAM发给MMA的TIMER OTA上报事件 配置信息
 1.日    期   : 2013年06月20日
   作    者   : l00167671
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulItems;
    VOS_UINT32                          aulTimerMsg[NAS_MAX_TIMER_EVENT];
}NAS_TIMER_EVENT_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_OM_CONFIG_TIMER_REPORT_REQ_STRU
 结构说明  : OAM发给MMA的TIMER OTA上报事件 配置信息
 1.日    期   : 2015年06月27日
   作    者   : z00301431
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT32                          ulCommand;
    NAS_TIMER_EVENT_INFO_STRU           stTimerMsg;
}NAS_OM_CONFIG_TIMER_REPORT_REQ_STRU;
/* Added by z00301431 for OM融合, 2015-6-27 end */

/* Added by wx270776 for OM融合, 2015-7-14, begin */
/*****************************************************************************
 结构名    : NAS_OM_CONFIG_TIMER_REPORT_CNF_STRU
 结构说明  : MMC回复OM TIMER OTA上报事件 配置信息
 1.日    期   : 2015年7月14日
   作    者   : wx270776
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
}NAS_OM_CONFIG_TIMER_REPORT_CNF_STRU;
/* Added by wx270776 for OM融合, 2015-7-14, end */

#define NAS_OM_DATA_OFFSET              12                                      /* usLength下一字节到aucData的偏移*/

/* Modified by wx270776 for OM融合, 2015-7-25, begin */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 原语ID                                   */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;                             /* 工具ID，用于支持多工具，由工具定义，UE侧原值返回即可 */
    VOS_UINT8                           aucData[NAS_OM_DATA_PTR_LEN];                             /* 传输的消息内容                         */
}ID_NAS_OM_CNF_STRU;
/* Modified by wx270776 for OM融合, 2015-7-25, end */


/*OTA相关*/
/* Modified by wx270776 for OM融合, 2015-7-25, begin */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT32                          ulOnOff;                                /* 0 - 停止上报 1 - 开始上报 */
}OM_NAS_OTA_REQ_STRUCT;
/* Modified by wx270776 for OM融合, 2015-7-25, end */


/* Modified by wx270776 for OM融合, 2015-7-25, begin */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT32                          ulErrCode;                              /* 传输的消息内容 */
}NAS_OM_OTA_CNF_STRUCT;
/* Modified by wx270776 for OM融合, 2015-7-25, end */

/* Modified by wx270776 for OM融合, 2015-7-25, begin */
typedef struct
{
    VOS_UINT32    ulModule;
    VOS_UINT32    ulPid;
    VOS_UINT32    ulMsgId;
    VOS_UINT32    ulDirection;
    VOS_UINT32    ulLength;
    VOS_UINT8     aucData[NAS_OM_DATA_PTR_LEN];
}NAS_OM_OTA_IND_STRUCT;
/* Modified by wx270776 for OM融合, 2015-7-25, end */

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usPrimId;                               /* 原语ID                                   */
    VOS_UINT16                          usToolsId;                              /* 工具ID，用于支持多工具，由工具定义，UE侧原值返回即可 */
    VOS_UINT8                           aucData[NAS_OM_DATA_PTR_LEN];                             /* 传输的消息内容                         */
}ID_NAS_OM_CONFIG_TIMER_REPORT_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID NAS_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                            *pPara,
    VOS_UINT32                          ulLen
);

extern VOS_VOID NAS_SendAirMsgToOM(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          usMsgID,
    VOS_UINT8                           ucUpDown,
    VOS_UINT32                          ulMsgLen,
    VOS_UINT8                           *pucMsg
);

extern VOS_VOID NAS_RcvOmOtaReq( OM_NAS_OTA_REQ_STRUCT *pstOtaReq );

extern NAS_OM_REGISTER_STATE_ENUM_UINT8 NAS_GetRegisterState(VOS_VOID);

extern NAS_OM_SERVICE_TYPE_ENUM_UINT8   NAS_GetServiceType(VOS_VOID);

/* Deleted by wx270776 for OM融合, 2015-7-18, begin */
/* Deleted by wx270776 for OM融合, 2015-7-18, end */

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

#endif /* end of NasOm.h */

