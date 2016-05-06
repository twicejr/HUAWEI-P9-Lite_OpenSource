/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasSsIe.h

  修改历史   :

  1.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
******************************************************************************/

#ifndef _NAS_SS_IE_H
#define _NAS_SS_IE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"

/******************************************************************************/
/*  Enumerated Definition                                                     */
/******************************************************************************/

/* [3.6] Facility information element */
/*============================================================================*/
/* 3.6.2 Component type tag */
enum NAS_SS_COMPONET_TYPE_TAG_ENUM
{
    NAS_SS_COMPONENT_TYPE_TAG_INVOKE                        = 0xA1,             /* 1 0 1 0 0 0 0 1 Invoke       */
    NAS_SS_COMPONENT_TYPE_TAG_RTN_RSLT                      = 0xA2,             /* 1 0 1 0 0 0 1 0 Return Rslt  */
    NAS_SS_COMPONENT_TYPE_TAG_RTN_ERR                       = 0xA3,             /* 1 0 1 0 0 0 1 1 Return Error */
    NAS_SS_COMPONENT_TYPE_TAG_REJECT                        = 0xA4              /* 1 0 1 0 0 1 0 0 Reject       */
};
typedef VOS_UINT8 NAS_SS_COMPONET_TYPE_TAG_ENUM_U8;

/* 3.6.3 Component ID tag */
enum NAS_SS_COMPONENT_ID_TAG_ENUM
{
    NAS_SS_COMPONENT_ID_TAG_INVOKE                          = 0x02,             /* 0 0 0 0 0 0 1 0 Invoke ID    */
    NAS_SS_COMPONENT_ID_TAG_LINKED                          = 0x80,             /* 1 0 0 0 0 0 0 0 Linked ID    */
    NAS_SS_COMPONENT_ID_TAG_NULL                            = 0x05              /* 0 0 0 0 0 1 0 1 NULL         */
};
typedef VOS_UINT8 NAS_SS_COMPONENT_ID_TAG_ENUM_U8;


/* 3.6.4 Operation Code */
enum NAS_SS_OPERATION_TAG_ENUM
{
    NAS_SS_OPERATION_CODE_TAG                              = 0x02
};
typedef VOS_UINT8 NAS_SS_OPERATION_TAG_ENUM_U8;

/* 3.6.5 Sequence and Set tags */
enum NAS_SS_SEQUENCE_SET_TAG_ENUM
{
    NAS_SS_SEQUENCE_TAG                                     = 0x30,
    NAS_SS_SET_TAG                                          = 0x31
};
typedef VOS_UINT8 NAS_SS_SEQUENCE_SET_TAG_ENUM_U8;

/* 3.6.6 Error Code */
enum NAS_SS_ERROR_TAG_ENUM
{
    NAS_SS_ERROR_CODE_TAG                                   = 0x02
};
typedef VOS_UINT8 NAS_SS_ERROR_TAG_ENUM_U8;

/* 3.6.7 Problem Code */
enum NAS_SS_PROBLEM_TAG_ENUM
{
    NAS_SS_PROBLEM_TAG_GENERAL                              = 0x80,             /* 1 0 0 0 0 0 0 0 General       */
    NAS_SS_PROBLEM_TAG_INVOKE                               = 0x81,             /* 1 0 0 0 0 0 0 1 Invoke        */
    NAS_SS_PROBLEM_TAG_RTN_RSLT                             = 0x82,             /* 1 0 0 0 0 0 1 0 Return Result */
    NAS_SS_PROBLEM_TAG_RTN_ERR                              = 0x83              /* 1 0 0 0 0 0 1 1 Return Error  */
};
typedef VOS_UINT8 NAS_SS_PROBLEM_TAG_ENUM_U8;

enum NAS_SS_GENERAL_PROBLEM_CODE_ENUM
{
    NAS_SS_GENERAL_PROBLEM_UNRECOGNIZED_COMPONENT           = 0,
    NAS_SS_GENERAL_PROBLEM_MISTYPED_COMPONENT               = 1,
    NAS_SS_GENERAL_PROBLEM_BADLY_STRUCTURED_COMPONENT       = 2
};
typedef VOS_UINT8  NAS_SS_GENERAL_PROBLEM_CODE_ENUM_U8;

enum NAS_SS_INVOKE_PROBLEM_CODE_ENUM
{
    NAS_SS_INVOKE_PROBLEM_DUPLICATE_INVOKE_ID               = 0,
    NAS_SS_INVOKE_PROBLEM_UNRECOGNIZED_OPERATION            = 1,
    NAS_SS_INVOKE_PROBLEM_MISTYPED_PARAMETER                = 2,
    NAS_SS_INVOKE_PROBLEM_RESOURCE_LIMITATION               = 3,
    NAS_SS_INVOKE_PROBLEM_INITIATING_RELEASE                = 4,
    NAS_SS_INVOKE_PROBLEM_UNRECOGNIZED_LINKED_ID            = 5,
    NAS_SS_INVOKE_PROBLEM_LINKED_RESPONSE_UNEXPECTED        = 6,
    NAS_SS_INVOKE_PROBLEM_UNEXPECTED_LINKED_OPERATION       = 7
};
typedef VOS_UINT8  NAS_SS_INVOKE_PROBLEM_CODE_ENUM_U8;

enum NAS_SS_RTN_RSLT_PROBLEM_CODE_ENUM
{
    NAS_SS_RTN_RSLT_PROBLEM_UNRECOGNIZED_INVOKE_ID          = 0,
    NAS_SS_RTN_RSLT_PROBLEM_RETURN_RESULT_UNEXPECTED        = 1,
    NAS_SS_RTN_RSLT_PROBLEM_MISTYPED_PARAMETER              = 2
};
typedef VOS_UINT8  NAS_SS_RTN_RSLT_PROBLEM_CODE_ENUM_U8;

enum NAS_SS_RTN_ERR_PROBLEM_CODE_ENUM
{
    NAS_SS_RTN_ERR_PROBLEM_UNRECOGNIZED_INVOKE_ID           = 0,
    NAS_SS_RTN_ERR_PROBLEM_UNEXPECTED                       = 1,
    NAS_SS_RTN_ERR_PROBLEM_UNRECOGNIZED_ERROR               = 2,
    NAS_SS_RTN_ERR_PROBLEM_UNEXPECTED_ERROR                 = 3,
    NAS_SS_RTN_ERR_PROBLEM_MISTYPED_PARAMETER               = 4
};
typedef VOS_UINT8  NAS_SS_RTN_ERR_PROBLEM_CODE_ENUM_U8;


/* 3.7 Version handling for supplementary services */
/*============================================================================*/
/* 3.7.1 Supplementary service screening indicator */
enum NAS_SS_SCREENING_INDICATOR_ENUM
{
    NAS_SS_SCREENING_INDICATOR_PHASE1                = 0,
    NAS_SS_SCREENING_INDICATOR_PHASE2                = 1,
    NAS_SS_SCREENING_INDICATOR_FUTURE_USE1           = 2,
    NAS_SS_SCREENING_INDICATOR_FUTURE_USE2           = 3
};
typedef VOS_UINT8  NAS_SS_SCREENING_INDICATOR;

/* 3.7.2 Supplementary service version indicator */
enum NAS_SS_VERSION_INDICATOR_ENUM
{
    NAS_SS_VERSION_INDICATOR_PHASE2                  = 0,
    NAS_SS_VERSION_INDICATOR_VER3                    = 1
};
typedef VOS_UINT8 NAS_SS_VERSION_INDICATOR;


/* 4.2 Operation types */
/*============================================================================*/
enum NAS_SS_OPERATION_TYPE_ENUM
{                                              /* Operation name    CRSS CISS */
    NAS_SS_OPERATION_REGISTER_SS                            =  10,              /* registerSS          -    +  */
    NAS_SS_OPERATION_ERASE_SS                               =  11,              /* eraseSS             -    +  */
    NAS_SS_OPERATION_ACTIVATE_SS                            =  12,              /* activateSS          -    +  */
    NAS_SS_OPERATION_DEACTIVATE_SS                          =  13,              /* deactivateSS        -    +  */
    NAS_SS_OPERATION_INTERROGATE_SS                         =  14,              /* forwardChargeAdvice +    -  */
    NAS_SS_OPERATION_NOTIFY_SS                              =  16,              /* interrogateSS       -    +  */
    NAS_SS_OPERATION_REGISTER_PASSWORD                      =  17,              /* registerPassword    -    +  */
    NAS_SS_OPERATION_GET_PASSWORD                           =  18,              /* getPassword         -    +  */
    NAS_SS_OPERATION_PROC_USSD                              =  19,              /* processUSS-Data     +    +  */
    NAS_SS_OPERATION_FWD_CHECK_SS_IND                       =  38,              /* forwardCheckSS-Ind  -    +  */
    NAS_SS_OPERATION_PROC_USS_REQ                           =  59,              /* processUSS-Request  -    +  */
    NAS_SS_OPERATION_USS_REQ                                =  60,              /* USS-Request         -    +  */
    NAS_SS_OPERATION_USS_NOTIFY                             =  61,              /* USS-Notify          -    +  */
    NAS_SS_OPERATION_FWD_CHARGE_ADVICE                      = 125,              /* notifySS            +    -  */
    NAS_SS_OPERATION_FWD_CUG_INFO                           = 120,              /* forwardCUG-Info     +    -  */
    NAS_SS_OPERATION_BUILD_MPTY                             = 124,              /* buildMPTY           +    -  */
    NAS_SS_OPERATION_HOLD_MPTY                              = 123,              /* holdMPTY            +    -  */
    NAS_SS_OPERATION_RETRIEVE_MPTY                          = 122,              /* retrieveMPTY        +    -  */
    NAS_SS_OPERATION_SPLIT_MPTY                             = 121,              /* splitMPTY           +    -  */
    NAS_SS_OPERATION_EXPLICIT_CT                            = 126,              /* explicitCT          +    -  */
    NAS_SS_OPERATION_ACCESS_REG_CC_ENTRY                    = 119,              /* accessRegCCEntry    +    -  */
    NAS_SS_OPERATION_ERASE_CC_ENTRY                         =  77,              /* eraseCCEntry        -    +  */
    NAS_SS_OPERATION_CALL_DEFLECTION                        = 117,              /* callDeflection      +    -  */
    NAS_SS_OPERATION_USER_USER_SERVICE                      = 118,              /* userUserService     +    -  */
    NAS_SS_OPERATION_LCS_LOC_NOTIFY                         = 116,              /* lcs-LocNotification -    +  */
    NAS_SS_OPERATION_LCS_MOLR                               = 115,              /* lcs-MOLR            -    +  */
    NAS_SS_OPERATION_BUTT
};
typedef VOS_UINT8 NAS_SS_OPERATION_ENUM_U8;

/* 4.3 Errors */
/*============================================================================*/
enum NAS_SS_ERROR_CODE_TYPE_ENUM
{
    NAS_SS_ERR_UNKNOWN_SUBSCRIBER                           =   1,
    NAS_SS_ERR_BEARER_SERVICE_NOT_PROVISIONED               =  10,
    NAS_SS_ERR_TELESERVICE_NOT_PROVISIONED                  =  11,
    NAS_SS_ERR_ILLEGAL_SS_OPERATION                         =  16,
    NAS_SS_ERR_SS_ERROR_STATUS                              =  17,
    NAS_SS_ERR_SS_NOT_AVAILABLE                             =  18,
    NAS_SS_ERR_SS_SUBSCRIPTION_VIOLATION                    =  19,
    NAS_SS_ERR_SS_INCOMPATIBILITY                           =  20,
    NAS_SS_ERR_SYSTEM_FAILURE                               =  34,
    NAS_SS_ERR_DATA_MISSING                                 =  35,
    NAS_SS_ERR_UNEXPECTED_DATA_VALUE                        =  36,
    NAS_SS_ERR_PASSWORD_REGISTRATION_FAILURE                =  37,
    NAS_SS_ERR_NEGATIVE_PASSWORD_CHECK                      =  38,
    NAS_SS_ERR_FACILITY_NOT_SUPPORTED                       =  21,
    NAS_SS_ERR_RESOURCES_NOT_AVAILABLE                      = 127,
    NAS_SS_ERR_MAX_NUM_OF_MPTY_PARTICIPANTS_EXCEEDED        = 126,
    NAS_SS_ERR_CALL_BARRED                                  =  13,
    NAS_SS_ERR_NUMBER_OF_PW_ATTEMPTS_VIOLATION              =  43,
    NAS_SS_ERR_ABSENT_SUBSCRIBER                            =  27,
    NAS_SS_ERR_ILLEGAL_SUBSCRIBER                           =   9,
    NAS_SS_ERR_ILLEGAL_EQUIPMENT                            =  12,
    NAS_SS_ERR_USSD_BUSY                                    =  72,
    NAS_SS_ERR_UNKNOWN_ALPHABET                             =  71,
    NAS_SS_ERR_INVALID_DEFLECTED_TO_NUMBER                  = 125,
    NAS_SS_ERR_SPECIAL_SERVICE_CODE                         = 124,
    NAS_SS_ERR_DEFLECTION_TO_SERVED_SUBSCRIBER              = 123,
    NAS_SS_ERR_REJECTED_BY_NETWORK                          = 122,
    NAS_SS_ERR_REJECTED_BY_USER                             = 121,
    NAS_SS_ERR_POSITION_METHOD_FAILURE                      =  54
};
typedef VOS_UINT8  NAS_SS_ERROR_CODE_TYPE_ENUM_U8;

/* 4.4 Data types and identifiers */
enum NAS_SS_CODE_ENUM
{
    NAS_SS_CODE_ALL_SS                                      = 0x00,             /* reserved for possible future use */
                                                                                /* all SS */
    NAS_SS_CODE_ALI_SS                                      = 0x10,             /* reserved for possible future use */
                                                                                /* all line identification SS */
    NAS_SS_CODE_CLIP                                        = 0x11,             /* calling line identification presentation */
    NAS_SS_CODE_CLIR                                        = 0x12,             /* calling line identification restriction */
    NAS_SS_CODE_COLP                                        = 0x13,             /* connected line identification presentation */
    NAS_SS_CODE_COLR                                        = 0x14,             /* connected line identification restriction */
    NAS_SS_CODE_MCI                                         = 0x15,             /* reserved for possible future use */
                                                                                /* malicious call identification */
    NAS_SS_CODE_ANI_SS                                      = 0x18,             /* all name identification SS */
    NAS_SS_CODE_CNAP                                        = 0x19,             /* calling name presentation */

    NAS_SS_CODE_AF_SS                                       = 0x20,             /* all forwarding SS */
    NAS_SS_CODE_CFU                                         = 0x24,             /* call forwarding unconditional */
    NAS_SS_CODE_ACF_SS                                      = 0x28,             /* all conditional forwarding SS */
    NAS_SS_CODE_CFB                                         = 0x29,             /* call forwarding on mobile subscriber busy */
    NAS_SS_CODE_CFNRY                                       = 0x2A,             /* call forwarding on mobile subscriber no reply */
    NAS_SS_CODE_CFNRC                                       = 0x2B,             /* call forwarding on mobile subscriber not reachable */
    NAS_SS_CODE_ACO_SS                                      = 0x30,             /* reserved for possible future use */
                                                                                /* all call offering SS includes also all forwarding SS */
    NAS_SS_CODE_ECT                                         = 0x31,             /* explicit call transfer */
    NAS_SS_CODE_MAH                                         = 0x32,             /* reserved for possible future use */
                                                                                /* mobile access hunting */
    NAS_SS_CODE_ACC_SS                                      = 0x40,             /* reserved for possible future use */
                                                                                /* all Call completion SS */
    NAS_SS_CODE_CW                                          = 0x41,             /* call waiting */
    NAS_SS_CODE_HOLD                                        = 0x42,             /* call hold */
    NAS_SS_CODE_CCBS_OS                                     = 0x43,             /* completion of call to busy subscribers, originating side */
    NAS_SS_CODE_CCBS_DS                                     = 0x44,             /* completion of call to busy subscribers, destination side */
                                                                                /* this SS-Code is used only in InsertSubscriberData and DeleteSubscriberData */
    NAS_SS_CODE_MC                                          = 0x45,             /* multicall */
    NAS_SS_CODE_AMP_SS                                      = 0x50,             /* reserved for possible future use */
                                                                                /* all multiparty SS */
    NAS_SS_CODE_MPTY                                        = 0x51,             /* multiparty */
    NAS_SS_CODE_ACOI_SS                                     = 0x60,             /* reserved for possible future use */
                                                                                /* all community of interest SS */
    NAS_SS_CODE_CUG                                         = 0x61,             /* closed user group */
    NAS_SS_CODE_AC_SS                                       = 0x70,             /* reserved for possible future use */
                                                                                /* all charging SS */
    NAS_SS_CODE_AOCI                                        = 0x71,             /* advice of charge information */
    NAS_SS_CODE_AOCC                                        = 0x72,             /* advice of charge charging */
    NAS_SS_CODE_AAIT_SS                                     = 0x80,             /* reserved for possible future use */
                                                                                /* all additional information transfer SS */
    NAS_SS_CODE_UUS1                                        = 0x81,             /* UUS1 user-to-user signalling */
    NAS_SS_CODE_UUS2                                        = 0x82,             /* UUS2 user-to-user signalling */
    NAS_SS_CODE_UUS3                                        = 0x83,             /* UUS3 user-to-user signalling */
    NAS_SS_CODE_AB_SS                                       = 0x90,             /* all barring SS */
    NAS_SS_CODE_BOC                                         = 0x91,             /* barring of outgoing calls */
    NAS_SS_CODE_BAOC                                        = 0x92,             /* barring of all outgoing calls */
    NAS_SS_CODE_BOIC                                        = 0x93,             /* barring of outgoing international calls */
    NAS_SS_CODE_BOICEXHC                                    = 0x94,             /* barring of outgoing international calls except those directed */
                                                                                /* to the home PLMN */
    NAS_SS_CODE_BIC                                         = 0x99,             /* barring of incoming calls */
    NAS_SS_CODE_BAIC                                        = 0x9A,             /* barring of all incoming calls */
    NAS_SS_CODE_BICROAM                                     = 0x9B,             /* barring of incoming calls when roaming outside home PLMN Country */
    NAS_SS_CODE_ACP_SS                                      = 0xA0,             /* reserved for possible future use */
                                                                                /* all call priority SS*/
    NAS_SS_CODE_EMLPP                                       = 0xA1,             /* enhanced Multilevel Precedence Pre-emption 'EMLPP' service */
    NAS_SS_CODE_ALCSPE                                      = 0xB0,             /* all LCS Privacy Exception Classes */
    NAS_SS_CODE_UNIVERSAL                                   = 0xB1,             /* allow location by any LCS client */
    NAS_SS_CODE_CR                                          = 0xB2,             /* allow location by any value added LCS client to which a call */
                                                                                /* is established from the target MS */
    NAS_SS_CODE_CUR                                         = 0xB3,             /* allow location by designated external value added LCS clients */
    NAS_SS_CODE_PLMN_OP                                     = 0xB4,             /* allow location by designated PLMN operator LCS clients */
    NAS_SS_CODE_AMOLR_SS                                    = 0xC0,             /* all Mobile Originating Location Request Classes */
    NAS_SS_CODE_BSL                                         = 0xC1,             /* allow an MS to request its own location */
    NAS_SS_CODE_ASL                                         = 0xC2,             /* allow an MS to perform self location without interaction */
                                                                                /* with the PLMN for a predetermined period of time */
    NAS_SS_CODE_TTTP                                        = 0xC3,             /* allow an MS to request transfer of its location to another LCS client */
    NAS_SS_CODE_APLMN_SSS                                   = 0xF0,
    NAS_SS_CODE_PLMN_SSS1                                   = 0xF1,
    NAS_SS_CODE_PLMN_SSS2                                   = 0xF2,
    NAS_SS_CODE_PLMN_SSS3                                   = 0xF3,
    NAS_SS_CODE_PLMN_SSS4                                   = 0xF4,
    NAS_SS_CODE_PLMN_SSS5                                   = 0xF5,
    NAS_SS_CODE_PLMN_SSS6                                   = 0xF6,
    NAS_SS_CODE_PLMN_SSS7                                   = 0xF7,
    NAS_SS_CODE_PLMN_SSS8                                   = 0xF8,
    NAS_SS_CODE_PLMN_SSS9                                   = 0xF9,
    NAS_SS_CODE_PLMN_SSSA                                   = 0xFA,
    NAS_SS_CODE_PLMN_SSSB                                   = 0xFB,
    NAS_SS_CODE_PLMN_SSSC                                   = 0xFC,
    NAS_SS_CODE_PLMN_SSSD                                   = 0xFD,
    NAS_SS_CODE_PLMN_SSSE                                   = 0xFE,
    NAS_SS_CODE_PLMN_SSSF                                   = 0xFF
};
typedef VOS_UINT8 NAS_SS_CODE_ENUM_U8;

enum NAS_SS_TELESERVICES_CODE_ENUM
{
    NAS_SS_TELESERVICES_CODE_ALL                            = 0x00,
    NAS_SS_TELESERVICES_CODE_ASTS                           = 0x10,
    NAS_SS_TELESERVICES_CODE_TELEPHONY                      = 0x11,
    NAS_SS_TELESERVICES_CODE_EMERGENCY_CALLS                = 0x12,
    NAS_SS_TELESERVICES_CODE_ASMS                           = 0x20,
    NAS_SS_TELESERVICES_CODE_SMMT_PP                        = 0x21,
    NAS_SS_TELESERVICES_CODE_SMMO_PP                        = 0x22,
    NAS_SS_TELESERVICES_CODE_AFTS                           = 0x30,
    NAS_SS_TELESERVICES_CODE_FG3AAS                         = 0x31,
    NAS_SS_TELESERVICES_CODE_AFG3                           = 0x32,
    NAS_SS_TELESERVICES_CODE_FG4                            = 0x33,
    NAS_SS_TELESERVICES_CODE_ADT                            = 0x70,
    NAS_SS_TELESERVICES_CODE_AT_EXSMS                       = 0x80,
    NAS_SS_TELESERVICES_CODE_AVGCS                          = 0x90,
    NAS_SS_TELESERVICES_CODE_VGC                            = 0x91,
    NAS_SS_TELESERVICES_CODE_VBC                            = 0x92,
    NAS_SS_TELESERVICES_CODE_APLMN_STS                      = 0xD0,
    NAS_SS_TELESERVICES_CODE_PLMN_STS1                      = 0xD1,
    NAS_SS_TELESERVICES_CODE_PLMN_STS2                      = 0xD2,
    NAS_SS_TELESERVICES_CODE_PLMN_STS3                      = 0xD3,
    NAS_SS_TELESERVICES_CODE_PLMN_STS4                      = 0xD4,
    NAS_SS_TELESERVICES_CODE_PLMN_STS5                      = 0xD5,
    NAS_SS_TELESERVICES_CODE_PLMN_STS6                      = 0xD6,
    NAS_SS_TELESERVICES_CODE_PLMN_STS7                      = 0xD7,
    NAS_SS_TELESERVICES_CODE_PLMN_STS8                      = 0xD8,
    NAS_SS_TELESERVICES_CODE_PLMN_STS9                      = 0xD9,
    NAS_SS_TELESERVICES_CODE_PLMN_STSA                      = 0xDA,
    NAS_SS_TELESERVICES_CODE_PLMN_STSB                      = 0xDB,
    NAS_SS_TELESERVICES_CODE_PLMN_STSC                      = 0xDC,
    NAS_SS_TELESERVICES_CODE_PLMN_STSD                      = 0xDD,
    NAS_SS_TELESERVICES_CODE_PLMN_STSE                      = 0xDE,
    NAS_SS_TELESERVICES_CODE_PLMN_STSF                      = 0xDF
};
typedef VOS_UINT8 NAS_SS_TELESERVICES_CODE_ENUM_U8;

enum NAS_SS_BS_CODE_ENUM
{
	NAS_SS_BS_CODE_TEMP
};
typedef VOS_UINT8 NAS_SS_BS_CODE_ENUM_U8;

enum NAS_SS_STATUS_ENUM
{
    NAS_SS_STATUS_ACTIVE                                    = 0x01,
    NAS_SS_STATUS_REGISTER                                  = 0x02,
    NAS_SS_STATUS_PROVIDE                                   = 0x04,
    NAS_SS_STATUS_QUIET                                     = 0x08
};
typedef VOS_UINT8 NAS_SS_STATUS_ENUM_U8;


#if 0
typedef struct
{
/*
    ss-Code                 <TLV> [4] SS-Code,
    basicService            <BER>     BasicServiceCode        OPTIONAL,
    forwardedToNumber       <BER> [4] AddressString           OPTIONAL,
    forwardedToSubaddress   <BER> [6] ISDN-SubaddressString   OPTIONAL,
    noReplyConditionTime    <BER> [5] NoReplyConditionTime    OPTIONAL,
    ...,
    defaultPriority         <BER> [7] EMLPP-Priority          OPTIONAL,
    nbrUser                 <BER> [8] MC-Bearers              OPTIONAL,
    longFTN-Supported       <BER> [9] NULL                    OPTIONAL
*/
}SS_REGISTER_SS_ARG_STRU;

typedef struct
{
/*
    SS-ForBS-Code
*/
}SS_ERASE_ARG_STRU;

typedef struct
{
/*
    SS-ForBS-Code
*/
}SS_ACTIVE_ARG_STRU;

typedef struct
{
/*
    SS-ForBS-Code
*/
}SS_DEACTIVE_ARG_STRU;

typedef struct
{
/*
    SS-ForBS-Code
*/
}SS_INTERROGATE_ARG_STRU;

typedef struct
{
/*
    ss-Code                     <TLV,T|LEN-8,L|LEN-8,V|LEN-8>[0x81]     SS-Code,
    ss-Status                   <TLV,T|LEN-8,L|LEN-8,V|LEN-8>[0x84]     SS-Status,
    ss-Notification             <BER>[5]     SS-Notification OPTIONAL,
    callIsWaiting-Indicator     <BER>[14]    NULL OPTIONAL,
    callOnHold-Indicator        <BER>[15]    CallOnHold-Indicator OPTIONAL,
    mpty-Indicator              <BER>[16]    NULL OPTIONAL,
    cug-Index                   <BER>[17]    IMPLICIT INTEGER ( 0 .. 32767 ) OPTIONAL,
    clirSuppressionRejected     <BER>[18]    NULL OPTIONAL,
    ... ,
    ect-Indicator               <BER>[19]    ECT-Indicator OPTIONAL,
    nameIndicator               <BER>[20]    NameIndicator OPTIONAL,
    ccbs-Feature                <BER>[21]    CCBS-Feature OPTIONAL,
    alertingPattern             <BER>[22]    AlertingPattern OPTIONAL,
    multicall-Indicator         <BER>[23]    Multicall-Indicator OPTIONAL
*/
}SS_NOTIFY_SS_ARG_STRU;

typedef struct
{
/*
    <V> SS-Code
*/
}SS_REGISTER_PASSWORD_ARG_STRU;

typedef struct
{
/*
    GuidanceInfo
*/
}SS_GET_PASSWORD_ARG_STRU;

typedef struct
{
/*
    ussd-DataCodingScheme   <BER> [4] USSD-DataCodingScheme,
    ussd-String             <BER> [4] USSD-String,
    ... ,
    alertingPattern         <BER> [4] AlertingPattern     OPTIONAL,
    msisdn                  <BER> [0] ISDN-AddressString  OPTIONAL
*/
}SS_PROCESS_USSD_ARG_STRU;

typedef struct
{
/*
    NULL
*/
}SS_FWD_CHK_SS_IND_ARG_STRU;

typedef struct
{
/*
    ussd-DataCodingScheme   <BER> [4] USSD-DataCodingScheme,
    ussd-String             <BER> [4] USSD-String,
    ... ,
    alertingPattern         <BER> [4] AlertingPattern     OPTIONAL,
    msisdn                  <BER> [0] ISDN-AddressString  OPTIONAL
*/
}SS_PROCESS_USS_REQ_ARG_STRU;

typedef struct
{
/*
    ussd-DataCodingScheme   <BER> [4] USSD-DataCodingScheme,
    ussd-String             <BER> [4] USSD-String,
    ... ,
    alertingPattern         <BER> [4] AlertingPattern     OPTIONAL,
    msisdn                  <BER> [0] ISDN-AddressString  OPTIONAL
*/
}SS_USS_REQ_ARG_STRU;

typedef struct
{
/*
    ussd-DataCodingScheme   <BER> [4] USSD-DataCodingScheme,
    ussd-String             <BER> [4] USSD-String,
    ... ,
    alertingPattern         <BER> [4] AlertingPattern     OPTIONAL,
    msisdn                  <BER> [0] ISDN-AddressString  OPTIONAL
*/
}SS_USS_NOTIFY_ARG_STRU;

typedef struct
{
/*
    ss-Code            <BER> [0] SS-Code,
    ccbs-Data          <BER> [1] CCBS-Data    OPTIONAL,
    ...
*/
}SS_REGISTER_CC_ENTRY_ARG_STRU;

typedef struct
{
/*
    ss-Code        <BER> [0] SS-Code,
    ccbs-Index     <BER> [1] CCBS-Index  OPTIONAL,
    ...
*/
}SS_ERASE_CC_ENTRY_ARG_STRU;

typedef struct
{
/*
    deflectedToNumber       <BER> [0] IMPLICIT OCTET STRING (  SIZE (1 .. 20 ) ),
    deflectedToSubaddress   <BER> [1] IMPLICIT OCTET STRING (  SIZE (1 .. 21 ) ) OPTIONAL,
    ...
*/
}SS_CALL_DEFLECTION_ARG_STRU;

typedef struct
{
/*
    uUS-Service    <BER> [0] UUS-Service,
    uUS-Required   <BER> [1] IMPLICIT BOOLEAN,
    ...
*/
}SS_USER_USER_SERVICE_ARG_STRU;

typedef struct
{
/*
    ...
*/
}SS_ACCESS_REGISTER_CC_ENTRY_ARG_STRU;

typedef struct
{
/*
    cug-Index         <BER> [0] IMPLICIT INTEGER ( 0 .. 32767 ) OPTIONAL,
    suppressPrefCUG   <BER> [1] IMPLICIT NULL OPTIONAL,
    suppressOA        <BER> [2] IMPLICIT NULL OPTIONAL,
    ...
*/
}SS_FWD_CUG_INFO_ARG_STRU;

typedef struct
{
/*
    NULL
*/
}SS_SPLIT_MPTY_ARG_STRU;

typedef struct
{
/*
    NULL
*/
}SS_RETRIEVE_MPTY_ARG_STRU;

typedef struct
{
/*
    NULL
*/
}SS_HOLD_MPTY_ARG_STRU;

typedef struct
{
/*
    NULL
*/
}SS_BUILD_MPTY_ARG_STRU;

typedef struct
{
/*
    ss-Code               <BER> [0] SS-Code,
    chargingInformation   <BER> [1] IMPLICIT  ChargingInformation,
    ...
*/
}SS_FWD_CHARGE_ADVICE_ARG_STRU;

typedef struct
{
/*
    NULL
*/
}SS_EXPLICIT_CT_ARG_STRU;

typedef struct
{
/*
    notificationType      <BER>[0] IMPLICIT NotificationType,
    locationType          <BER>[1] IMPLICIT LocationType,
    lcsClientExternalID   <BER>[2] IMPLICIT LCSClientExternalID  OPTIONAL,
    lcsClientName         <BER>[3] IMPLICIT LCSClientName        OPTIONAL,
    ...
*/
}SS_LCS_LOC_NOTIFICATION_ARG_STRU;

typedef struct
{
/*
    molr-Type             <BER>[0] IMPLICIT Molr-Type,
    locationMethod        <BER>[1] IMPLICIT LocationMethod OPTIONAL,
    lcs-QoS               <BER>[2] IMPLICIT LCS-QoS  OPTIONAL,
    lcsClientExternalID   <BER>[3] IMPLICIT LCSClientExternalID OPTIONAL,
    mlc-Number            <BER>[4] IMPLICIT OCTET STRING (  SIZE (1 .. 20 ) ) (  SIZE (1 .. 9 ) ) OPTIONAL,
    gpsAssistanceData     <BER>[5] IMPLICIT OCTET STRING (  SIZE (1 .. 38 ) ) OPTIONAL,
    ... ,
    supportedGADShapes    <BER>[6] IMPLICIT BIT STRING
    {
        ellipsoidPoint                                      (0 ),
        ellipsoidPointWithUncertaintyCircle                 (1 ),
        ellipsoidPointWithUncertaintyEllipse                (2 ),
        polygon                                             (3 ),
        ellipsoidPointWithAltitude                          (4 ),
        ellipsoidPointWithAltitudeAndUncertaintyElipsoid    (5 ),
        ellipsoidArc                                        (6 )
    } (  SIZE (7 .. 16 ) ) OPTIONAL

*/
}SS_LCS_MOLR_ARG_STRU;


typedef union
{
    SS_REGISTER_SS_ARG_STRU                 RegisterSSArg;
    SS_ERASE_ARG_STRU                       EraseArg;
    SS_ACTIVE_ARG_STRU                      ActiveArg;
    SS_DEACTIVE_ARG_STRU                    DeactiveArg;
    SS_INTERROGATE_ARG_STRU                 InterrogateArg;
    SS_NOTIFY_SS_ARG_STRU                   NotifySSArg;
    SS_REGISTER_PASSWORD_ARG_STRU           RegisterPasswordArg;
    SS_GET_PASSWORD_ARG_STRU                GetPasswordArg;
    SS_PROCESS_USSD_ARG_STRU                ProcessUSSDArg;
    SS_FWD_CHK_SS_IND_ARG_STRU              FwdCheckSSIndArg;
    SS_PROCESS_USS_REQ_ARG_STRU             ProcessUSSReqArg;
    SS_USS_REQ_ARG_STRU                     USSReqArg;
    SS_USS_NOTIFY_ARG_STRU                  USSNotifyArg;
    SS_REGISTER_CC_ENTRY_ARG_STRU           RegisterCCEntryArg;
    SS_ERASE_CC_ENTRY_ARG_STRU              EraseCCEntryArg;
    SS_CALL_DEFLECTION_ARG_STRU             CallDeflectionArg;
    SS_USER_USER_SERVICE_ARG_STRU           UseruserServiceArg;
    SS_ACCESS_REGISTER_CC_ENTRY_ARG_STRU    AccessRegisterCCEntryArg;
    SS_FWD_CUG_INFO_ARG_STRU                FwdCUGInfoArg;
    SS_SPLIT_MPTY_ARG_STRU                  SplitMPTYArg;
    SS_RETRIEVE_MPTY_ARG_STRU               RetrieveMPTYArg;
    SS_HOLD_MPTY_ARG_STRU                   HoldMPTYArg;
    SS_BUILD_MPTY_ARG_STRU                  BuildMPTYArg;
    SS_FWD_CHARGE_ADVICE_ARG_STRU           FwdChargeAdviceArg;
    SS_EXPLICIT_CT_ARG_STRU                 ExplicitCTArg;
    SS_LCS_LOC_NOTIFICATION_ARG_STRU        LCSLocNotificationArg;
    SS_LCS_MOLR_ARG_STRU                    LCSMOLRArg;
}SS_ARG_UNION;

typedef union
{
/*
    register-ss                      <BER> RegisterSS-Res                       WHEN(10 == opcd.v),
    erase-ss                         <BER> EraseSS-Res                          WHEN(11 == opcd.v),
    active-ss                        <BER> Active-SS-Res                        WHEN(12 == opcd.v),
    deactive-ss                      <BER> Deactive-SS-Res                      WHEN(13 == opcd.v),
    interrogate-ss                   <BER> Interrogate-SS-Res                   WHEN(14 == opcd.v),
    notify-ss                        <BER> Notify-SS-Res                        WHEN(16 == opcd.v),
    register-password                <BER> Register-password-Res                WHEN(17 == opcd.v),
    get-password                     <BER> Get-password-Res                     WHEN(18 == opcd.v),
    process-ussd                     <BER> Process-ussd-Res                     WHEN(19 == opcd.v),
    forward-check-ss-indication      <BER> Forward-check-ss-indication-Res      WHEN(38 == opcd.v),
    process-unstructuredss-request   <BER> Process-Unstructuredss-request-Res   WHEN(59 == opcd.v),
    unstructuredss-request           <BER> Unstructuredss-request-Res           WHEN(60 == opcd.v),
    unstructuredss-notify            <BER> Unstructuredss-notify-Res            WHEN(61 == opcd.v),
    register-cc-entry                <BER> Register-cc-entry-Res                WHEN(76 == opcd.v),
    erase-cc-entry                   <BER> Erase-cc-entry-Res                   WHEN(77 == opcd.v),
    callDeflection                   <BER> Calldeflection-Res                   WHEN(117 == opcd.v),
    userUserService                  <BER> Useruserservice-Res                  WHEN(118 == opcd.v),
    accessRegisterCCEntry            <BER> Accessregisterccentry-Res            WHEN(119 == opcd.v),
    forwardCUG-Info                  <BER> Forwardcug-info-Res                  WHEN(120 == opcd.v),
    splitMPTY                        <BER> Splitmpty-Res                        WHEN(121 == opcd.v),
    retrieveMPTY                     <BER> Retrievempty-Res                     WHEN(122 == opcd.v),
    holdMPTY                         <BER> Holdmpty-Res                         WHEN(123 == opcd.v),
    buildMPTY                        <BER> Buildmpty-Res                        WHEN(124 == opcd.v),
    forwardChargeAdvice              <BER> Forwardchargeadvice-Res              WHEN(125 == opcd.v),
    explicitCT                       <BER> Explicitct-Res                       WHEN(126 == opcd.v),
    lcs-LocationNotification         <BER> Lcs-locationnotification-Res         WHEN(116 == opcd.v),
    lcs-MOLR                         <BER> Lcs-molr-Res                         WHEN(115 == opcd.v)
*/
}SS_RES_UNION;

typedef union
{
/*
    unknownSubscriber                   <BER>UnknownSubscriberParam                    WHEN(1 == epcd.v),
    illegalSubscriber                   <BER>IllegalSubscriberParam                    WHEN(9 == epcd.v),
    bearerServiceNotProvisioned         <BER>BearerServNotProvParam                    WHEN(10 == epcd.v),
    teleserviceNotProvisioned           <BER>TeleservNotProvParam                      WHEN(11 == epcd.v),
    illegalEquipment                    <BER>IllegalEquipmentParam                     WHEN(12 == epcd.v),
    callBarred                          <BER>CallBarredParam                           WHEN(13 == epcd.v),
    illegalSS-Operation                 <BER>IllegalSS-OperationParam                  WHEN(16 == epcd.v),
    ss-ErrorStatus                      <BER>SS-ErrorStatusParam                       WHEN(17 == epcd.v),
    ss-NotAvailable                     <BER>SS-NotAvailableParam                      WHEN(18 == epcd.v),
    ss-SubscriptionViolation            <BER>SS-SubscriptionViolationParam             WHEN(19 == epcd.v),
    ss-Incompatibility                  <BER>SS-IncompatibilityCause                   WHEN(20 == epcd.v),
    facilityNotSupported                <BER>FacilityNotSupParam                       WHEN(21 == epcd.v),
    absentSubscriber                    <BER>AbsentSubscriberParam                     WHEN(27 == epcd.v),
    shortTermDenial                     <BER>ShortTermDenialParam                      WHEN(29 == epcd.v),
    longTermDenial                      <BER>LongTermDenialParam                       WHEN(30 == epcd.v),
    systemFailure                       <BER>SystemFailureParam                        WHEN(34 == epcd.v),
    dataMissing                         <BER>DataMissingParam                          WHEN(35 == epcd.v),
    unexpectedDataValue                 <BER>UnexpectedDataParam                       WHEN(36 == epcd.v),
    pw-RegistrationFailure              <BER>[4]PW-RegistrationFailureCause            WHEN(37 == epcd.v),
    negativePW-Check                    <BER>NegativePW-CheckParam                     WHEN(38 == epcd.v),
    numberOfPW-AttemptsViolation        <BER>NumberOfPW-AttemptsViolationParam         WHEN(43 == epcd.v),
    positionMethodFailure               <BER>PositionMethodFailure-Param               WHEN(54 == epcd.v),
    unknownAlphabet                     <BER>UnknownAlphabetParam                      WHEN(71 == epcd.v),
    ussd-Busy                           <BER>Ussd-BusyParam                            WHEN(72 == epcd.v),
    nbr-SbExceeded                      <BER>Nbr-SbExceededParam                       WHEN(120 == epcd.v),
    rejectedByUser                      <BER>RejectedByUserParam                       WHEN(121 == epcd.v),
    rejectedByNetwork                   <BER>RejectedByNetworkParam                    WHEN(122 == epcd.v),
    deflectionToServedSubscriber        <BER>DeflectionToServedSubscriberParam         WHEN(123 == epcd.v),
    specialServiceCode                  <BER>SpecialServiceCodeParam                   WHEN(124 == epcd.v),
    invalidDeflectedToNumber            <BER>InvalidDeflectedToNumberParam             WHEN(125 == epcd.v),
    maxNumberOfMPTYParticipantsExceeded <BER>MaxNumberOfMPTYParticipantsExceededParam  WHEN(126 == epcd.v),
    resourcesNotAvailable               <BER>ResourcesNotAvailableParam                WHEN(127 == epcd.v)
*/
}SS_PARAM_UNION;
#endif

/******************************************************************************/
/* Componet Sturct Definition  ( 3.6.1 Component )                            */
/******************************************************************************/
/* Table 3.3: Invoke component */
/*
    ┌────────────┬──────┬───────────┐
    │    Invoke component    │ Reference  │ Mandatory indication │
    ├────────────┼──────┼───────────┤
    │  Component type tag    │   3.6.2    │          M           │
    │  Component length      │   X.690    │                      │
    ├────────────┼──────┼───────────┤
    │  Invoke ID tag         │   3.6.3    │                      │
    │  Invoke ID length      │   X.690    │          M           │
    │  Invoke ID             │   3.6.3    │                      │
    ├────────────┼──────┼───────────┤
    │  Linked ID tag         │   3.6.3    │                      │
    │  Linked ID length      │   X.690    │          O           │
    │  Linked ID             │   3.6.3    │                      │
    ├────────────┼──────┼───────────┤
    │  Operation Code tag    │   3.6.4    │                      │
    │  Operation Code length │   X.690    │          M           │
    │  Operation Code        │   3.6.4    │                      │
    ├────────────┼──────┼───────────┤
    │  Parameters            │     4      │          O           │
    └────────────┴──────┴───────────┘
*/
typedef struct
{
    NAS_SS_COMPONET_TYPE_TAG_ENUM_U8    ComponentTypeTag;
    VOS_UINT8                           ComponentLength;

    NAS_SS_COMPONENT_ID_TAG_ENUM_U8     InvokeIDTag;
    VOS_UINT8                           InvokeIDLength;
    VOS_UINT8                           InvokeID;

    NAS_SS_COMPONENT_ID_TAG_ENUM_U8     LinkedIDTag;
    VOS_UINT8                           LinkedIDLength;
    VOS_UINT8                           LinkedID;

    NAS_SS_OPERATION_TAG_ENUM_U8        OperationCodeTag;
    VOS_UINT8                           OperationCodeLength;
    NAS_SS_OPERATION_ENUM_U8            Operationcode;


  /*SS_ARG_UNION                        Arg;
 */
}SS_INVOKE_COMPONENT_STRU;

/* Table 3.4: Return Result component */
/*
    ┌────────────┬──────┬───────────┐
    │Return Result component │ Reference  │ Mandatory indication │
    ├────────────┼──────┼───────────┤
    │  Component type tag    │   3.6.2    │          M           │
    │  Component length      │   X.690    │                      │
    ├────────────┼──────┼───────────┤
    │  Invoke ID tag         │   3.6.3    │                      │
    │  Invoke ID length      │   X.690    │          M           │
    │  Invoke ID             │   3.6.3    │                      │
    ├────────────┼──────┼───────────┤
    │  Sequence tag          │   3.6.5    │                      │
    │  Sequence length       │   X.690    │          O           │
    ├────────────┼──────┼───────────┤
    │  Operation Code tag    │   3.6.4    │                      │
    │  Operation Code length │   X.690    │          O           │
    │  Operation Code        │   3.6.4    │                      │
    ├────────────┼──────┼───────────┤
    │  Parameters            │     4      │          O           │
    └────────────┴──────┴───────────┘
*/
typedef struct
{
    NAS_SS_COMPONET_TYPE_TAG_ENUM_U8    ComponentTypeTag;
    VOS_UINT8                           ComponentLength;

    NAS_SS_COMPONENT_ID_TAG_ENUM_U8     InvokeIDTag;
    VOS_UINT8                           InvokeIDLength;
    VOS_UINT8                           InvokeID;

    NAS_SS_SEQUENCE_SET_TAG_ENUM_U8     SequenceTag;
    VOS_UINT8                           SequenceLength;

    NAS_SS_OPERATION_TAG_ENUM_U8        OperationCodeTag;
    VOS_UINT8                           OperationCodeLength;
    NAS_SS_OPERATION_ENUM_U8            Operationcode;

  /*SS_RES_UNION                        Res;
 */
}SS_RTN_RSLT_COMPONENT_STRU;


/* Table 3.5: Return Error component */
/*
    ┌────────────┬──────┬───────────┐
    │ Return Error component │ Reference  │ Mandatory indication │
    ├────────────┼──────┼───────────┤
    │  Component type tag    │   3.6.2    │          M           │
    │  Component length      │   X.690    │                      │
    ├────────────┼──────┼───────────┤
    │  Invoke ID tag         │   3.6.3    │                      │
    │  Invoke ID length      │   X.690    │          M           │
    │  Invoke ID             │   3.6.3    │                      │
    ├────────────┼──────┼───────────┤
    │  Error Code tag        │   3.6.6    │                      │
    │  Error Code length     │   X.690    │          O           │
    │  Error Code            │   3.6.6    │                      │
    ├────────────┼──────┼───────────┤
    │  Parameters            │     4      │          O           │
    └────────────┴──────┴───────────┘
*/
typedef struct
{
    NAS_SS_COMPONET_TYPE_TAG_ENUM_U8    ComponentTypeTag;
    VOS_UINT8                           ComponentLength;

    NAS_SS_COMPONENT_ID_TAG_ENUM_U8     InvokeIDTag;
    VOS_UINT8                           InvokeIDLength;
    VOS_UINT8                           InvokeID;

    NAS_SS_ERROR_TAG_ENUM_U8            ErrorCodeTag;
    VOS_UINT8                           ErrorCodeLength;
    NAS_SS_ERROR_CODE_TYPE_ENUM_U8      ErrorCode;

  /*SS_PARAM_UNION                      Param;
 */
}SS_RTN_ERR_COMPONENT_STRU;

/* Table 3.6: Reject component */
/*
    ┌────────────┬──────┬───────────┐
    │   Reject  component    │ Reference  │ Mandatory indication │
    ├────────────┼──────┼───────────┤
    │  Component type tag    │   3.6.2    │          M           │
    │  Component length      │   X.690    │                      │
    ├────────────┼──────┼───────────┤
    │  Invoke ID tag         │   3.6.3    │                      │
    │  Invoke ID length      │   X.690    │          M           │
    │  Invoke ID             │   3.6.3    │                      │
    ├────────────┼──────┼───────────┤
    │  Problem Code tag      │   3.6.7    │                      │
    │  Problem Code length   │   X.690    │          O           │
    │  Problem Code          │   3.6.7    │                      │
    └────────────┴──────┴───────────┘
*/
typedef struct
{
    NAS_SS_COMPONET_TYPE_TAG_ENUM_U8    ComponentTypeTag;
    VOS_UINT8                           ComponentLength;

    NAS_SS_COMPONENT_ID_TAG_ENUM_U8     InvokeIDTag;
    VOS_UINT8                           InvokeIDLength;
    VOS_UINT8                           InvokeID;

    NAS_SS_PROBLEM_TAG_ENUM_U8          ProblemCodeTag;
    VOS_UINT8                           ProblemCodeLength;
    union
    {
        NAS_SS_GENERAL_PROBLEM_CODE_ENUM_U8    General;
        NAS_SS_INVOKE_PROBLEM_CODE_ENUM_U8     Invoke;
        NAS_SS_RTN_RSLT_PROBLEM_CODE_ENUM_U8   RtnRslt;
        NAS_SS_RTN_ERR_PROBLEM_CODE_ENUM_U8    RtnErr;
    }ProblemCode;
}SS_REJECT_COMPONENT_STRU;

/* component union */
typedef union
{
    NAS_SS_COMPONET_TYPE_TAG_ENUM_U8    ComponentTypeTag;
    SS_INVOKE_COMPONENT_STRU            Invoke;
    SS_RTN_RSLT_COMPONENT_STRU          RtnRslt;
    SS_RTN_ERR_COMPONENT_STRU           RtnErr;
    SS_REJECT_COMPONENT_STRU            Reject;
}SS_COMPONET_UNION;



/******************************************************************************/
/* IE Sturct Definition                                                       */
/******************************************************************************/
typedef struct
{
    VOS_UINT8                           T;
    VOS_UINT8                           L;

    SS_COMPONET_UNION                   Component;
}SS_IE_FACILITY_STRU;

typedef struct
{
    VOS_UINT8                           T;
    VOS_UINT8                           L;

    NAS_SS_VERSION_INDICATOR            Version;
}SS_IE_SS_VER_INDICATOR_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _NAS_SS_IE_H */

