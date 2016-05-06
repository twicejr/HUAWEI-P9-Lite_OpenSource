

#ifndef __TAF_APP_SSA_H__
#define __TAF_APP_SSA_H__

#include "TafTypeDef.h"

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-20, begin */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-20, end */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


#pragma pack(4)

/* USSD */
#define AT_USSD_NON_TRAN_MODE               0    /* 非透传:单板支持编解码 */
#define AT_USSD_TRAN_MODE                   1    /* 透传:  单板不编解码，只是透传，由后台来编解码 */

/*************************Operation Code************************/
typedef     TAF_UINT8                       TAF_SS_OPERATION;
#define     TAF_SS_REGISTERSS                               10
#define     TAF_SS_ERASESS                                  11
#define     TAF_SS_ACTIVATESS                               12
#define     TAF_SS_DEACTIVATESS                             13
#define     TAF_SS_INTERROGATESS                            14
#define     TAF_SS_PROCESS_USS_DATA                         19
#define     TAF_SS_PROCESS_USS_REQ                          59
#define     TAF_SS_USS_REQ                                  60
#define     TAF_SS_USS_NOTIFY                               61
#define     TAF_SS_REGISTERPASSWORD                         17
#define     TAF_SS_GETPASSWORD                              18
#define     TAF_SS_ERASECC_ENTRY                            77
#define     TAF_SS_FORWARDCHECKSS_INDICATION                38
/***************************************************************/

/************************Component ID tag**********************/
/*目前用不到*/
typedef     TAF_UINT8           TAF_SS_MSGTYPE;
#define     TAF_SS_MSG_TYPE_FACILITY                           0x3b
#define     TAF_SS_MSG_TYPE_REGISTER                           0x3a
#define     TAF_SS_MSG_TYPE_RLCOMPLETE                         0x2a


/***************************************************************/
typedef     TAF_UINT8           TAF_SS_COMPONENTTYPE;
#define     TAF_SS_COMPONENT_TYPE_INVOKE                       0xA1
#define     TAF_SS_COMPONENT_TYPE_RTRNRSLT                     0xA2
#define     TAF_SS_COMPONENT_TYPE_RTRNERR                      0xA3
#define     TAF_SS_COMPONENT_TYPE_REJECT                       0xA4
/***************************************************************/

/**********************SS-Status定义****************************/
typedef     TAF_UINT8           TAF_SS_STATUS;
#define     TAF_SS_QUIESCENT_STATUS_MASK                       0x08
#define     TAF_SS_PROVISIONED_STATUS_MASK                     0x04
#define     TAF_SS_REGISTERED_STATUS_MASK                      0x02
#define     TAF_SS_ACTIVE_STATUS_MASK                          0x01
/**********************SS-Status定义结束************************/

/********************defaultPriority定义****************************/
typedef     TAF_UINT8           TAF_DEFAULT_PRIORITY;
#define     TAF_SS_PRIORITY_LEVELA                             0x06
#define     TAF_SS_PRIORITY_LEVELB                             0x05
#define     TAF_SS_PRIORITY_LEVEL0                             0x00
#define     TAF_SS_PRIORITY_LEVEL1                             0x01
#define     TAF_SS_PRIORITY_LEVEL2                             0x02
#define     TAF_SS_PRIORITY_LEVEL3                             0x03
#define     TAF_SS_PRIORITY_LEVEL4                             0x04
/********************defaultPriority定义结束****************************/

/********************AlertingPattern***********************************/
typedef     TAF_UINT8           TAF_SS_ALERTINGPATTERN;
#define     TAF_SS_ALERTING_LEVEL_0                            0x00
#define     TAF_SS_ALERTING_LEVEL_1                            0x01
#define     TAF_SS_ALERTINT_LEVEL_2                            0x02
#define     TAF_SS_ALERTING_CATEGORY_1                         0x04
#define     TAF_SS_ALERTING_CATEGORY_2                         0x05
#define     TAF_SS_ALERTING_CATEGORY_3                         0x06
#define     TAF_SS_ALERTING_CATEGORY_4                         0x07
#define     TAF_SS_ALERTING_CATEGORY_5                         0x08

/**********************************************************************/

typedef      TAF_UINT16         TAF_SS_ERROR;

/*******************SS-Code的定义**************************/
typedef     TAF_UINT8           TAF_SS_CODE;
#define     TAF_SS_CODE_MASK                                (0xf0)              /* 用于识别补充业务类别，如呼叫闭锁业务高4bit为9， */

#define     TAF_ALL_SS_CODE                                 0x00    /*所有的补充业务*/

#define     TAF_CLIP_SS_CODE                                0x11    /*主叫线路识别显示*/
#define     TAF_CLIR_SS_CODE                                0x12    /*主叫线路识别限制*/
#define     TAF_COLP_SS_CODE                                0x13    /*被叫识别显示*/
#define     TAF_COLR_SS_CODE                                0x14    /*被叫识别限制*/
#define     TAF_MCI_SS_CODE                                 0x15    /*恶意呼叫识别*/
#define     TAF_ALL_NAME_IDENTIFICATION_SS_CODE             0x18    /*主叫姓名识别显示*/
#define     TAF_CNAP_SS_CODE                                0x19    /*主叫姓名识别显示*/

#define     TAF_ALL_FORWARDING_SS_CODE                      0x20    /*所有转移*/
#define     TAF_CFU_SS_CODE                                 0x21    /*无条件呼叫前转*/
#define     TAF_ALL_COND_FORWARDING_SS_CODE                 0x28    /*有条件呼叫前转*/
#define     TAF_CFB_SS_CODE                                 0x29    /*遇忙呼叫前转*/
#define     TAF_CFNRY_SS_CODE                               0x2A    /*无应答呼叫前转*/
#define     TAF_CFNRC_SS_CODE                               0x2B    /*无法到达呼叫前转*/
#define     TAF_CD_SS_CODE                                  0x24    /*呼叫偏转*/

#define     TAF_ECT_SS_CODE                                 0x31    /*显式呼叫转移*/
#define     TAF_MAH_SS_CODE                                 0x32    /*移动访问捕获*/

#define     TAF_CW_SS_CODE                                  0x41    /*呼叫等待*/
#define     TAF_HOLD_SS_CODE                                0x42    /*呼叫保持*/
#define     TAF_CCBS_A_SS_CODE                              0x43    /*遇忙呼叫完成，发起方*/
#define     TAF_CCBS_B_SS_CODE                              0x44    /*遇忙呼叫完成，目的方*/
#define     TAF_MC_SS_CODE                                  0x45    /*多呼*/

#define     TAF_MULTIPTY_SS_CODE                            0x51    /*多方通话*/

#define     TAF_CUG_SS_CODE                                 0x61    /*闭合用户群*/

#define     TAF_AOCI_SS_CODE                                0x71    /*计费通知(信息)*/
#define     TAF_AOCC_SS_CODE                                0x72    /*计费通知(计费)*/

#define     TAF_UUS1_SS_CODE                                0x81    /*用户对用户信令1*/
#define     TAF_UUS2_SS_CODE                                0x82    /*用户对用户信令2*/
#define     TAF_UUS3_SS_CODE                                0x83    /*用户对用户信令3*/

#define     TAF_ALL_BARRING_SS_CODE                         0x90    /*所有呼叫禁止*/
#define     TAF_BARRING_OF_OUTGOING_CALLS_SS_CODE           0x91
#define     TAF_BAOC_SS_CODE                                0x92    /*禁止所有出局呼叫*/
#define     TAF_BOIC_SS_CODE                                0x93    /*禁止国际出局呼叫*/
#define     TAF_BOICEXHC_SS_CODE                            0x94    /*禁止所有除归属国PLMN外的国际出局呼叫*/
#define     TAF_BARRING_OF_INCOMING_CALLS_SS_CODE           0x99
#define     TAF_BAIC_SS_CODE                                0x9A    /*禁止所有入局呼叫*/
#define     TAF_BICROAM_SS_CODE                             0x9B    /*漫游时，禁止入局呼叫*/

#define     TAF_ALL_PLMN_SPECIFIC_SS_CODE                   0xF0    /*所有PLMNd定义的SS-CODE*/
#define     TAF_PLMN_SPECIFIC_1_SS_CODE                     0xF1
#define     TAF_PLMN_SPECIFIC_2_SS_CODE                     0xF2
#define     TAF_PLMN_SPECIFIC_3_SS_CODE                     0xF3
#define     TAF_PLMN_SPECIFIC_4_SS_CODE                     0xF4
#define     TAF_PLMN_SPECIFIC_5_SS_CODE                     0xF5
#define     TAF_PLMN_SPECIFIC_6_SS_CODE                     0xF6
#define     TAF_PLMN_SPECIFIC_7_SS_CODE                     0xF7
#define     TAF_PLMN_SPECIFIC_8_SS_CODE                     0xF8
#define     TAF_PLMN_SPECIFIC_9_SS_CODE                     0xF9
#define     TAF_PLMN_SPECIFIC_A_SS_CODE                     0xFA
#define     TAF_PLMN_SPECIFIC_B_SS_CODE                     0xFB
#define     TAF_PLMN_SPECIFIC_C_SS_CODE                     0xFC
#define     TAF_PLMN_SPECIFIC_D_SS_CODE                     0xFD
#define     TAF_PLMN_SPECIFIC_E_SS_CODE                     0xFE
#define     TAF_PLMN_SPECIFIC_F_SS_CODE                     0xFF
#define     TAF_EMLPP_SS_CODE                               0xA1    /*增强型多级优先和抢占*/


typedef      TAF_UINT16         TAF_SS_PROBLEM;



/*********************BasicService定义**************************/
typedef     TAF_UINT8           TAF_BASIC_SERVICE_TYPE;
#define     TAF_SS_BEARER_SERVICE                           0x02
#define     TAF_SS_TELE_SERVICE                             0x03
/****************Teleservice Codes定义***************************/
typedef     TAF_UINT8           TAF_BASIC_SERVICE_CODE;
#define     TAF_ALL_TELESERVICES_TSCODE                     0x00

#define     TAF_ALL_SPEECH_TRANSMISSION_SERVICES_TSCODE     0x10
#define     TAF_TELEPHONY_TSCODE                            0x11
#define     TAF_EMERGENCY_CALLS_TSCODE		                0x12

#define     TAF_ALL_SMS_SERVICES_TSCODE                     0x20
#define     TAF_SMS_MT_PP_TSCODE                            0x21
#define     TAF_SMS_MO_PP_TSCODE                            0x22

#define     TAF_ALL_FACSIMILE_TRANSMISSION_SERVICES_TSCODE  0x60
#define     TAF_FACSIMILE_GROUP3_AND_ALTER_SPEECH_TSCODE    0x61
#define     TAF_AUTOMATIC_FACSIMILE_GROUP3_TSCODE           0x62
#define     TAF_FACSIMILE_GROUP4_TSCODE                     0x63

#define     TAF_ALL_DATA_TELESERVICES_TSCODE                0x70
#define     TAF_ALL_TELESERVICES_EXEPTSMS_TSCODE            0x80

#define     TAF_ALL_VOICE_GROUP_CALL_SERVICES_TSCODE        0x90
#define     TAF_VOICE_GROUP_CALL_TSCODE		                0x91
#define     TAF_VOICE_BROADCAST_CALL_TSCODE                 0x92

#define     TAF_ALL_PLMN_SPECIFICTS_TSCODE                  0xD0
#define     TAF_PLMN_SPECIFICTS_1_TSCODE                    0xD1
#define     TAF_PLMN_SPECIFICTS_2_TSCODE                    0xD2
#define     TAF_PLMN_SPECIFICTS_3_TSCODE                    0xD3
#define     TAF_PLMN_SPECIFICTS_4_TSCODE                    0xD4
#define     TAF_PLMN_SPECIFICTS_5_TSCODE                    0xD5
#define     TAF_PLMN_SPECIFICTS_6_TSCODE                    0xD6
#define     TAF_PLMN_SPECIFICTS_7_TSCODE                    0xD7
#define     TAF_PLMN_SPECIFICTS_8_TSCODE                    0xD8
#define     TAF_PLMN_SPECIFICTS_9_TSCODE                    0xD9
#define     TAF_PLMN_SPECIFICTS_A_TSCODE                    0xDA
#define     TAF_PLMN_SPECIFICTS_B_TSCODE                    0xDB
#define     TAF_PLMN_SPECIFICTS_C_TSCODE                    0xDC
#define     TAF_PLMN_SPECIFICTS_D_TSCODE                    0xDD
#define     TAF_PLMN_SPECIFICTS_E_TSCODE                    0xDE
#define     TAF_PLMN_SPECIFICTS_F_TSCODE                    0xDF

/*********************BEARER SERVICE CODES***********************/
#define     TAF_ALL_BEARERSERVICES_BSCODE                   0x00

#define     TAF_ALL_DATACDA_SERVICES_BSCODE                 0x10
#define     TAF_DATACDA_300BPS_BSCODE		                0x11
#define     TAF_DATACDA_1200BPS_BSCODE                      0x12
#define     TAF_DATACDA_1200_75BPS_BSCODE                   0x13
#define     TAF_DATACDA_2400BPS_BSCODE                      0x14
#define     TAF_DATACDA_4800BPS_BSCODE                      0x15
#define     TAF_DATACDA_9600BPS_BSCODE                      0x16
#define     TAF_GENERAL_DATACDA_BSCODE                      0x17
#define     TAF_ALL_DATACDS_SERVICES_BSCODE                 0x18
#define     TAF_DATACDS_1200BPS_BSCODE                      0x1A
#define     TAF_DATACDS_2400BPS_BSCODE                      0x1C
#define     TAF_DATACDS_4800BPS_BSCODE                      0x1D
#define     TAF_DATACDS_9600BPS_BSCODE                      0x1E
#define     TAF_GENERAL_DATACDS_BSCODE                      0x1F

#define     TAF_ALL_PADACCESSCA_SERVICES_BSCODE             0x20
#define     TAF_PADACCESSCA_300BPS_BSCODE                   0x21
#define     TAF_PADACCESSCA_1200BPS_BSCODE                  0x22
#define     TAF_PADACCESSCA_1200_75BPS_BSCODE               0x23
#define     TAF_PADACCESSCA_2400BPS_BSCODE                  0x24
#define     TAF_PADACCESSCA_4800BPS_BSCODE                  0x25
#define     TAF_PADACCESSCA_9600BPS_BSCODE                  0x26
#define     TAF_GENERAL_PADACCESSCA_BSCODE                  0x27
#define     TAF_ALL_DATAPDS_SERVICES_BSCODE                 0x28
#define     TAF_DATAPDS_2400BPS_BSCODE                      0x2C
#define     TAF_DATAPDS_4800BPS_BSCODE                      0x2D
#define     TAF_DATAPDS_9600BPS_BSCODE                      0x2E
#define     TAF_GENERAL_DATAPDS_BSCODE                      0x2F

#define     TAF_ALL_ALTERNATE_SPEECH_DATACDA_BSCODE         0x30
#define     TAF_ALL_ALTERNATE_SPEECH_DATACDS_BSCODE         0x38

#define     TAF_ALL_SPEECH_FOLLOWED_BY_DATACDA_BSCODE       0x40
#define     TAF_ALL_SPEECH_FOLLOWED_BY_DATACDS_BSCODE       0x48

#define     TAF_ALL_DATA_CIRCUIT_ASYNCHRONOUS_BSCODE        0x50
#define     TAF_ALL_ASYNCHRONOUS_SERVICES_BSCODE            0x60
#define     TAF_ALL_DATA_CIRCUIT_SYNCHRONOUS_BSCODE         0x58
#define     TAF_ALL_SYNCHRONOUS_SERVICES_BSCODE             0x68

#define     TAF_ALL_PLMN_SPECIFICBS_BSCODE                  0xD0
#define     TAF_PLMN_SPECIFICBS_1_BSCODE                    0xD1
#define     TAF_PLMN_SPECIFICBS_2_BSCODE                    0xD2
#define     TAF_PLMN_SPECIFICBS_3_BSCODE                    0xD3
#define     TAF_PLMN_SPECIFICBS_4_BSCODE                    0xD4
#define     TAF_PLMN_SPECIFICBS_5_BSCODE                    0xD5
#define     TAF_PLMN_SPECIFICBS_6_BSCODE                    0xD6
#define     TAF_PLMN_SPECIFICBS_7_BSCODE                    0xD7
#define     TAF_PLMN_SPECIFICBS_8_BSCODE                    0xD8
#define     TAF_PLMN_SPECIFICBS_9_BSCODE                    0xD9
#define     TAF_PLMN_SPECIFICBS_A_BSCODE                    0xDA
#define     TAF_PLMN_SPECIFICBS_B_BSCODE                    0xDB
#define     TAF_PLMN_SPECIFICBS_C_BSCODE                    0xDC
#define     TAF_PLMN_SPECIFICBS_D_BSCODE                    0xDD
#define     TAF_PLMN_SPECIFICBS_E_BSCODE                    0xDE
#define     TAF_PLMN_SPECIFICBS_F_BSCODE                    0xDF


/********************forwardingoptions的定义***************************/
typedef     TAF_UINT8           TAF_SS_FORWARDINGOPTIONS;
#define     TAF_SS_NOTIFICATION_TO_FORWARDING_PARTY         0x80
#define     TAF_SS_REDERECTINT_PRESENTATION                 0x40
#define     TAF_SS_NOTIFICATION_TO_CALLING_PARTY            0x20
#define     TAF_SS_FWDREASON_MS_NOT_REACHABLE               0x00
#define     TAF_SS_FWDREASON_MS_BUSY                        0x02
#define     TAF_SS_FWDREASON_MS_NOREPLY                     0x04
#define     TAF_SS_FWDREASON_MS_UNCONDITION                 0x06

/********************一些参数限定的范围********************************/
#define     TAF_SS_MAX_FORWARDED_TO_NUM_LEN                        40
#define     TAF_SS_MAX_ENCODE_FWD_TO_NUM_LEN                       20
#define     TAF_SS_MAX_FORWARDED_TO_SUBADDRESS_LEN                 20
#define     TAF_SS_MAX_ENCODE_FWD_TO_SUBADDR_LEN                   21
#define     TAF_SS_MAX_NUM_OF_FW_FEATURES                          13
#define     TAF_SS_MAX_LONGFWDNUM_LEN                              40
#define     TAF_SS_MAX_NUM_OF_BASIC_SERVICES                       13
#define     TAF_SS_MAX_NUM_OF_CallBarring_FEATURES                 13
#define     TAF_SS_MAX_NUM_OF_CCBS_FEATURE                         5
#define     TAF_SS_MAX_NUM_OF_BSUBSCRIBER_NUMBER                   40
#define     TAF_SS_MAX_NUM_OF_BSUBSCRIBER_SUBADDRESS               21
#define     TAF_SS_MAX_NUM_OF_USERDATA                             200
#define     TAF_SS_MAX_USSDSTRING_LEN                              182
#define     TAF_SS_MAX_USS_CHAR                                    160
#define     TAF_SS_MAX_MSISDN_LEN                                  20
#define     TAF_SS_MAX_PASSWORD_LEN                                4
#define     TAF_SS_MAX_UNPARSE_PARA_LEN                            255
#define     TAF_SS_MAX_USSD_CHAR_HEX_FORMAT                        (TAF_SS_MAX_USS_CHAR * 2)


/********************SS错误原因值*************************************/
/*补充业务错误码*/
#define TAF_ERR_SS_ILLEGAL_SUBSCRIBER               (TAF_ERR_SS_BASE + 9)   /*非法签约用户*/
#define TAF_ERR_SS_BEARERSERVICE_NOT_PROVISIONED    (TAF_ERR_SS_BASE + 10)   /*承载业务未提供*/
#define TAF_ERR_SS_TELESERVICE_NOT_PROVISIONED      (TAF_ERR_SS_BASE + 11)   /*电信业务未提供*/
#define TAF_ERR_SS_ILLEGAL_EQUIPMENT                (TAF_ERR_SS_BASE + 12)   /*非法设备*/
#define TAF_ERR_SS_CALL_BARRED                      (TAF_ERR_SS_BASE + 13)   /*呼叫无关签约用户控制过程被禁止*/
#define TAF_ERR_SS_ILLEGALSS_OPERATION              (TAF_ERR_SS_BASE + 16)   /*非法补充业务操作*/
#define TAF_ERR_SS_ERROR_STATUS                     (TAF_ERR_SS_BASE + 17)   /*网络侧状态错误*/
#define TAF_ERR_SS_NOT_AVAILABLE                    (TAF_ERR_SS_BASE + 18)   /*操作不可用*/
#define TAF_ERR_SS_SUBSCRIPTION_VIOLATION           (TAF_ERR_SS_BASE + 19)   /*违反签约规定*/
#define TAF_ERR_SS_INCOMPATIBILITY                  (TAF_ERR_SS_BASE + 20)  /*操作不兼容*/
#define TAF_ERR_SS_ABSENT_SUBSCRIBER                (TAF_ERR_SS_BASE + 27)  /*签约用户已经激活detach业务或系统缺乏条件*/
#define TAF_ERR_SS_SYSTEM_FAILURE                   (TAF_ERR_SS_BASE + 34)  /*系统故障*/
#define TAF_ERR_SS_DATA_MISSING                     (TAF_ERR_SS_BASE + 35)  /*可选项数据缺失*/
#define TAF_ERR_SS_UNEXPECTED_DATA_VALUE            (TAF_ERR_SS_BASE + 36)  /*参数值有误*/
#define TAF_ERR_SS_PW_REGISTRATION_FAILURE          (TAF_ERR_SS_BASE + 37)  /*密码注册失败*/
#define TAF_ERR_SS_NEGATIVE_PASSWORD_CHECK          (TAF_ERR_SS_BASE + 38)  /*密码错误*/
#define TAF_ERR_SS_NUMBER_OF_PW_ATTEMPTS_VIOLATION  (TAF_ERR_SS_BASE + 43)  /*密码尝试次数超过上限*/
#define TAF_ERR_SS_UNKNOWN_ALPHABET                 (TAF_ERR_SS_BASE + 71)  /*USSD字符编码不支持*/
#define TAF_ERR_SS_USSD_BUSY                        (TAF_ERR_SS_BASE + 72)  /*当前无法进行USSD操作*/
#define TAF_ERR_SS_NO_PASSWORD                      (TAF_ERR_SS_BASE + 73)      /* 无操作要求的密码 */

#define TAF_ERR_IMSA_USSD_BUSY                      (TAF_ERR_SS_IMSA_BASE + 1)  /*当前无法进行USSD操作*/
#define TAF_ERR_IMSA_SRVCCING_BUFF_MSG              (TAF_ERR_SS_IMSA_BASE + 2)  /*SRVCC过程中的USSD缓存,在SRVCC成功后通过此原因通知*/
#define TAF_ERR_IMSA_INTERUPT_BY_SRVCC_SUCC         (TAF_ERR_SS_IMSA_BASE + 3)  /*SRVCC成功打断当前USSD流程*/
#define TAF_ERR_IMSA_WAIT_NET_TIMEOUT               (TAF_ERR_SS_IMSA_BASE + 4)  /*等待网侧定时器超时*/
#define TAF_ERR_IMSA_WAIT_APP_TIMEOUT               (TAF_ERR_SS_IMSA_BASE + 5)  /*等待APP定时器超时*/
#define TAF_ERR_IMSA_SRVCCING_BUFF_MSG_FAIL         (TAF_ERR_SS_IMSA_BASE + 7)  /*SRVCC过程中缓存USSD消息失败*/
#define TAF_ERR_IMSA_SRVCC_ABNORMAL                 (TAF_ERR_SS_IMSA_BASE + 8)  /* SRVCC异常，例如关机等 */
#define TAF_ERR_IMSA_SRVCC_ABNORMAL_DEREG           (TAF_ERR_SS_IMSA_BASE + 9)  /* SRVCC过程中出现DEREG */


#define TAF_ERR_IMSA_USSD_UNSPECIFIC                (TAF_ERR_SS_IMSA_BASE + 100)  /*当前USSD错误不详*/


/********Ivoke和return result的参数 begin*****************************/
typedef     TAF_UINT8       TAF_SS_CCBSINDEX;
typedef     TAF_UINT8       TAF_SS_NOREPLYCONDITIONTIME;
typedef     TAF_UINT8       TAF_SS_DEFAULTPRIORITY;
typedef     TAF_UINT8       TAF_SS_NBRUSER;
typedef     TAF_UINT8       TAF_SS_NBRSN;
typedef     TAF_UINT8       TAF_SS_NBRSB;
typedef     TAF_UINT8       TAF_SS_MAXENTITLEDPRIORITY;
typedef     TAF_UINT8       TAF_SS_NUMTYPE;
typedef     TAF_UINT8       TAF_SS_SUBADDRTYPE;
typedef     TAF_UINT8       TAF_SS_CAUSE;

typedef struct
{
    TAF_UINT8   ucStatus;        /* 1: NV有效标志位，0：无效 */
    TAF_UINT8   ucUssdTransMode;
    TAF_UINT8   aucRsv[2];
}USSD_TRANS_MODE_STRU;

typedef struct
{
    TAF_BASIC_SERVICE_TYPE          BsType;
    TAF_BASIC_SERVICE_CODE          BsServiceCode;
    TAF_UINT8                       aucRsv[2];
}TAF_SS_BASIC_SERVICE_STRU;

/*SS-TAF  ENUM: cliRestrictionOption*/
typedef     TAF_UINT8   TAF_SS_CLI_RESTRICION_OPTION;
#define     TAF_SS_CLI_PERMANENT                0
#define     TAF_SS_CLI_TMP_DEFAULT_RESTRICTED   1
#define     TAF_SS_CLI_TMP_DEFAULT_ALLOWED      2


/*SS-TAF ENUM: overrideCategory*/
typedef     TAF_UINT8   TAF_SS_OVERRIDE_CATEGORY;
#define     TAF_SS_OVERRIDE_ENABLEd             0
#define     TAF_SS_OVERRIDE_DISABLED            1


/*SS-TAF union: ss-SubscriptionOption*/
typedef      TAF_UINT8  TAF_SS_SUBSCRIPTIONOPTION_VALUE;
typedef      TAF_UINT8  TAF_SS_SUBSCRIPTIONOPTION_CHOICE;
#define      TAF_SS_CLI_STRICTION_OP   2
#define      TAF_SS_OVERIDE_CATEGORY   1

typedef struct
{
    TAF_SS_SUBSCRIPTIONOPTION_CHOICE            SubScriptionOptionChoice;
    TAF_SS_SUBSCRIPTIONOPTION_VALUE             SubScriptionOptionValue;
    TAF_UINT8                                   aucRsv[2];
}TAF_SS_SSSUBSCRIPTION_OP_STRU;


/*SS-TAF structrue forwardingFeature*/
typedef struct
{
    TAF_UINT32                              OP_BsService:1;
    TAF_UINT32                              OP_SsStatus:1;
    TAF_UINT32                              OP_NumType:1;
    TAF_UINT32                              OP_FwdToNum:1;
    TAF_UINT32                              OP_SubAddrType:1;
    TAF_UINT32                              OP_FwdToSubAddr:1;
    TAF_UINT32                              OP_FwdOption:1;
    TAF_UINT32                              OP_NoRepCondTime:1;
    TAF_UINT32                              OP_LongFwdNumType:1;
    TAF_UINT32                              OP_LongFwdToNum:1;
    TAF_UINT32                              OP_Spare:22;


    TAF_SS_BASIC_SERVICE_STRU               BsService;

    TAF_SS_STATUS                           SsStatus;
    TAF_SS_NUMTYPE                          NumType;
    TAF_UINT8                               aucFwdToNum[TAF_SS_MAX_FORWARDED_TO_NUM_LEN + 1];
    TAF_SS_SUBADDRTYPE                      SubAddrType;

    TAF_UINT8                               aucFwdToSubAddr[TAF_SS_MAX_FORWARDED_TO_SUBADDRESS_LEN + 1];
    TAF_SS_FORWARDINGOPTIONS                FwdOption;
    TAF_SS_NOREPLYCONDITIONTIME             NoRepCondTime;
    TAF_SS_NUMTYPE                          LongFwdNumType;

    TAF_UINT8                               aucLongFwdToNum[TAF_SS_MAX_LONGFWDNUM_LEN + 1];
    TAF_UINT8                               aucRsv[3];
}TAF_SS_FWDFEATURE_STRU;

/*SS-TAF structrue forwardingFeatureList*/
typedef struct
{
    TAF_UINT8                               ucCnt;
    TAF_UINT8                               aucRsv[3];
    TAF_SS_FWDFEATURE_STRU                  astFwdFtr[TAF_SS_MAX_NUM_OF_FW_FEATURES];
}TAF_SS_FWDFEATURELIST_STRU;

/*SS-TAF structure forwardingInfo*/
typedef struct
{
    TAF_UINT32                              OP_SsCode:1;
    TAF_UINT32                              OP_Spare:31;

    TAF_SS_CODE                             SsCode;
    TAF_UINT8                               aucRsv[3];
    TAF_SS_FWDFEATURELIST_STRU              FwdFeaTurelist;
}TAF_SS_FORWARDINGINFO_STRU;

/*SS-TAF  structure:  callBarringFeature*/
typedef struct
{
    TAF_UINT32                              OP_BsService:1;
    TAF_UINT32                              OP_SsStatus:1;
    TAF_UINT32                              OP_Spare:30;

    TAF_SS_BASIC_SERVICE_STRU               BsService;
    TAF_SS_STATUS                           SsStatus;
    TAF_UINT8                               aucRsv[3];
}TAF_SS_CALLBARRINGFEATURE_STRU;

/*SS-TAF  structure:  callBarringFeatureList*/
typedef struct
{
    TAF_UINT8                               ucCnt;
    TAF_UINT8                               aucRsv[3];
    TAF_SS_CALLBARRINGFEATURE_STRU          astCallBarFtr[TAF_SS_MAX_NUM_OF_CallBarring_FEATURES];
}TAF_SS_CALLBARFEATURELIST_STRU;


/*SS-TAF structure:  callBarringInfo*/
typedef struct
{
    TAF_UINT32                              OP_SsCode:1;
    TAF_UINT32                              OP_Spare:31;

    TAF_SS_CODE                             SsCode;
    TAF_UINT8                               aucRsv[3];
    TAF_SS_CALLBARFEATURELIST_STRU          CallBarFtrList;
}TAF_SS_CALLBRARINGINFO_STRU;


/*SS-TAF structure:  basicServiceGroupList*/
typedef struct
{
    TAF_UINT8                               ucCnt;
    TAF_UINT8                               aucRsv[3];
    TAF_SS_BASIC_SERVICE_STRU               astBsService[TAF_SS_MAX_NUM_OF_BASIC_SERVICES];
}TAF_SS_BS_SERV_GROUPLIST_STRU;

/*SS-TAF structure:  ss-Data*/
typedef struct
{
    TAF_UINT32                              OP_SsCode:1;
    TAF_UINT32                              OP_SsStatus:1;
    TAF_UINT32                              OP_SsSubscriptionOp:1;
    TAF_UINT32                              OP_BsServGroupList:1;
    TAF_UINT32                              OP_DefaultPrio:1;
    TAF_UINT32                              OP_NbrUser:1;
    TAF_UINT32                              OP_Spare:26;

    TAF_SS_CODE                             SsCode;
    TAF_SS_STATUS                           SsStatus;
    TAF_UINT8                               aucRsv[2];

    TAF_SS_SSSUBSCRIPTION_OP_STRU           SsSubScriptionOp;
    TAF_SS_BS_SERV_GROUPLIST_STRU           BsServGroupList;
    TAF_SS_DEFAULTPRIORITY                  DefaultPrio;
    TAF_SS_NBRUSER                          NbrUser;
    TAF_UINT8                               aucRsv1[2];
}TAF_SS_SSDATA_STRU;

/*SS-TAF structure: ccbs-Feature*/

typedef struct
{
    TAF_UINT32                              OP_CcbsIndex:1;
    TAF_UINT32                              OP_NumType:1;
    TAF_UINT32                              OP_BSubscriberNum:1;
    TAF_UINT32                              OP_SubAddrType:1;
    TAF_UINT32                              OP_BSubscriberSubAddr:1;
    TAF_UINT32                              OP_BsService:1;
    TAF_UINT32                              OP_Spare:26;

    TAF_SS_CCBSINDEX                        CcbsIndex;
    TAF_SS_NUMTYPE                          NumType;
    TAF_UINT8                               aucBSubscriberNum[TAF_SS_MAX_NUM_OF_BSUBSCRIBER_NUMBER + 1];
    TAF_SS_SUBADDRTYPE                      SubAddrType;

    TAF_UINT8                               aucBSubscriberSubAddr[TAF_SS_MAX_NUM_OF_BSUBSCRIBER_SUBADDRESS + 1];
    TAF_UINT8                               aucRsv[2];
    TAF_SS_BS_SERV_GROUPLIST_STRU           BsServGroupList;
}TAF_SS_CCBS_FEATURE_STRU;

/*SS-TAF structure: ccbs-FeatureList*/
typedef struct
{
    TAF_UINT8                               ucCnt;
    TAF_UINT8                               aucRsv[3];
    TAF_SS_CCBS_FEATURE_STRU                astCcBsFeature[TAF_SS_MAX_NUM_OF_CCBS_FEATURE];
}TAF_SS_CCBS_FEATURELIST_STRU;

/*SS-TAF structure:  genericServiceInfo*/
typedef struct
{
    TAF_UINT32                              OP_CliStrictOp:1;
    TAF_UINT32                              OP_MaxEntiledPrio:1;
    TAF_UINT32                              OP_DefaultPrio:1;
    TAF_UINT32                              OP_CcbsFeatureList:1;
    TAF_UINT32                              OP_NbrSb:1;
    TAF_UINT32                              OP_NbrUser:1;
    TAF_UINT32                              OP_NbrSn:1;
    TAF_UINT32                              OP_Spare:25;

    TAF_SS_STATUS                           SsStatus;
    TAF_SS_CLI_RESTRICION_OPTION            CliRestrictionOp;
    TAF_SS_MAXENTITLEDPRIORITY              MaxEntitledPrio;
    TAF_SS_DEFAULTPRIORITY                  DefaultPrio;

    TAF_SS_CCBS_FEATURELIST_STRU            CcbsFeatureList;
    TAF_SS_NBRSB                            NbrSb;
    TAF_SS_NBRUSER                          NbrUser;
    TAF_SS_NBRSN                            NbrSn;
    TAF_UINT8                               ucRsv;
}TAF_SS_GENERIC_SERV_INFO_STRU;

typedef    TAF_UINT8        TAF_SS_GUIDANCE_INFO;
#define    TAF_SS_ENTER_PASSWORD                0
#define    TAF_SS_ENTER_NEW_PASSWORD            1
#define    TAF_SS_ENTER_NEW_PASSWORD_AGAIN      2

typedef struct
{
    TAF_UINT16                              usCnt;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
    VOS_UINT8                               aucReserved[2];
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */

    TAF_UINT8                               aucUssdStr[TAF_SS_MAX_USSDSTRING_LEN*2];
}TAF_SS_USSD_STRING_STRU;


/*1. SS-TAF struture: RegisterSS-invoke   MS->NETWORK*/
typedef struct
{
    TAF_UINT32                              OP_BsService:1;
    TAF_UINT32                              OP_NumType:1;
    TAF_UINT32                              OP_FwdToNum:1;
    TAF_UINT32                              OP_SubAddrType:1;
    TAF_UINT32                              OP_FwdToAddr:1;
    TAF_UINT32                              OP_NoRepCondTime:1;
    TAF_UINT32                              OP_DefaultPrio:1;
    TAF_UINT32                              OP_NbrUser:1;
    TAF_UINT32                              OP_LongFTN_Supported:1;
    TAF_UINT32                              OP_Spare:23;

    TAF_SS_CODE                             SsCode;
    TAF_SS_BASIC_SERVICE_STRU               BsService;

    TAF_SS_NUMTYPE                          NumType;
    TAF_UINT8                               aucFwdToNum[TAF_SS_MAX_FORWARDED_TO_NUM_LEN + 1];
    TAF_SS_SUBADDRTYPE                      SubAddrType;
    TAF_UINT8                               aucFwdToSubAddr[TAF_SS_MAX_FORWARDED_TO_SUBADDRESS_LEN + 1];
    TAF_SS_NOREPLYCONDITIONTIME             NoRepCondTime;
    TAF_SS_DEFAULTPRIORITY                  DefaultPrio;
    TAF_SS_NBRUSER                          NbrUser;
}TAF_SS_REGISTERSS_REQ_STRU;

typedef    TAF_UINT8   TAF_SS_VERIFICATIONRES;
#define    TAF_SS_PERMISSIONDENIED     0
#define    TAF_SS_PERMISSIONGRANTED    1


#define         TAF_SS_REG_FWD_INFO          0
#define         TAF_SS_REG_CALL_BAR_INFO     1
#define         TAF_SS_REG_SS_DATA           2

/* Added by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
/*****************************************************************************
 枚举名    : TAF_SS_CUSD_TYPE_ENUM_UINT8
 结构说明  : cusd设置的类型
 1.日    期   : 2014年4月8日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum TAF_SS_CUSD_TYPE_ENUM
{
    TAF_SS_CUSD_TYPE_DISABLE                  = 0,
    TAF_SS_CUSD_TYPE_ENABLE                   = 1,
    TAF_SS_CUSD_TYPE_CANCEL                   = 2,
    TAF_SS_CUSD_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SS_CUSD_TYPE_ENUM_UINT8;

/* Added by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-8, end */


/*2. SS-TAF struture: EraseSS-invoke       MS->NETWORK*/
/*****************************************************************************
 结构名    : TAF_SS_ERASESS_REQ_STRU
 结构说明  : 补充业务激活,去激活,删除和查询操作信息结构
 1.日    期   : 2013年05月07日
   作    者   : f62575
   修改内容   : 补充密码字段
*****************************************************************************/
typedef  struct
{
    TAF_UINT32                              OP_BsService:1;
    TAF_UINT32                              OP_LongFTN_Supported:1;
    TAF_UINT32                              OP_Password:1;
    TAF_UINT32                              OP_Spare:29;

    /**选择bearerService(SS_BEARER_SERVICE:0)还是teleService(SS_TELE_SERVICE1)**/
    TAF_SS_CODE                             SsCode;
    VOS_UINT8                               aucReserved1[3];
    TAF_SS_BASIC_SERVICE_STRU               BsService;
    TAF_UINT8                               aucPassword[TAF_SS_MAX_PASSWORD_LEN];                 /* 指示Clck密码 */
}TAF_SS_ERASESS_REQ_STRU;


/*3. SS-TAF struture: ActivateSS-invoke    MS->NETWORK*/
typedef  TAF_SS_ERASESS_REQ_STRU            TAF_SS_ACTIVATESS_REQ_STRU;


/*4. SS-TAF struture: DeactivateSS-invoke  MS->NETWORK*/
typedef  TAF_SS_ERASESS_REQ_STRU            TAF_SS_DEACTIVATESS_REQ_STRU;


/*5. SS-TAF struture: interrogateSS-invoke   MS->NETWORK*/
typedef  TAF_SS_ERASESS_REQ_STRU            TAF_SS_INTERROGATESS_REQ_STRU;



/*6. SS-TAF struct: registerPassword-invoke   MS->NETWORK*/
typedef struct
{
    TAF_SS_CODE                             SsCode;
    VOS_UINT8                               aucReserved[3];
    TAF_UINT8                               aucOldPwdStr[TAF_SS_MAX_PASSWORD_LEN];
    TAF_UINT8                               aucNewPwdStr[TAF_SS_MAX_PASSWORD_LEN];
    TAF_UINT8                               aucNewPwdStrCnf[TAF_SS_MAX_PASSWORD_LEN];
}TAF_SS_REGPWD_REQ_STRU;


/*6. SS-TAF struture: registerPassword-result   NETWORK->MS*/
typedef struct
{
    TAF_UINT8                               aucPwdStr[TAF_SS_MAX_PASSWORD_LEN];
}TAF_SS_PASSWORD_STRU;

/*7.  SS-TAF struct: GetPassword-invoke    NETWORK->MS*/
typedef struct
{
    TAF_SS_GUIDANCE_INFO                    GuidanceInfo;
}TAF_SS_GETPWD_IND_STRU;

/*7.  SS-TAF struct: GetPassword-result    MS->NETWORK*/
typedef struct
{
    TAF_UINT8                               aucPwdStr[TAF_SS_MAX_PASSWORD_LEN];
}TAF_SS_GETPWD_RSP_STRU;

/*8. SS-TAF  forwardCheckSS-Indication 无参数*/

typedef       TAF_UINT8           TAF_SS_DATA_CODING_SCHEME;
#define       TAF_SS_7bit_LANGUAGE_UNSPECIFIED         0x0f
#define       TAF_SS_8bit                              0x44
#define       TAF_SS_UCS2                              0x48
#define       TAF_SS_7BIT_DATA_CODING                  0xf0


/*9. TAF-SS  struct:processUnstructuredSS-Request -result  MS->NETWORK*/
typedef struct
{
    TAF_UINT32                              OP_AlertingPattern:1;
    TAF_UINT32                              OP_Msisdn:1;
    TAF_UINT32                              OP_Spare:30;

    TAF_SS_USSD_STRING_STRU                 UssdStr;

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
    TAF_SS_CUSD_TYPE_ENUM_UINT8             enCusdType;
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, end */
    TAF_SS_DATA_CODING_SCHEME               DatacodingScheme;
    TAF_SS_ALERTINGPATTERN                  AlertingPattern;
    TAF_UINT8                               aucMsisdn[TAF_SS_MAX_MSISDN_LEN + 1];
}TAF_SS_PROCESS_USS_REQ_STRU;

/*9. SS-TAF struct:processUnstructuredSS-Request -result  NETWORK->MS*/
typedef struct
{
    TAF_SS_DATA_CODING_SCHEME               DataCodeScheme;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-10, begin */
    TAF_SS_CUSD_TYPE_ENUM_UINT8             enCusdType;
    VOS_UINT8                               aucReserved[2];
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-10, end */

    TAF_SS_USSD_STRING_STRU                 UssdStr;
}TAF_SS_PROCESS_USS_CNF_STRU;

/*10. SS-TAF  struct:unstructuredSS-Request -invoke  NETWORK->MS*/
typedef  TAF_SS_PROCESS_USS_REQ_STRU        TAF_SS_USS_IND_STRU;

/*10. TAF_SS struct:unstructuredSS-Request -result  MS->NETWORK*/
typedef TAF_SS_PROCESS_USS_CNF_STRU         TAF_SS_USS_RSP_STRU;

/*12. SS-TAF  struct:eraseCCEntry -invoke MS->NETWORK*/
typedef struct
{
    TAF_UINT32                              OP_CcbsIndex:1;
    TAF_UINT32                              OP_Spare:31;

    TAF_SS_CODE                             SsCode;
    TAF_SS_CCBSINDEX                        CcbsIndex;
    VOS_UINT8                               aucReserved[2];
}TAF_SS_ERASECC_ENTRY_REQ_STRU;

/*12. SS-TAF  struct:eraseCCEntry -result  NETWORK->MS*/
typedef struct
{
    TAF_UINT32                              OP_SsStatus:1;
    TAF_UINT32                              OP_Spare:31;

    TAF_SS_CODE                             SsCode;
    TAF_SS_STATUS                           SsStatus;
    VOS_UINT8                               aucReserved[2];
}TAF_SS_ERASECC_ENTRY_CNF_STRU;



/*13. SS-TAF  struct:eraseCCEntry -invoke  MS->NETWORK*/
typedef struct
{
    TAF_UINT8                               ucCnt;
    TAF_UINT8                               aucUserData[TAF_SS_MAX_NUM_OF_USERDATA];
}TAF_SS_PROCESS_USSDATA_REQ_STRU;

typedef struct
{
    TAF_UINT8                               ucCnt;
    TAF_UINT8                               aucUnParsePara[TAF_SS_MAX_UNPARSE_PARA_LEN];

}TAF_SS_UNPARSE_PARA_STRU;

/********Invoke和return result的参数 end*****************************/

typedef     TAF_UINT8                      TAF_SS_EVENT;
#define     TAF_SS_EVT_ERROR                                0
#define     TAF_SS_EVT_REGISTERSS_CNF                       1
#define     TAF_SS_EVT_ERASESS_CNF                          2
#define     TAF_SS_EVT_ACTIVATESS_CNF                       3
#define     TAF_SS_EVT_DEACTIVATESS_CNF                     4
#define     TAF_SS_EVT_INTERROGATESS_CNF                    5
#define     TAF_SS_EVT_REG_PASSWORD_CNF                     6
#define     TAF_SS_EVT_GET_PASSWORD_IND                     7
#define     TAF_SS_EVT_PROCESS_USS_REQ_CNF                  8
#define     TAF_SS_EVT_USS_REQ_IND                          9
#define     TAF_SS_EVT_USS_NOTIFY_IND                       10
#define     TAF_SS_EVT_USS_RELEASE_COMPLETE_IND             11
#define     TAF_SS_EVT_ERASE_CC_ENTRY_CNF                   12
#define     TAF_SS_EVT_USSD_DATA_SND                        13
#define     TAF_SS_EVT_PROBLEM                              14



/*呼叫无关事件上报参数*/
typedef struct
{
    TAF_UINT32                              OP_Cause:1;
    TAF_UINT32                              OP_Error:1;
    TAF_UINT32                              OP_BsService:1;
    TAF_UINT32                              OP_FwdInfo:1;
    TAF_UINT32                              OP_CallBarInfo:1;
    TAF_UINT32                              OP_SsData:1;
    TAF_UINT32                              OP_SsCode:1;
    TAF_UINT32                              OP_SsStatus:1;
    TAF_UINT32                              OP_BsServGroupList:1;
    TAF_UINT32                              OP_FwdFeaturelist:1;
    TAF_UINT32                              OP_GenericServiceInfo:1;
    TAF_UINT32                              OP_PassWord:1;
    TAF_UINT32                              OP_GuidanceInfo:1;
    TAF_UINT32                              OP_DataCodingScheme:1;
    TAF_UINT32                              OP_UssdString:1;
    TAF_UINT32                              OP_AlertingPattern:1;
    TAF_UINT32                              OP_Msisdn:1;
    TAF_UINT32                              OP_USSData:1;
    TAF_UINT32                              OP_UnParsePara:1;
    TAF_UINT32                              OP_ProblemCode:1;
    TAF_UINT32                              OP_Spare:12;

    MN_CLIENT_ID_T                          ClientId;
    MN_OPERATION_ID_T                       OpId;
    TAF_SS_EVENT                            SsEvent;

    TAF_SS_CAUSE                            Cause;
    TAF_UINT8                               ucRsv;
    TAF_SS_ERROR                            ErrorCode;

    TAF_SS_PROBLEM                          ProblemCode;
    VOS_UINT8                               aucRsv[2];

    TAF_SS_BASIC_SERVICE_STRU               BsService;

    TAF_SS_FORWARDINGINFO_STRU              FwdInfo;

    TAF_SS_CALLBRARINGINFO_STRU             CallBarInfo;

    TAF_SS_SSDATA_STRU                      SsData;

    TAF_SS_CODE                             SsCode;
    TAF_SS_STATUS                           SsStatus;
    TAF_UINT8                               aucRsv1[2];

    TAF_SS_BS_SERV_GROUPLIST_STRU           BsServGroupList;
    TAF_SS_FWDFEATURELIST_STRU              FwdFeaturelist;
    TAF_SS_GENERIC_SERV_INFO_STRU           GenericServiceInfo;

    TAF_UINT8                               aucPassWord[TAF_SS_MAX_PASSWORD_LEN];

    TAF_SS_GUIDANCE_INFO                    GuidanceInfo;
    TAF_SS_DATA_CODING_SCHEME               DataCodingScheme;
    TAF_UINT8                               aucRsv2[2];

    TAF_SS_USSD_STRING_STRU                 UssdString;

    TAF_SS_ALERTINGPATTERN                  AlertingPattern;
    TAF_UINT8                               aucMsisdn[TAF_SS_MAX_MSISDN_LEN + 1];
    TAF_UINT8                               aucRsv3[2];

    TAF_SS_UNPARSE_PARA_STRU                UnParsePara;
}TAF_SS_CALL_INDEPENDENT_EVENT_STRU;

/*****************定义TAF提供给APP/AT的操作接口函数********************/
/*RegisterSS操作*/
/*lint -esym(752,TAF_RegisterSSReq)*/
TAF_UINT32 TAF_RegisterSSReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_SS_REGISTERSS_REQ_STRU         *para
);

/*EraseSS操作*/
/*lint -esym(752,TAF_EraseSSReq)*/
TAF_UINT32 TAF_EraseSSReq(MN_CLIENT_ID_T                                 ClientId,
                          MN_OPERATION_ID_T                                        OpId,
                          TAF_SS_ERASESS_REQ_STRU                      *pPara);

/*ActivateSS操作*/
/*lint -esym(752,TAF_ActivateSSReq)*/
TAF_UINT32 TAF_ActivateSSReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_SS_ACTIVATESS_REQ_STRU         *pPara
);

/*DeactivateSS操作*/
/*lint -esym(752,TAF_DeactivateSSReq)*/
TAF_UINT32 TAF_DeactivateSSReq(MN_CLIENT_ID_T                             ClientId,
                              MN_OPERATION_ID_T                                    OpId,
                              TAF_SS_DEACTIVATESS_REQ_STRU             *pPara);

/*InterrogateSS操作*/
/*lint -esym(752,TAF_InterrogateSSReq)*/
TAF_UINT32 TAF_InterrogateSSReq(MN_CLIENT_ID_T                           ClientId,
                                MN_OPERATION_ID_T                                  OpId,
                                TAF_SS_INTERROGATESS_REQ_STRU          *pPara);

/*RegisterPassword操作*/
/*lint -esym(752,TAF_RegisterPasswordReq)*/
TAF_UINT32 TAF_RegisterPasswordReq(MN_CLIENT_ID_T                        ClientId,
                                   MN_OPERATION_ID_T                               OpId,
                                   TAF_SS_REGPWD_REQ_STRU              *pPara);

/* 删除GetPassword操作函数TAF_GetPasswordRsp外部引用 */


/*ProcessUnstructuredSS-Request操作*/
/*lint -esym(752,TAF_ProcessUnstructuredSSReq)*/
TAF_UINT32 TAF_ProcessUnstructuredSSReq(MN_CLIENT_ID_T                   ClientId,
                                        MN_OPERATION_ID_T                          OpId,
                                        TAF_SS_PROCESS_USS_REQ_STRU    *pPara);


/*EraseCCEntry操作*/
/*lint -esym(752,TAF_EraseCCEntryReq)*/
TAF_UINT32 TAF_EraseCCEntryReq(MN_CLIENT_ID_T                            ClientId,
                               MN_OPERATION_ID_T                                   OpId,
                               TAF_SS_ERASECC_ENTRY_REQ_STRU           *pPara);


/*ReleaseComplete操作,释放当前操作占用的链路*/
/*lint -esym(752,TAF_SsReleaseComplete)*/
TAF_UINT32 TAF_SsReleaseComplete(MN_CLIENT_ID_T                                  ClientId,
                         MN_OPERATION_ID_T                                         OpId);





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

#endif /* end of TafAppSSa.h */
