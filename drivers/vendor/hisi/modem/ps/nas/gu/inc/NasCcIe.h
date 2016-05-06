/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcIe.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月25日
  最近修改   : 2007年8月25日
  功能描述   : 定义CC空口消息中的IE
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年9月11日
    作    者   :S62952
    修改内容   : 问题单号:AT2D05593
  3.日    期   : 2008年10月24日
    作    者   :S62952
    修改内容   : 问题单号:A32D14191
  4.日    期   : 2010年02月23日
    作    者   : f62575
    修改内容   : 问题单号:AT2D16374

  5.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  6.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
******************************************************************************/

#ifndef __NAS_CC_IE_H__
#define __NAS_CC_IE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasCc.h"
#include "MnCallApi.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* NAS_CC_CAUSE_CC_INTER_ERR_BEGIN要与TAF_CS_CAUSE_CC_INTER_ERR_T303_TIME_OUT的值一致 */
#define             NAS_CC_CAUSE_NW_SECTION_BEGIN                (0x0000)
#define             NAS_CC_CAUSE_NW_SECTION_END                  (0x00FF)
#define             NAS_CC_CAUSE_CM_SRV_REJ_BEGIN                (0x0100)
#define             NAS_CC_CAUSE_CM_SRV_REJ_END                  (0x01FF)
#define             NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN              (0x0200)
#define             NAS_CC_CAUSE_CSFB_SRV_REJ_END                (0x02FF)
#define             NAS_CC_CAUSE_SMS_CP_ERR_BEGIN                (0x0300)
#define             NAS_CC_CAUSE_SMS_CP_ERR_END                  (0x03FF)
#define             NAS_CC_CAUSE_SMS_RP_ERR_BEGIN                (0x0400)
#define             NAS_CC_CAUSE_SMS_RP_ERR_END                  (0x04FF)
#define             NAS_CC_CAUSE_SS_NW_REJ_BEGIN                 (0x0500)
#define             NAS_CC_CAUSE_SS_NW_REJ_END                   (0x05FF)
#define             NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN              (0x0600)
#define             NAS_CC_CAUSE_RR_CONN_FAIL_END                (0x06FF)
#define             NAS_CC_CAUSE_RR_REL_BEGIN                    (0x0700)
#define             NAS_CC_CAUSE_RR_REL_END                      (0x07FF)
#define             NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN             (0x0800)
#define             NAS_CC_CAUSE_CSFB_LMM_FAIL_END               (0x08FF)
#define             NAS_CC_CAUSE_MM_INTER_ERR_BEGIN              (0x0900)
#define             NAS_CC_CAUSE_MM_INTER_ERR_END                (0x09FF)
#define             NAS_CC_CAUSE_CC_INTER_ERR_BEGIN              (0x0A1F)
#define             NAS_CC_CAUSE_CC_INTER_ERR_END                (0x0AFF)

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/* EXT bit of IE octet */
enum
{
    NAS_CC_IE_EXT                                           = 0,
    NAS_CC_IE_NO_EXT                                        = 1
};

/* The invalid value for all IE fields */
enum {
    NAS_CC_IE_INVALID_VAL                                   = 0xff
};

/*             24.008 - 10.5.4 Call control information elements              */

/******************************************************************************/
/*  Enumerated Definition                                                     */
/******************************************************************************/
enum NAS_CC_IEI_ENUM
{
    NAS_CC_IEI_EXT_CODESETS                                 = 0,                /* 10.5.4.1 Extensions of codesets      */
    NAS_CC_IEI_LOCKING_SHIFT,                                                   /* 10.5.4.2 Locking shift procedure     */
    NAS_CC_IEI_NON_LOCKING_SHIFT,                                               /* 10.5.4.3 Non-locking shift procedure */
    NAS_CC_IEI_AUX_STATES,                                                      /* 10.5.4.4 Auxiliary states            */
    NAS_CC_IEI_BAK_BC,                                                          /* 10.5.4.4a Backup bearer capability   */
    NAS_CC_IEI_BC,                                                              /* 10.5.4.5 Bearer capability           */
    NAS_CC_IEI_CC_CAP,                                                          /* 10.5.4.5a Call Control Capabilities  */
    NAS_CC_IEI_CALL_STATE,                                                      /* 10.5.4.6 Call state                  */
    NAS_CC_IEI_CALLED_NUM,                                                      /* 10.5.4.7 Called party BCD number     */
    NAS_CC_IEI_CALLED_SUBADDR,                                                  /* 10.5.4.8 Called party subaddress     */
    NAS_CC_IEI_CALLING_NUM,                                                     /* 10.5.4.9 Calling party BCD number    */
    NAS_CC_IEI_CALLING_SUBADDR,                                                 /* 10.5.4.10 Calling party subaddress   */
    NAS_CC_IEI_CAUSE,                                                           /* 10.5.4.11 Cause                      */
    NAS_CC_IEI_CLIR_S,                                                          /* 10.5.4.11a CLIR suppression          */
    NAS_CC_IEI_CLIR_I,                                                          /* 10.5.4.11b CLIR invocation           */
    NAS_CC_IEI_CONG_LEVEL,                                                      /* 10.5.4.12 Congestion level           */
    NAS_CC_IEI_CONN_NUM,                                                        /* 10.5.4.13 Connected number           */
    NAS_CC_IEI_CONN_SUBADDR,                                                    /* 10.5.4.14 Connected subaddress       */
    NAS_CC_IEI_FACILITY,                                                        /* 10.5.4.15 Facility                   */
    NAS_CC_IEI_HLC,                                                             /* 10.5.4.16 High layer compatibility   */
    NAS_CC_IEI_KEYPAD_FACILITY,                                                 /* 10.5.4.17 Keypad facility            */
    NAS_CC_IEI_LLC,                                                             /* 10.5.4.18 Low layer compatibility    */
    NAS_CC_IEI_MORE_DATA,                                                       /* 10.5.4.19 More data                  */
    NAS_CC_IEI_NOTIFY_IND,                                                      /* 10.5.4.20 Notification indicator     */
    NAS_CC_IEI_PROG_IND,                                                        /* 10.5.4.21 Progress indicator         */
    NAS_CC_IEI_RECALL_TYPE,                                                     /* 10.5.4.21a Recall type $(CCBS)$      */
    NAS_CC_IEI_REDIRECT_NUM,                                                    /* 10.5.4.21b Redirecting BCD number    */
    NAS_CC_IEI_REDIRECT_SUBADDR,                                                /* 10.5.4.21c Redirecting subaddress    */
    NAS_CC_IEI_REPEAT_IND,                                                      /* 10.5.4.22 Repeat indicator           */
    NAS_CC_IEI_RESVERSE_DIR,                                                    /* 10.5.4.22a Reverse call setup dir.   */
    NAS_CC_IEI_SETUP_CONTAINER,                                                 /* 10.5.4.22b SETUP Container $(CCBS)$  */
    NAS_CC_IEI_SIGNAL,                                                          /* 10.5.4.23 Signal                     */
    NAS_CC_IEI_SS_VER,                                                          /* 10.5.4.24 SS Version Indicator       */
    NAS_CC_IEI_USER_USER,                                                       /* 10.5.4.25 User-user                  */
    NAS_CC_IEI_ALERTING_PATTERN,                                                /* 10.5.4.26 Alerting Pattern $(NIA)$   */
    NAS_CC_IEI_ALLOWED_ACTIONS,                                                 /* 10.5.4.27 Allowed actions $(CCBS)$   */
    NAS_CC_IEI_STREAM_ID,                                                       /* 10.5.4.28 Stream Identifier          */
    NAS_CC_IEI_NW_CC_CAP,                                                       /* 10.5.4.29 Network Call Control Cap.  */
    NAS_CC_IEI_NO_CLI_CAUSE,                                                    /* 10.5.4.30 Cause of No CLI            */
    NAS_CC_IEI_VOID,                                                            /* 10.5.4.31 Void                       */
    NAS_CC_IEI_CODEC_LIST,                                                      /* 10.5.4.32 Supported codec list       */
    NAS_CC_IEI_SERVICE_CAT,                                                     /* 10.5.4.33 Service category           */
    NAS_CC_IEI_REDIAL,                                                          /* 10.5.4.34 Redial                     */
    NAS_CC_IEI_NISU_IND,                                                        /* 10.5.4.35 NISU indicator             */

    NAS_CC_IEI_PRIO_LEVEL,                                                      /* 10.5.1.11 Priority Level             */
    NAS_CC_IEI_FACILITY_1D,                                                     /* 10.5.4.15 Facility $CCBS$            */
    NAS_CC_IEI_FACILITY_1B                                                      /* 10.5.4.15 Facility $CCBS$            */
};
typedef VOS_UINT8  NAS_CC_IEI_ENUM_U8;

/* [10.5.1.11] Priority Level */
/*============================================================================*/
enum NAS_CALL_PRIORITY_ENUM
{                                                                               /* Bit 3 2 1                         */
    NAS_CALL_PRIORITY_NONE                                  = 0,                /*     0 0 0 no priority applied     */
    NAS_CALL_PRIORITY_LEVEL_4                               = 1,                /*     0 0 1 call priority level 4   */
    NAS_CALL_PRIORITY_LEVEL_3                               = 2,                /*     0 2 0 call priority level 3   */
    NAS_CALL_PRIORITY_LEVEL_2                               = 3,                /*     0 1 1 call priority level 2   */
    NAS_CALL_PRIORITY_LEVEL_1                               = 4,                /*     1 0 0 call priority level 1   */
    NAS_CALL_PRIORITY_LEVEL_0                               = 5,                /*     1 0 1 call priority level 0   */
    NAS_CALL_PRIORITY_LEVEL_B                               = 6,                /*     1 1 0 call priority level B   */
    NAS_CALL_PRIORITY_LEVEL_A                               = 7                 /*     1 1 1 call priority level A   */
};
typedef VOS_UINT8  NAS_CALL_PRIORITY_ENUM_U8;


/* [10.5.4.1] Extensions of codesets */
/*============================================================================*/


/* [10.5.4.2] Locking shift procedure */
/*============================================================================*/


/* [10.5.4.3] Non-locking shift procedure */
/*============================================================================*/


/* [10.5.4.4] Auxiliary states */
/*============================================================================*/

/* [10.5.4.4a] Backup bearer capability */
/*============================================================================*/
/*Table 10.5.101a/3GPP TS 24.008: Backup bearer capability information element*/

/* Radio channel requirement (octet 3)
   In A/Gb mode and GERAN Iu mode, Bits 6 and 7 are spare bits.
   The sending side shall set bit 7 to value 0 and bit 6 to value 1.          */

enum NAS_CC_BC_CODING_STANDARD_ENUM                                             /* Coding standard (octet 3)         */
{                                                                               /* Bit 5                             */
    NAS_CC_BC_CODING_GSM                                    = 0,                /*     0 GSM standardized coding     */
    NAS_CC_BC_CODING_RESERVED                               = 1                 /*     1 reserved                    */
};
typedef VOS_UINT8   NAS_CC_BC_CODING_STANDARD_ENUM_U8;

enum NAS_CC_TRANSFER_MODE_ENUM                                                  /* Transfer mode (octet 3)           */
{                                                                               /* Bit 4                             */
    NAS_CC_TRANSFER_MODE_CIRCUIT                            = 0,                /*     0 circuit mode                */
    NAS_CC_TRANAFER_MODE_PACKET                             = 1                 /*     1 packet mode                 */
};
typedef VOS_UINT8   NAS_CC_TRANSFER_MODE_ENUM_U8;

enum NAS_CC_INFO_TRANSFER_CAP_ENUM                                              /* Info transfer capability (octet 3)*/
{                                                                               /* Bits 3 2 1                        */
    NAS_CC_ITC_SPEECH                                       = 0,                /*      0 0 0 speech                 */
    NAS_CC_ITC_UDI                                          = 1,                /*      0 0 1 UDI                    */
    NAS_CC_ITC_3D1K                                         = 2,                /*      0 1 0 3.1 kHz audio, ex PLMN */
    NAS_CC_ITC_FAX                                          = 3,                /*      0 1 1 facsimile group 3      */
    NAS_CC_ITC_OTHER                                        = 5,                /*      1 0 1 Other ITC (Octet 5a)   */
    NAS_CC_ITC_AUXILIARY_SPEECH                             = 6,                /*      1 1 0 Auxiliary speech(for ALS)*/
    NAS_CC_ITC_RESERVED                                     = 7                 /*      1 1 1 reserved               */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_INFO_TRANSFER_CAP_ENUM_U8;

/*Table 10.5.101b/3GPP TS 24.008: Backup bearer capability information element*/

/* Compression (octet 4)
   Bit 7 is spare and shall be set to "0". */

enum NAS_CC_STRUCTURE_ENUM                                                      /* Structure (octet 4)               */
{                                                                               /* Bits 6 5                          */
   NAS_CC_STRUCTURE_STRUCTERD                               = 0,                /* 0 0 service data unit integrity   */
   NAS_CC_STRUCTURE_UNSTRUCTURED                            = 3                 /* 1 1 unstructured                  */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_STRUCTURE_ENUM_U8;

enum NAS_CC_DUPLEX_MODE_ENUM                                                    /* Duplex mode (octet 4)             */
{                                                                               /* Bit 4                             */
   NAS_CC_HALF_DUPLEX                                       = 0,                /*     0 half duplex                 */
   NAS_CC_FULL_DUPLEX                                       = 1                 /*     1 full duplex                 */
};
typedef VOS_UINT8   NAS_CC_DUPLEX_MODE_ENUM_U8;

enum NAS_CC_CONFIGURATION_ENUM                                                  /* Configuration (octet 4)           */
{                                                                               /* Bit 3                             */
   NAS_CC_CONFIGURATION_P2P                                 = 0                 /*     0 point-to-point              */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_CONFIGURATION_ENUM_U8;

/* NIRR (octet 4) (Negotiation of Intermediate Rate Requested)
   In A/Gb mode and GERAN Iu mode,not applicable for UTRAN Iu modedata services.
   Bit 2 is spare and shall be set to "0". */

enum NAS_CC_ESTABLISHMENT_ENUM                                                  /* Establishment (octet 4)           */
{                                                                               /* Bit 1                             */
    NAS_CC_ESTABLISHMNET_DEMAND                             = 0                 /*     0 demand                      */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_ESTABLISHMENT_ENUM_U8;

/*Table 10.5.101c/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_ACCESS_IDENTITY_ENUM                                                /* Access identity (octet 5)         */
{                                                                               /* Bits 7 6                          */
    NAS_CC_OCTET_IDENTIFIER                                 = 0                 /*      0 0 octet identifier         */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_ACCESS_IDENTITY_ENUM_U8;

enum NAS_CC_RATE_ADAPTION_ENUM                                                  /* Rate adaption (octet 5)           */
{                                                                               /* Bits 5 4                          */
    NAS_CC_RATE_ADAPTION_NONE                               = 0,                /*      0 0 no rate adaption         */
    NAS_CC_RATE_ADAPTION_V110                               = 1,                /*      0 1 V.110, I.460/X.30        */
    NAS_CC_RATE_ADAPTION_X31                                = 2,                /*      1 0 ITU-T X.31 flag stuffing */
    NAS_CC_RATE_ADAPTION_OTHER                              = 3                 /*      1 1 Other rate adaption (5a) */
};
typedef VOS_UINT8   NAS_CC_RATE_ADAPTION_ENUM_U8;

enum NAS_CC_SIG_ACCESS_PROTOCOL_ENUM                                            /* Sig. access protocol (octet 5)    */
{                                                                               /* Bits 3 2 1                        */
    NAS_CC_SAP_I440_450                                     = 0                 /*      0 0 1 I.440/450              */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_SIG_ACCESS_PROTOCOL_ENUM_U8;

/*Table 10.5.101d/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_OTHER_ITC_ENUM                                                      /* Other ITC (octet 5a)              */
{                                                                               /* Bit 7 6                           */
    NAS_CC_OTHER_ITC_RDI                                    = 0                 /*     0 0 RDI                       */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_OTHER_ITC_ENUM_U8;

enum NAS_CC_OTHER_RATE_ADAPTION_ENUM                                            /* Other rate adaption (octet 5a)    */
{                                                                               /* Bit 5 4                           */
    NAS_CC_OTHER_RA_V120                                    = 0,                /*     0 0 V.120                     */
    NAS_CC_OTHER_RA_H223_H245                               = 1,                /*     0 1 H.223 & H.245             */
    NAS_CC_OTHER_RA_PIAFS                                   = 2                 /*     1 0 PIAFS                     */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_OTHER_RATE_ADAPTION_ENUM_U8;

/*Table 10.5.101e/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_L1_IDENTITY_ENUM                                                    /* Layer 1 identity (octet 6)        */
{                                                                               /* Bits 7 6                          */
    NAS_CC_L1_OCTET_IDENTIFIER                              = 1                 /*      0 1 octet identifier         */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_L1_OCTET_IDENTIFIER_ENUM_U8;

enum NAS_CC_UIL1P_ENUM                                                          /* User info l1 protocol (octet 6)   */
{                                                                               /* Bits 5 4 3 2                      */
    NAS_CC_DEFAULT_L1_PROTOCOL                              = 0                 /*      0 0 0 0 default l1 protocol  */
};                                                                              /*      All other values reserved.   */
typedef VOS_UINT8   NAS_CC_UIL1P_ENUM_U8;

enum NAS_CC_SYNC_ASYNC_ENUM                                                     /* Synchronous/asynchronous (octet 6)*/
{                                                                               /* Bit 1                             */
    NAS_CC_SYNC                                             = 0,                /*     0 synchronous                 */
    NAS_CC_ASYNC                                            = 1                 /*     1 asynchronous                */
};
typedef VOS_UINT8   NAS_CC_SYNC_ASYNC_ENUM_U8;

/*Table 10.5.101f/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_NUM_OF_STOP_BITS_ENUM                                               /* Number of Stop Bits (octet 6a)    */
{                                                                               /* Bit 7                             */
    NAS_CC_1_STOP_BITS                                      = 0,                /*     0 1 bit (also in sync mode)   */
    NAS_CC_2_STOP_BITS                                      = 1                 /*     1 2 bits                      */
};
typedef VOS_UINT8   NAS_CC_NUM_OF_STOP_BITS_ENUM_U8;

enum NAS_CC_NEGOTIATION_ENUM                                                    /* Negotiation (octet 6a)            */
{                                                                               /* Bit 6                             */
    NAS_CC_NO_NEGOTIATION                                   = 0                 /*     0 negotiation not possible    */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_NEGOTIATION_ENUM_U8;


enum NAS_CC_NUM_OF_DATA_BITS_ENUM                                               /* Num of data bits (octet 6a)       */
{                                                                               /* Bit 5                             */
    NAS_CC_7BITS_DATA                                       = 0,                /*     0 7 bits                      */
    NAS_CC_8BITS_DATA                                       = 1                 /*     1 8 bits                      */
};
typedef VOS_UINT8   NAS_CC_NUM_OF_DATA_BITS_ENUM_U8;


enum NAS_CC_USER_RATE_ENUM                                                      /* User rate (octet 6a)              */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_USER_RATE_300                                    = 1,                /*      0 0 0 1 0.3 kbps X.1 & V.110 */
    NAS_CC_USER_RATE_1200                                   = 2,                /*      0 0 1 0 1.2 kbps X.1 & V.110 */
    NAS_CC_USER_RATE_2400                                   = 3,                /*      0 0 1 1 2.4 kbps X.1 & V.110 */
    NAS_CC_USER_RATE_4800                                   = 4,                /*      0 1 0 1 9.6 kbps X.1 & V.110 */
    NAS_CC_USER_RATE_9600                                   = 5,                /*      0 1 0 1 9.6 kbps X.1 & V.110 */
    NAS_CC_USER_RATE_12K                                    = 6,                /*      0 1 1 0 12 kbps transparent  */
    NAS_CC_USER_RATE_RESERVED                               = 7                 /*      0 1 1 1 reserved             */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_USER_RATE_ENUM_U8;

/*Table 10.5.101g/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_INTER_RATE_ENUM                                                     /* V.110/X.30 Inter-rate (octet 6b)  */
{                                                                               /* Bits 7 6                          */
    NAS_CC_INTER_RATE_RESERVED1                             = 0,                /*      0 0 reserved                 */
    NAS_CC_INTER_RATE_RESERVED2                             = 1,                /*      0 1 reserved                 */
    NAS_CC_INTER_RATE_8K                                    = 2,                /*      1 0 8 kbit/s                 */
    NAS_CC_INTER_RATE_16K                                   = 3                 /*      1 1 16 kbit/s                */
};
typedef VOS_UINT8   NAS_CC_INTER_RATE_ENUM_U8;

enum NAS_CC_NIC_ON_TX_ENUM                                                      /* NIC on Tx (octet 6b)              */
{                                                                               /* Bit 5                             */
    NAS_CC_NIC_ON_TX_NOT_REQUIRE                            = 0,                /*     0 does not require            */
    NAS_CC_NIC_ON_TX_REQUIRE                                = 1                 /*     1 requires                    */
};
typedef VOS_UINT8   NAS_CC_NIC_ON_TX_ENUM_U8;

enum NAS_CC_NIC_ON_RX_ENUM                                                      /* NIC on Rx (octet 6b)              */
{                                                                               /* Bit 4                             */
    NAS_CC_NIC_ON_RX_NOT_ACCEPT                             = 0,                /*     0 cannot accept               */
    NAS_CC_NIC_ON_RX_ACCEPT                                 = 1                 /*     1 can accept                  */
};
typedef VOS_UINT8   NAS_CC_NIC_ON_RX_ENUM_U8;

enum NAS_CC_PARITY_INFO_ENUM                                                    /* Parity information (octet 6b)     */
{                                                                               /* Bits 3 2 1                        */
    NAS_CC_PARITY_ODD                                       = 0,                /*      0 0 0 odd                    */
    NAS_CC_PARITY_EVEN                                      = 2,                /*      0 1 0 even                   */
    NAS_CC_PARITY_FORCED_0                                  = 4,                /*      1 0 0 forced to 0            */
    NAS_CC_PARITY_FORCED_1                                  = 5                 /*      1 0 1 forced to 1            */
};
typedef VOS_UINT8   NAS_CC_PARITY_INFO_ENUM_U8;

/*Table 10.5.101h/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_CONNECTION_ELEMENT_ENUM                                             /* Connection element (octet 6c)     */
{                                                                               /* Bit 7 6                           */
    NAS_CC_CONNECTION_T                                     = 0,                /* 0 0 transparent                   */
    NAS_CC_CONNECTION_NT                                    = 1,                /* 0 1 non transparent (RLP)         */
    NAS_CC_CONNECTION_BOTH_T                                = 2,                /* 1 0 both, T preferred             */
    NAS_CC_CONNECTION_BOTH_NT                               = 3                 /* 1 1 both, NT preferred            */
};
typedef VOS_UINT8   NAS_CC_CONNECTION_ELEMENT_ENUM_U8;

enum NAS_CC_MODEM_TYPE_ENUM                                                     /* Modem type (octet 6c)             */
{                                                                               /* Bits 5 4 3 2 1                    */
    NAS_CC_MODEM_NONE                                       = 0,                /*      0 0 0 0 0 none               */
    NAS_CC_MODEM_V21                                        = 1,                /*      0 0 0 0 1 V.21               */
    NAS_CC_MODEM_V22                                        = 2,                /*      0 0 0 1 0 V.22               */
    NAS_CC_MODEM_V22BIS                                     = 3,                /*      0 0 0 1 1 V.22 bis           */
    NAS_CC_MODEM_RESERVED                                   = 4,                /*      0 0 1 0 0 reserved           */
    NAS_CC_MODEM_V26TER                                     = 5,                /*      0 0 1 0 1 V.26 ter           */
    NAS_CC_MODEM_V32                                        = 6,                /*      0 0 1 1 0 V.32               */
    NAS_CC_MODEM_UNDEFINE                                   = 7,                /*      0 0 1 1 1 undefine interface */
    NAS_CC_MODEM_AUTOBAND                                   = 8                 /*      0 1 0 0 0 autobauding type 1 */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_MODEM_TYPE_ENUM_U8;

/*Table 10.5.101i/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_OTHER_MODEM_TYPE_ENUM                                               /* Other modem type (octet 6d)       */
{                                                                               /* Bits 7 6                          */
    NAS_CC_OTHER_MODEM_NONE                                 = 0,                /*      0 0 no other modem type      */
    NAS_CC_OTHER_MODEM_V34                                  = 2                 /*      1 0 V.34                     */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_OTHER_MODEM_TYPE_ENUM_U8;

enum NAS_CC_FNUR_ENUM                                                           /* Fixed network user rate (octet 6d)*/
{                                                                               /* Bit 5 4 3 2 1                     */
    NAS_CC_FNUR_NONE                                        =  0,               /*     0 0 0 0 0 not applicable      */
    NAS_CC_FNUR_9600                                        =  1,               /*     0 0 0 0 1 9.6 kbit/s          */
    NAS_CC_FNUR_14400                                       =  2,               /*     0 0 0 1 0 14.4 kbit/s         */
    NAS_CC_FNUR_19200                                       =  3,               /*     0 0 0 1 1 19.2 kbit/s         */
    NAS_CC_FNUR_22800                                       =  4,               /*     0 0 1 0 0 28.8 kbit/s         */
    NAS_CC_FNUR_38400                                       =  5,               /*     0 0 1 0 1 38.4 kbit/s         */
    NAS_CC_FNUR_48000                                       =  6,               /*     0 0 1 1 0 48.0 kbit/s         */
    NAS_CC_FNUR_56000                                       =  7,               /*     0 0 1 1 1 56.0 kbit/s         */
    NAS_CC_FNUR_64000                                       =  8,               /*     0 1 0 0 0 64.0 kbit/s         */
    NAS_CC_FNUR_33600                                       =  9,               /*     0 1 0 0 1 33.6 kbit/s         */
    NAS_CC_FNUR_32000                                       = 10,               /*     0 1 0 1 0 32.0 kbit/s         */
    NAS_CC_FNUR_31200                                       = 11                /*     0 1 0 1 1 31.2 kbit/s         */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_FNUR_ENUM_U8;

/*Table 10.5.101j/3GPP TS 24.008: Backup bearer capability information element*/
/* Acceptable channel codings (octet 6e):
   Bits 4 to 7 are spare and shall be set to "0".

   Maximum number of traffic channels (octet 6e):
   Bits 1 to 3 are spare and shall be set to "0". */

/*Table 10.5.101k/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_UIMI_ENUM                                                           /* UIMI (octet 6f)                   */
{                                                                               /* Bits 7 6 5                        */
    NAS_CC_UIMI_NONE                                        = 0,                /*      0 0 0 not allowed/applicable */
    NAS_CC_UIMI_1TCH                                        = 1,                /*      0 0 1 1 TCH/F                */
    NAS_CC_UIMI_2TCH                                        = 2,                /*      0 1 0 2 TCH/F                */
    NAS_CC_UIMI_3TCH                                        = 3,                /*      0 1 1 3 TCH/F                */
    NAS_CC_UIMI_4TCH                                        = 4                 /*      1 0 0 4 TCH/F                */
};                                                                              /*      All other values as 4 TCH/F  */
typedef VOS_UINT8   NAS_CC_UIMI_ENUM_U8;

/* Wanted air interface user rate (octet 6f):
   Bits 1 to 4 are spare and shall be set to "0". */

/*Table 10.5.101m/3GPP TS 24.008: Backup bearer capability information element*/
/* Acceptable Channel Codings extended (octet 6g):
   Bits 3 to 7 are spare and shall be set to "0".
   Bits 2 and 1 are spare. */


/*Table 10.5.101l/3GPP TS 24.008: Backup bearer capability information element*/
enum NAS_CC_L2_IDENTITY_ENUM                                                    /* Layer 2 identity (octet 7)        */
{                                                                               /* Bits 7 6                          */
    NAS_CC_L2_OCTET_IDENTIFIER                              = 2                 /*      1 0 octet identifier         */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_L2_IDENTITY_ENUM_U8;

enum NAS_CC_UIL2P_ENUM                                                          /* User info l2 protocol (octet 7)   */
{                                                                               /* Bits 5 4 3 2 1                    */
    NAS_CC_L2_PROTOCOL_RESERVED1                            =  6,               /*      0 0 1 1 0                    */
    NAS_CC_L2_PROTOCOL_ISO6429                              =  8,               /*      0 1 0 0 0 ISO 6429           */
    NAS_CC_L2_PROTOCOL_RESERVED2                            =  9,               /*      0 0 1 1 0 never used         */
    NAS_CC_L2_PROTOCOL_VIDEOTEX                             = 10,               /*      0 1 0 1 0 videotex profile 1 */
    NAS_CC_L2_PROTOCOL_COPNOFlCT                            = 12,               /*      0 1 1 0 0 COPnoFlCt          */
    NAS_CC_L2_PROTOCOL_RESERVED3                            = 13                /*      0 1 1 0 1                    */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_UIL2P_ENUM_U8;


/* [10.5.4.4a.1] Static conditions for the backup bearer capability IE */
/*============================================================================*/
/* IF ( "speech" == information transfer capability field (octet 3) )
     octets 4, 5, 5a, 5b, 6, 6a, 6b, 6c, 6d, 6e, 6f, 6g and 7, [NOT be INCLUDED]
   ELSE
     (1) octets 4 and 5 [INCLUDED]
     (2) octets 6, 6a, 6b, 6c, 6d, 6e, 6f and 6g are [OPTIONAL]
     Sub CASE:
     octet 6 [INCLUDED], octets 6a, 6b, and 6c [ALSO be INCLUDED]
     octet 6d [INCLUDED], octets 6e, 6f and 6g [MAY] be included

   IF ( "facsimile group 3" == information transfer capability field (octet 3) )
   AND ( octet 6c [INCLUDED] )
     modem type field (octet 6c) shall indicate ["none"]

   IF ( "other ITC" == information transfer capability field (octet 3) )
   OR ( "other rate adaption" == the rate adaption field (octet 5) )
     modem type field (octet 6c) shall not indicate "autobauding type 1"
   UNLESS
     ( "non transparent" == connection element field (octet 6c) )             */


/* [10.5.4.5] Bearer capability */
/*============================================================================*/
/* Table 10.5.102/3GPP TS 24.008: Bearer capability information element */

/* Radio channel requirement (octet 3), network to MS direction
   In A/Gb mode and GERAN Iu mode, Bits 6 and 7 are spare bits.
   The sending side shall set bit 7 to value 0 and bit 6 to value 1.          */

enum NAS_CC_RADIO_CH_REQUIREMENT_ENUM                                           /* Radio Ch requirement (octet 3)    */
{                                                                               /* Bits 7 6                          */
    NAS_CC_RADIO_CH_RESERVED                                = 0,                /*      0 0 reserved                 */
    NAS_CC_RADIO_CH_FULL_RATE                               = 1,                /*      0 1 full rate only           */
    NAS_CC_RADIO_CH_DUAL_RATE_H                             = 2,                /*      1 0 dual rate / H preferred  */
    NAS_CC_RADIO_CH_DUAL_RATE_F                             = 3                 /*      1 1 dual rate / F preferred  */
};
typedef VOS_UINT8   NAS_CC_RADIO_CH_REQUIREMENT_ENUM_U8;

/* [Defined] Coding standard (octet 3) */

/* [Defined] Transfer mode (octet 3) */

/* [Defined] Information transfer capability (octet 3) */

/* Table 10.5.103/3GPP TS 24.008 Bearer capability information element */
enum NAS_CC_CTM_ENUM                                                            /* CTM       (octet 3a)              */
{                                                                               /* Bit 6                             */
    NAS_CC_CTM_TEXT_NOT_SUPPORTED                           = 0,                /* 0 CTM not supported               */
    NAS_CC_CTM_TEXT_SUPPORTED                               = 1                 /* 1 CTM supported                   */
};
typedef VOS_UINT8   NAS_CC_CTM_ENUM_U8;

enum NAS_CC_SPEECH_VER_ENUM                                                     /* Speech version (octet(s) 3a etc.) */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_GSM_FR_SPEECH_VER1                               =  0,               /*      0 0 0 0 GSM FR version 1     */
    NAS_CC_GSM_FR_SPEECH_VER2                               =  2,               /*      0 0 1 0 GSM FR version 2     */
    NAS_CC_GSM_FR_SPEECH_VER3                               =  4,               /*      0 1 0 0 GSM FR version 3     */
    NAS_CC_GSM_FR_SPEECH_VER4                               =  6,               /*      0 1 1 0 GSM FR version 4     */
    NAS_CC_GSM_FR_SPEECH_VER5                               =  8,               /*      1 0 0 0 GSM FR version 5     */
    NAS_CC_GSM_HR_SPEECH_VER1                               =  1,               /*      0 0 0 1 GSM HR version 1     */
    NAS_CC_GSM_HR_SPEECH_VER3                               =  5,               /*      0 1 0 1 GSM HR version 3     */
    NAS_CC_GSM_HR_SPEECH_VER4                               =  7,               /*      0 1 1 1 GSM HR version 4     */
    NAS_CC_GSM_HR_SPEECH_VER6                               = 11,               /*      1 0 1 1 GSM HR version 6     */
    NAS_CC_NO_SPEECH                                        = 15                /*      1 1 1 1 no speech supported  */
};                                                                              /* All other values "speech ver tbd" */
typedef VOS_UINT8   NAS_CC_SPEECH_VER_ENUM_U8;

/* Table 10.5.104/3GPP TS 24.008: Bearer capability information element */
enum NAS_CC_COMPRESSION_ENUM                                                    /* Compression (octet 4)             */
{                                                                               /* Bit 7                             */
   NAS_CC_NO_DATA_COMPRESION                                = 0,                /*     0 no data compression         */
   NAS_CC_DATA_COMPRESION                                   = 1                 /*     1 data compression            */
};
typedef VOS_UINT8   NAS_CC_COMPRESSION_ENUM_U8;

/* [Defined] Structure (octet 4) */

/* [Defined] Duplex mode (octet 4) */

/* [Defined] Configuration (octet 4) */

enum NAS_CC_NIRR_ENUM                                                           /* NIRR (octet 4)                    */
{                                                                               /* Bit 2                             */
   NAS_CC_NIRR_DISABLE                                      = 0,                /*     0 No meaning is associated    */
   NAS_CC_NIRR_ENABLE                                       = 1                 /*     1 -                           */
};
typedef VOS_UINT8   NAS_CC_NIRR_ENUM_U8;

/* [Defined] Establishment (octet 4) */

/* Table 10.5.105/3GPP TS 24.008: Bearer capability information element */
/* [Defined] Access identity (octet 5) */
/* [Defined] Rate adaption (octet 5) */
/* [Defined] Signalling access protocol (octet 5) */

/* Table 10.5.106/3GPP TS 24.008: Bearer capability information element */
/* [Defined] Other ITC (octet 5a) */
/* [Defined] Other rate adaption (octet 5a) */

/* Table 10.5.107/3GPP TS 24.008: Bearer capability information element */
enum NAS_CC_RATE_ADAPTION_HEADER_ENUM                                           /* RA header/no header (octet 5b)    */
{                                                                               /* Bit 7                             */
    NAS_CC_RA_NO_HEADER                                     = 0,                /*     0 header not included         */
    NAS_CC_RA_HEADER                                        = 1                 /*     1 header included             */
};
typedef VOS_UINT8   NAS_CC_RATE_ADAPTION_HEADER_ENUM_U8;

enum NAS_CC_MULTI_FRAME_EST_ENUM                                                /* Multi-frame establishment support */
{                                                                               /* Bit 6                             */
    NAS_CC_MF_EST_NO_SUPPORT                                = 0,                /*     0 MF EST not supported        */
    NAS_CC_MF_EST_SUPPORT                                   = 1                 /*     1 MF EST supported            */
};
typedef VOS_UINT8   NAS_CC_MULTI_FRAME_EST_ENUM_U8;

enum NAS_CC_OP_MODE_ENUM                                                        /* Mode of operation (octet 5b)      */
{                                                                               /* Bit 5                             */
    NAS_CC_OP_MODE_BIT_TRANS                                = 0,                /*     0 Bit transparent mode        */
    NAS_CC_OP_MODE_PROTOCOL                                 = 1                 /*     1 Protocol sensitive mode     */
};
typedef VOS_UINT8   NAS_CC_OP_MODE_ENUM_U8;

enum NAS_CC_LLI_NEGOTIATION_ENUM                                                /* LLI negotiation (octet 5b)        */
{                                                                               /* Bit 4                             */
    NAS_CC_LLI_256                                          = 0,                /*     0 Default, LLI=256 only       */
    NAS_CC_LLI_N                                            = 1                 /*     1 Full protocol negotiation   */
};
typedef VOS_UINT8   NAS_CC_LLI_NEGOTIATION_ENUM_U8;

enum NAS_CC_ASSIGNOR_ASSIGNEE_ENUM                                              /* Assignor/Assignee (octet 5b)      */
{                                                                               /* Bit 3                             */
    NAS_CC_MSG_ORIG_DEFAULT                                 = 0,                /*     0 default assignee            */
    NAS_CC_MSG_ORIG_ASSIGNOR                                = 1                 /*     1 assignor only               */
};
typedef VOS_UINT8   NAS_CC_ASSIGNOR_ASSIGNEE_ENUM_U8;

enum NAS_CC_IN_OUT_BAND_NEG_ENUM                                                /* band negotiation (octet 5b)       */
{                                                                               /* Bit 2                             */
    NAS_CC_IN_BAND_NEGOTIATION                              = 0,                /*     0 in-band                     */
    NAS_CC_OUT_BAND_NEGOTIATION                             = 1                 /*     1 out of band                 */
};
typedef VOS_UINT8   NAS_CC_IN_OUT_BAND_NEG_ENUM_U8;

/* Table 10.5.108/3GPP TS 24.008: Bearer capability information element */
/* [Defined] Layer 1 identity (octet 6) */
/* [Defined] User information layer 1 protocol (octet 6) */
/* [Defined] Synchronous/asynchronous (octet 6) */

/* Table 10.5.109/3GPP TS 24.008: Bearer capability information element */
/* [Defined] Number of Stop Bits (octet 6a) */
/* [Defined] Negotiation (octet 6a) */
/* [Defined] Number of data bits excluding parity bit if present (octet 6a) */
/* [Defined] User rate (octet 6a) */

/* Table 10.5.110/3GPP TS 24.008: Bearer capability information element */
/* [Defined] V.110/X.30 rate adaptation Intermediate rate (octet 6b) */
/* [Defined] Network independent clock (NIC) on transmission (Tx) (octet 6b) */
/* [Defined] Network independent clock (NIC) on reception (Rx) (octet 6b) */
/* [Defined] Parity information (octet 6b) */

/* Table 10.5.111/3GPP TS 24.008: Bearer capability information element */
/* [Defined] Connection element (octet 6c) */
/* [Defined] Modem type (octet 6c) */

/* Table 10.5.112/3GPP TS 24.008: Bearer capability information element */
/* [Defined] Other modem type (octet 6d) */
/* [Defined] Fixed network user rate (octet 6d) */

/* Table 10.5.113/3GPP TS 24.008: Bearer capability information element */
enum NAS_CC_TCH_F14_4_ENUM                                                      /* Acceptable ch codings (octet 6e)  */
{                                                                               /* Bit 7                             */
    NAS_CC_TCH_F14_4_NOT_ACCEPTABLE                         = 0,                /*     0 TCH/F14.4 not acceptable    */
    NAS_CC_TCH_F14_4_ACCEPTABLE                             = 1                 /*     1 TCH/F14.4 acceptable        */
};
typedef VOS_UINT8   NAS_CC_TCH_F14_4_ENUM_U8;

enum NAS_CC_TCH_F9_6_ENUM                                                       /* Acceptable ch codings (octet 6e)  */
{                                                                               /* Bit 5                             */
    NAS_CC_TCH_F9_6_NOT_ACCEPTABLE                          = 0,                /*     0 TCH/F9.6 not acceptable     */
    NAS_CC_TCH_F9_6_ACCEPTABLE                              = 1                 /*     1 TCH/F9.6 acceptable         */
};
typedef VOS_UINT8   NAS_CC_TCH_F9_6_ENUM_U8;

enum NAS_CC_TCH_F4_8_ENUM                                                       /* Acceptable ch codings (octet 6e)  */
{                                                                               /* Bit 4                             */
    NAS_CC_TCH_F4_8_NOT_ACCEPTABLE                          = 0,                /*     0 TCH/F4.8 not acceptable     */
    NAS_CC_TCH_F4_8_ACCEPTABLE                              = 1                 /*     1 TCH/F4.8 acceptable         */
};
typedef VOS_UINT8   NAS_CC_TCH_F4_8_ENUM_U8;

/* Acceptable channel codings (octet 6e), network to MS direction:
   Bits 4 to 7 are spare and shall be set to "0". */

enum NAS_CC_MAX_TCH_NUM_ENUM                                                    /* Maximum number of TCH (octet 6e)  */
{                                                                               /* Bits 3 2 1                        */
    NAS_CC_MAX_1TCH                                         = 0,                /*      0 0 0 1 TCH                  */
    NAS_CC_MAX_2TCH                                         = 1,                /*      0 0 1 2 TCH                  */
    NAS_CC_MAX_3TCH                                         = 2,                /*      0 1 0 3 TCH                  */
    NAS_CC_MAX_4TCH                                         = 3,                /*      0 1 0 4 TCH                  */
    NAS_CC_MAX_5TCH                                         = 4,                /*      0 1 0 5 TCH                  */
    NAS_CC_MAX_6TCH                                         = 5,                /*      0 1 0 6 TCH                  */
    NAS_CC_MAX_7TCH                                         = 6,                /*      0 1 0 7 TCH                  */
    NAS_CC_MAX_8TCH                                         = 7                 /*      0 1 0 8 TCH                  */
};
typedef VOS_UINT8   NAS_CC_MAX_TCH_NUM_ENUM_U8;

/* Maximum number of traffic channels (octet 6e), network to MS direction:
   Bits 1 to 3 are spare and shall be set to "0". */

/* Table 10.5.114/3GPP TS 24.008: Bearer capability information element       */
/* [Defined] UIMI, User initiated modification indication (octet 6f) */

enum NAS_CC_WAIUR_ENUM                                                          /* Wanted AIUR (octet 6f)            */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_WAIUR_NONE                                       =  0,               /*      0 0 0 0 AIUR not applicable  */
    NAS_CC_WAIUR_9600                                       =  1,               /*      0 0 0 1 9.6 kbit/s           */
    NAS_CC_WAIUR_14400                                      =  2,               /*      0 0 1 0 14.4 kbit/s          */
    NAS_CC_WAIUR_19200                                      =  3,               /*      0 0 1 1 19.2 kbit/s          */
    NAS_CC_WAIUR_28800                                      =  5,               /*      0 1 0 1 28.8 kbit/s          */
    NAS_CC_WAIUR_38400                                      =  6,               /*      0 1 1 0 38.4 kbit/s          */
    NAS_CC_WAIUR_43200                                      =  7,               /*      0 1 1 1 43.2 kbit/s          */
    NAS_CC_WAIUR_57600                                      =  8,               /*      1 0 0 1 as 38.4 kbit/s       */
    NAS_CC_WAIUR_38400_1                                    =  9,               /*      1 0 1 0 as 38.4 kbit/s       */
    NAS_CC_WAIUR_38400_2                                    = 10,               /*      1 0 1 1 as 38.4 kbit/s       */
    NAS_CC_WAIUR_38400_3                                    = 11,               /*      1 0 1 1 as 38.4 kbit/s       */
    NAS_CC_WAIUR_38400_4                                    = 12                /*      1 1 0 0 as 38.4 kbit/s       */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_WAIUR_ENUM_U8;

/* Wanted air interface user rate (octet 6f), network to MS direction:
   Bits 1 to 4 are spare and shall be set to "0". */

/* Table 10.5.115/3GPP TS 24.008: Bearer capability information element */
/* [Defined] Layer 2 identity (octet 7) */
/* [Defined] User information layer 2 protocol (octet 7) */

/* Table 10.5.115a/3GPP TS 24.008: Bearer capability information element */
enum NAS_CC_TCH_F28_8_ENUM                                                      /* Acceptable ch codings (octet 6g)  */
{                                                                               /* Bit 7                             */
    NAS_CC_TCH_F28_8_NOT_ACCEPTABLE                         = 0,                /*     0 TCH/F28.8 not acceptable    */
    NAS_CC_TCH_F28_8_ACCEPTABLE                             = 1                 /*     1 TCH/F28.8 acceptable        */
};
typedef VOS_UINT8   NAS_CC_TCH_F28_8_ENUM_U8;

enum NAS_CC_TCH_F32_0_ENUM                                                      /* Acceptable ch codings (octet 6g)  */
{                                                                               /* Bit 6                             */
    NAS_CC_TCH_F32_0_NOT_ACCEPTABLE                         = 0,                /*     0 TCH/F32.0 not acceptable    */
    NAS_CC_TCH_F32_0_ACCEPTABLE                             = 1                 /*     1 TCH/F32.0 acceptable        */
};
typedef VOS_UINT8   NAS_CC_TCH_F32_0_ENUM_U8;

enum NAS_CC_TCH_F43_2_ENUM                                                      /* Acceptable ch codings (octet 6g)  */
{                                                                               /* Bit 5                             */
    NAS_CC_TCH_F43_2_NOT_ACCEPTABLE                         = 0,                /*     0 TCH/F43.2 not acceptable    */
    NAS_CC_TCH_F43_2_ACCEPTABLE                             = 1                 /*     1 TCH/F43.2 acceptable        */
};
typedef VOS_UINT8   NAS_CC_TCH_F43_2_ENUM_U8;

enum NAS_CC_CCAI_ENUM                                                           /* CCAI (octet 6g)                   */
{                                                                               /* Bits 4 3                          */
    NAS_CC_CCAI_CH                                          = 0,                /*      0 0 Channel coding symmetry  */
    NAS_CC_CCAI_DOWNLINK                                    = 2,                /*      1 0 Downlink biased channel  */
    NAS_CC_CCAI_UPLINK                                      = 1,                /*      0 1 Uplink biased channel    */
    NAS_CC_CCAI_UNUSED                                      = 3                 /*      1 1 Unused as 0 0            */
};
typedef VOS_UINT8   NAS_CC_CCAI_ENUM_U8;

/* EDGE Channel Codings (octet 6g), network to MS direction:
   Bits 3 to 7 are spare and shall be set to "0".
   Bits 2 and 1 are spare. */


/* [10.5.4.5.1] Static conditions for the bearer capability IE contents */
/*============================================================================*/
/* [Defined] 10.5.4.4a.1 */

/* [10.5.4.5a] Call Control Capabilities */
/*============================================================================*/
/* Table 10.5.116/3GPP TS 24.008: Call Control Capabilities */
enum NAS_CC_DTMF_ENUM                                                           /* DTMF (octet 3)                    */
{                                                                               /* Bit 1                             */
    NAS_CC_DTMF_RESERVED                                    = 0,                /*     0 reserved                    */
    NAS_CC_DTMF_SPECIFIED                                   = 1                 /*     1 specified [5.5.7]           */
};
typedef VOS_UINT8   NAS_CC_DTMF_ENUM_U8;

enum NAS_CC_PCP_ENUM                                                            /* PCP (octet 3)                     */
{                                                                               /* Bit 2                             */
    NAS_CC_PCP_NOT_SUPPORT                                  = 0,                /*     0 not support PCP             */
    NAS_CC_PCP_SUPPORT                                      = 1                 /*     1 support PCP                 */
};
typedef VOS_UINT8  NAS_CC_PCP_ENUM_U8;

enum NAS_CC_ENICM_ENUM                                                          /* ENICM (octet 3)                   */
{                                                                               /* Bit 3                             */
    NAS_CC_ENICM_NOT_SUPPORT                                = 0,                /*     0 not support ENICM           */
    NAS_CC_ENICM_SUPPORT                                    = 1                 /*     1 support ENICM [5.3.4.3]     */
};
typedef VOS_UINT8  NAS_CC_ENICM_ENUM_U8;


enum NAS_CC_MAX_SUPPORT_BEARERS_ENUM                                            /* Max supported bearers (octet 3)    */
{                                                                               /* Bits 8 7 6 5                      */
    NAS_CC_BEARER_SUPPORTED_1                               =  0,               /*      0 0 0 0  1 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_2                               =  1,               /*      0 0 0 1  2 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_3                               =  2,               /*      0 0 1 0  3 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_4                               =  3,               /*      0 0 1 1  4 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_5                               =  4,               /*      0 1 0 0  5 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_6                               =  5,               /*      0 1 0 1  6 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_7                               =  6,               /*      0 1 1 0  7 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_8                               =  7,               /*      0 1 1 1  8 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_9                               =  8,               /*      1 0 0 0  9 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_10                              =  9,               /*      1 0 0 1 10 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_11                              = 10,               /*      1 0 1 0 11 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_12                              = 11,               /*      1 0 1 1 12 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_13                              = 12,               /*      1 1 0 0 13 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_14                              = 13,               /*      1 1 0 1 14 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_15                              = 14,               /*      1 1 1 0 15 bearer supported  */
    NAS_CC_BEARER_SUPPORTED_16                              = 15                /*      1 1 1 1 16 bearer supported  */
};
typedef VOS_UINT8   NASC_MAX_SUPPORT_BEARERS_ENUM_U8;


enum NAS_CC_MAX_SPEECH_BEARERS_ENUM                                             /* Max speech bearers (octet 4)      */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_SPEECH_BEARER_1                                  = 0                 /*      0 0 0 0  1 speech bearer     */
};
typedef VOS_UINT8   NAS_CC_MAX_SPEECH_BEARERS_ENUM_U8;


/* [10.5.4.6] Call state */
/*============================================================================*/
/* Table 10.5.117/3GPP TS 24.008: Call state information element */
enum NAS_CC_CODING_STANDARD_ENUM                                                /* Coding standard (octet 2)         */
{                                                                               /* Bits 8 7                          */
    NAS_CC_CODING_Q931                                      = 0,                /*      0 0 ITU-T Rec. Q.931         */
    NAS_CC_CODING_RESERVED                                  = 1,                /*      0 1 reserved                 */
    NAS_CC_CODING_NATIONAL                                  = 2,                /*      1 0 national standard        */
    NAS_CC_CODING_GSM                                       = 3                 /*      1 1 GSM PLMNS                */
};
typedef VOS_UINT8   NAS_CC_CODING_STANDARD_ENUM_U8;

/* [10.5.4.7] Called party BCD number */
/*============================================================================*/
/* Table 10.5.118/3GPP TS 24.008: Called party BCD number */
enum NAS_CC_TON_ENUM                                                            /* Type of number (octet 3)          */
{                                                                               /* Bits 7 6 5                        */
    NAS_CC_TON_UNKNOWN                                      = 0,                /*      0 0 0 unknown                */
    NAS_CC_TON_INTERNATIONAL                                = 1,                /*      0 0 1 international number   */
    NAS_CC_TON_NATIONAL                                     = 2,                /*      0 1 0 national number        */
    NAS_CC_TON_NETWORK_SPEC                                 = 3,                /*      0 1 1 specific number        */
    NAS_CC_TON_SHORT_CODE                                   = 4,                /*      1 0 0 short code             */
    NAS_CC_TON_RESERVED1                                    = 5,                /*      1 0 1 reserved               */
    NAS_CC_TON_RESERVED2                                    = 6,                /*      1 1 0 reserved               */
    NAS_CC_TON_RESERVED_EX                                  = 7                 /*      1 1 1 reserved for extension */
};
typedef VOS_UINT8   NAS_CC_TON_ENUM_U8;

enum NAS_CC_NPI_ENUM                                                            /* Numbering plan identification (3) */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_NPI_UNKNOWN                                      =  0,               /*      0 0 0 0 unknown              */
    NAS_CC_NPI_ISDN                                         =  1,               /*      0 0 0 1 ISDN                 */
    NAS_CC_NPI_DATA                                         =  3,               /*      0 0 1 1 data                 */
    NAS_CC_NPI_TELEX                                        =  4,               /*      0 1 0 0 telex                */
    NAS_CC_NPI_NATIONAL                                     =  8,               /*      1 0 0 0 national             */
    NAS_CC_NPI_PRIVATE                                      =  9,               /*      1 0 0 1 private              */
    NAS_CC_NPI_RESERVED_CTS                                 = 11,               /*      1 0 1 1 reserved for CTS     */
    NAS_CC_NPI_RESERVED_EX                                  = 15                /*      1 1 1 1 for extension        */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_NPI_ENUM_U8;

enum NAS_CC_BCD_NUM_ENUM                                                        /* Number digits (octets 4, etc.)    */
{                                                                               /* Bits Number digit value           */
    NAS_CC_BCD_NUM_0                                        =  0,               /* 0 0 0 0 - 0                       */
    NAS_CC_BCD_NUM_1                                        =  1,               /* 0 0 0 1 - 1                       */
    NAS_CC_BCD_NUM_2                                        =  2,               /* 0 0 1 0 - 2                       */
    NAS_CC_BCD_NUM_3                                        =  3,               /* 0 0 1 1 - 3                       */
    NAS_CC_BCD_NUM_4                                        =  4,               /* 0 1 0 0 - 4                       */
    NAS_CC_BCD_NUM_5                                        =  5,               /* 0 1 0 1 - 5                       */
    NAS_CC_BCD_NUM_6                                        =  6,               /* 0 1 1 0 - 6                       */
    NAS_CC_BCD_NUM_7                                        =  7,               /* 0 1 1 1 - 7                       */
    NAS_CC_BCD_NUM_8                                        =  8,               /* 1 0 0 0 - 8                       */
    NAS_CC_BCD_NUM_9                                        =  9,               /* 1 0 0 1 - 9                       */
    NAS_CC_BCD_NUM_STAR                                     = 10,               /* 1 0 1 0 - *                       */
    NAS_CC_BCD_NUM_POUND                                    = 11,               /* 1 0 1 1 - #                       */
    NAS_CC_BCD_NUM_a                                        = 12,               /* 1 1 0 0 - a                       */
    NAS_CC_BCD_NUM_b                                        = 13,               /* 1 1 0 1 - b                       */
    NAS_CC_BCD_NUM_c                                        = 14,               /* 1 1 1 0 - c                       */
    NAS_CC_BCD_NUM_END                                      = 15                /* 1 1 1 1 - used as an endmark      */
};
typedef VOS_UINT8   NAS_CC_BCD_NUM_ENUM_U8;


/* [10.5.4.8] Called party subaddress */
/*============================================================================*/
/* Table 10.5.119/3GPP TS 24.008: Called party subaddress */
enum NAS_CC_TYPE_OF_SUBADDR_ENUM                                                /* Type of subaddress (octet 3)      */
{                                                                               /* Bits 7 6 5                        */
    NAS_CC_SUBADDR_NSAP                                     = 0,                /*      0 0 0 NSAP                   */
    NAS_CC_USER_SPEC                                        = 2                 /*      0 1 0 User specified         */
};                                                                              /* All other values are reserved     */
typedef VOS_UINT8   NAS_CC_TYPE_OF_SUBADDR_ENUM_U8;

enum NAS_CC_ODD_EVEN_IND_ENUM                                                   /* Odd/even indicator (octet 3)      */
{                                                                               /* Bit 4                             */
    NAS_CC_EVEN_INDICATOR                                   = 0,                /*     0 even                        */
    NAS_CC_ODD_INDICATOR                                    = 1                 /*     1 odd                         */
};
typedef VOS_UINT8   NAS_CC_ODD_EVEN_IND_ENUM_U8;

/* Subaddress information (octet 4, etc...) */


/* [10.5.4.9] Calling party BCD number */
/*============================================================================*/
/* Table 10.5.120/3GPP TS 24.008: Calling party BCD number */
enum NAS_CC_PRESENTATION_IND_ENUM                                               /* Presentation indicator (octet 3a) */
{                                                                               /* Bits 7 6                          */
    NAS_CC_PRESENTATION_ALLOWED                             = 0,                /*      0 0 Presentation allowed     */
    NAS_CC_PRESENTATION_RESTRICTED                          = 1,                /*      0 1 Presentation restricted  */
    NAS_CC_PRESENTATION_NOT_AVAILABLE                       = 2,                /*      1 0 Number not available     */
    NAS_CC_PRESENTATION_RESERVED                            = 3                 /*      1 1 Reserved                 */
};
typedef VOS_UINT8   NAS_CC_PRESENTATION_IND_ENUM_U8;

enum NAS_CC_SCREENING_IND_ENUM                                                  /* Screening indicator (octet 3a)    */
{                                                                               /* Bits 2 1                          */
    NAS_CC_SCREENING_USER_NOT                               = 0,                /*      0 0 User, not screened       */
    NAS_CC_SCREENING_USER_V_PASS                            = 1,                /*      0 1 User, verified & passed  */
    NAS_CC_SCREENING_USER_V_FAIL                            = 2,                /*      1 0 User, verified & failed  */
    NAS_CC_SCREENING_NETWORK                                = 3                 /*      1 1 Network provided         */
};
typedef VOS_UINT8   NAS_CC_SCREENING_IND_ENUM_U8;


/* [10.5.4.10] Calling party subaddress */
/*============================================================================*/
/* Table 10.5.121/3GPP TS 24.008: Calling party subaddress */
/* [Defined] Type of subaddress (octet 3) */
/* [Defined] Odd/even indicator (octet 3) */


/* 10.5.4.11 Cause */
/*============================================================================*/
/* Table 10.5.122/3GPP TS 24.008: Cause information element */
/* [Defined] Coding standard (octet 3) */

enum NAS_CC_LOCATION_ENUM                                                       /* Location (octet 3)                */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_LOCATION_USER                                    =  0,               /*      0 0 0 0 user                 */
    NAS_CC_LOCATION_PRIVATE_LOCAL                           =  1,               /*      0 0 0 1 private / local user */
    NAS_CC_LOCATION_PUBLIC_LOCAL                            =  2,               /*      0 0 1 0 public / local user  */
    NAS_CC_LOCATION_TRANSIT                                 =  3,               /*      0 0 1 1 transit network      */
    NAS_CC_LOCATION_PUBLIC_REMOTE                           =  4,               /*      0 1 0 0 public / remote user */
    NAS_CC_LOCATION_PRIVATE_REMOTE                          =  5,               /*      0 1 0 1 private / remote user*/
    NAS_CC_LOCATION_INTERNATIONAL                           =  7,               /*      0 1 1 1 international network*/
    NAS_CC_LOCATION_NETWORK                                 = 10                /*      1 0 1 0 network              */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_LOCATION_ENUM_U8;

enum NAS_CC_CAUSE_VALUE_ENUM                                                    /* Cause value (octet 4)             */
{
    NAS_CC_CAUSE_1                                          =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 1,              /*   1. Unassigned (unallocated) number            */
    NAS_CC_CAUSE_3                                          =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 3,              /*   3. No route to destination                    */
    NAS_CC_CAUSE_6                                          =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 6,              /*   6. Channel unacceptable                       */
    NAS_CC_CAUSE_8                                          =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 8,              /*   8. Operator determined barring                */
    NAS_CC_CAUSE_16                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 16,              /*  16. Normal call clearing                       */
    NAS_CC_CAUSE_17                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 17,              /*  17. User busy                                  */
    NAS_CC_CAUSE_18                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 18,              /*  18. No user responding                         */
    NAS_CC_CAUSE_19                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 19,              /*  19. User alerting, no answer                   */
    NAS_CC_CAUSE_21                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 21,              /*  21. Call rejected                              */
    NAS_CC_CAUSE_22                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 22,              /*  22. Number changed                             */
    NAS_CC_CAUSE_24                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 24,
    NAS_CC_CAUSE_25                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 25,              /*  25. Pre-emption                                */
    NAS_CC_CAUSE_26                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 26,              /*  26. Non selected user clearing                 */
    NAS_CC_CAUSE_27                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 27,              /*  27. Destination out of order                   */
    NAS_CC_CAUSE_28                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 28,              /*  28. Invalid number format                      */
    NAS_CC_CAUSE_29                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 29,              /*  29. Facility rejected                          */
    NAS_CC_CAUSE_30                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 30,              /*  30. Response to STATUS ENQUIRY                 */
    NAS_CC_CAUSE_31                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 31,              /*  31. Normal, unspecified                        */
    NAS_CC_CAUSE_34                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 34,              /*  34. No circuit/channel available               */
    NAS_CC_CAUSE_38                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 38,              /*  38. Network out of order                       */
    NAS_CC_CAUSE_41                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 41,              /*  41. Temporary failure                          */
    NAS_CC_CAUSE_42                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 42,              /*  42. Switching equipment congestion             */
    NAS_CC_CAUSE_43                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 43,              /*  43. Access information discarded               */
    NAS_CC_CAUSE_44                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 44,              /*  44. requested circuit/channel not available    */
    NAS_CC_CAUSE_47                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 47,              /*  47. Resources unavailable, unspecified         */
    NAS_CC_CAUSE_49                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 49,              /*  49. Quality of service unavailable             */
    NAS_CC_CAUSE_50                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 50,              /*  50. Requested facility not subscribed          */
    NAS_CC_CAUSE_55                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 55,              /*  55. Incoming calls barred within the CUG       */
    NAS_CC_CAUSE_57                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 57,              /*  57. Bearer capability not authorized           */
    NAS_CC_CAUSE_58                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 58,              /*  58. Bearer capability not presently available  */
    NAS_CC_CAUSE_63                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 63,              /*  63. Service or option not available, unspec    */
    NAS_CC_CAUSE_65                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 65,              /*  65. Bearer service not implemented             */
    NAS_CC_CAUSE_68                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 68,              /*  68. ACM equal to or greater than ACMmax        */
    NAS_CC_CAUSE_69                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 69,              /*  69. Requested facility not implemented         */
    NAS_CC_CAUSE_70                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 70,              /*  70. Only restricted digital info BC available  */
    NAS_CC_CAUSE_79                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 79,              /*  79. Service or option not implemented, unspec  */
    NAS_CC_CAUSE_81                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 81,              /*  81. Invalid transaction identifier value       */
    NAS_CC_CAUSE_87                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 87,              /*  87. User not member of CUG                     */
    NAS_CC_CAUSE_88                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 88,              /*  88. Incompatible destination Incompatible para */
    NAS_CC_CAUSE_91                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 91,              /*  91. Invalid transit network selection          */
    NAS_CC_CAUSE_95                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 95,              /*  95. Semantically incorrect message             */
    NAS_CC_CAUSE_96                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 96,              /*  96. Invalid mandatory information              */
    NAS_CC_CAUSE_97                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 97,              /*  97. Msg type non-existent or not implemented   */
    NAS_CC_CAUSE_98                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 98,              /*  98. Msg type not compatible with protocol state*/
    NAS_CC_CAUSE_99                                         =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 99,              /*  99. IE non-existent or not implemented         */
    NAS_CC_CAUSE_100                                        =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 100,              /* 100. Conditional IE error                       */
    NAS_CC_CAUSE_101                                        =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 101,              /* 101. Message not compatible with protocol state */
    NAS_CC_CAUSE_102                                        =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 102,              /* 102. Recovery on timer expiry Timer number      */
    NAS_CC_CAUSE_111                                        =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 111,              /* 111. Protocol error, unspecified                */
    NAS_CC_CAUSE_127                                        =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 127,              /* 127. Interworking, unspecified                  */
    NAS_CC_CAUSE_128                                        =  NAS_CC_CAUSE_NW_SECTION_BEGIN + 128,              /* 128. DTMF buffer is full                  */

    /* cm service rej */
    NAS_CC_CAUSE_CM_SRV_REJ_IMSI_UNKNOWN_IN_HLR                                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 2,
    NAS_CC_CAUSE_CM_SRV_REJ_ILLEGAL_MS                                          = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 3,
    NAS_CC_CAUSE_CM_SRV_REJ_IMSI_UNKNOWN_IN_VLR                                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 4,
    NAS_CC_CAUSE_CM_SRV_REJ_IMEI_NOT_ACCEPTED                                   = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 5,
    NAS_CC_CAUSE_CM_SRV_REJ_ILLEGAL_ME                                          = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 6,
    NAS_CC_CAUSE_CM_SRV_REJ_PLMN_NOT_ALLOWED                                    = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 11,
    NAS_CC_CAUSE_CM_SRV_REJ_LOCATION_AREA_NOT_ALLOWED                           = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 12,
    NAS_CC_CAUSE_CM_SRV_REJ_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA           = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 13,
    NAS_CC_CAUSE_CM_SRV_REJ_NO_SUITABLE_CELLS_IN_LOCATION_AREA                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 15,
    NAS_CC_CAUSE_CM_SRV_REJ_NETWORK_FAILURE                                     = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 17,
    NAS_CC_CAUSE_CM_SRV_REJ_MAC_FAILURE                                         = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 20,
    NAS_CC_CAUSE_CM_SRV_REJ_SYNCH_FAILURE                                       = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 21,
    NAS_CC_CAUSE_CM_SRV_REJ_CONGESTION                                          = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 22,
    NAS_CC_CAUSE_CM_SRV_REJ_GSM_AUTHENTICATION_UNACCEPTABLE                     = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 23,
    NAS_CC_CAUSE_CM_SRV_REJ_NOT_AUTHORIZED_FOR_THIS_CSG                         = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 25,
    NAS_CC_CAUSE_CM_SRV_REJ_SERVICE_OPTION_NOT_SUPPORTED                        = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 32,
    NAS_CC_CAUSE_CM_SRV_REJ_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED             = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 33,
    NAS_CC_CAUSE_CM_SRV_REJ_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER             = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 34,
    NAS_CC_CAUSE_CM_SRV_REJ_CALL_CANNOT_BE_IDENTIFIED                           = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 38,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_0                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 48,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_1                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 49,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_2                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 50,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_3                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 51,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_4                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 52,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_5                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 53,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_6                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 54,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_7                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 55,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_8                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 56,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_9                  = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 57,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_10                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 58,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_11                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 59,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_12                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 60,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_13                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 61,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_14                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 62,
    NAS_CC_CAUSE_CM_SRV_REJ_RETRY_UPON_ENTRY_INTO_A_NEW_CELL_15                 = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 63,
    NAS_CC_CAUSE_CM_SRV_REJ_SEMANTICALLY_INCORRECT_MESSAGE                      = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 95,
    NAS_CC_CAUSE_CM_SRV_REJ_INVALID_MANDATORY_INFORMATION                       = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 96,
    NAS_CC_CAUSE_CM_SRV_REJ_MESSAGE_TYPE_NONEXISTENT_OR_NOT_IMPLEMENTED         = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 97,
    NAS_CC_CAUSE_CM_SRV_REJ_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCAL_STATE = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 98,
    NAS_CC_CAUSE_CM_SRV_REJ_INFOMATION_ELEMENT_NONEXISTENT_OR_NOT_IMPLEMENTED   = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 99,
    NAS_CC_CAUSE_CM_SRV_REJ_CONDITIONAL_IE_ERROR                                = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 100,
    NAS_CC_CAUSE_CM_SRV_REJ_MESSAGE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE      = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 101,
    NAS_CC_CAUSE_CM_SRV_REJ_PROTOCOL_ERROR_UNSPECIFIED                          = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 111,

    NAS_CC_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246                               = NAS_CC_CAUSE_CM_SRV_REJ_BEGIN + 127,


    /* CSFB service rej */
    NAS_CC_CAUSE_CSFB_SRV_REJ_ILLEGAL_UE                                        = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 3,
    NAS_CC_CAUSE_CSFB_SRV_REJ_ILLEGAL_ME                                        = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 6,
    NAS_CC_CAUSE_CSFB_SRV_REJ_EPS_SERVICES_NOT_ALLOWED                          = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 7,
    NAS_CC_CAUSE_CSFB_SRV_REJ_EPS_SERVICES_AND_NONEPS_SERVICES_NOT_ALLOWED      = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 8,
    NAS_CC_CAUSE_CSFB_SRV_REJ_UE_IDENTITY_CANNOT_BE_DERIVED_BY_NW               = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 9,
    NAS_CC_CAUSE_CSFB_SRV_REJ_IMPLICITLY_DETACHED                               = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 10,
    NAS_CC_CAUSE_CSFB_SRV_REJ_PLMN_NOT_ALLOWED                                  = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 11,
    NAS_CC_CAUSE_CSFB_SRV_REJ_TRACKING_AREA_NOT_ALLOWED                         = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 12,
    NAS_CC_CAUSE_CSFB_SRV_REJ_ROAMING_NOT_ALLOWED_IN_THIS_TA                    = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 13,
    NAS_CC_CAUSE_CSFB_SRV_REJ_NO_SUITABLE_CELLS_IN_TRACKING_AREA                = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 15,
    NAS_CC_CAUSE_CSFB_SRV_REJ_CS_DOMAIN_NOT_AVAILABLE                           = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 18,
    NAS_CC_CAUSE_CSFB_SRV_REJ_CONGESTION                                        = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 22,
    NAS_CC_CAUSE_CSFB_SRV_REJ_NOT_AUTHORIZED_FOR_THIS_CSG                       = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 25,
    NAS_CC_CAUSE_CSFB_SRV_REJ_REQ_SER_OPTION_NOT_AUTHORIZED_IN_PLMN             = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 35,
    NAS_CC_CAUSE_CSFB_SRV_REJ_CS_SERVICE_TEMPORARILY_NOT_AVAILABLE              = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 39,
    NAS_CC_CAUSE_CSFB_SRV_REJ_NO_EPS_BEARER_CONTEXT_ACTIVATED                   = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 40,
    NAS_CC_CAUSE_CSFB_SRV_REJ_SEVERE_NETWORK_FAILURE                            = NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN + 42,


    /* AS rr connection fail */
    NAS_CC_CAUSE_RR_CONN_FAIL_CONGESTION                              = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 1,
    NAS_CC_CAUSE_RR_CONN_FAIL_UNSPECIFIED                             = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 2,
    NAS_CC_CAUSE_RR_CONN_FAIL_ACCESS_BAR                              = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 3,
    NAS_CC_CAUSE_RR_CONN_FAIL_EST_CONN_FAIL                           = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 4,
    NAS_CC_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT                 = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 5,
    NAS_CC_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_REJECT                    = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 6,
    NAS_CC_CAUSE_RR_CONN_FAIL_T3122_RUNING                            = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 7,
    NAS_CC_CAUSE_RR_CONN_FAIL_NO_RF                                   = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 8,
    NAS_CC_CAUSE_RR_CONN_FAIL_LOW_LEVEL_SEARCHING_NETWORK             = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 9,
    NAS_CC_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_SEND_FAIL                 = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 10,
    NAS_CC_CAUSE_RR_CONN_FAIL_NO_VALID_INFO                           = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 11,
    NAS_CC_CAUSE_RR_CONN_FAIL_UE_NOT_ALLOW                            = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 12,
    NAS_CC_CAUSE_RR_CONN_FAIL_TIME_OUT                                = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 13,
    NAS_CC_CAUSE_RR_CONN_FAIL_NO_RANDOM_ACCESS_RESOURCE               = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 14,
    NAS_CC_CAUSE_RR_CONN_FAIL_INVALID_IMMEDIATE_ASSIGNED_MSG          = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 15,
    NAS_CC_CAUSE_RR_CONN_FAIL_ACTIVE_PHYSICAL_CHANNEL_FAIL            = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 16,
    NAS_CC_CAUSE_RR_CONN_FAIL_AIR_MSG_DECODE_ERROR                    = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 17,
    NAS_CC_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT            = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 18,
    NAS_CC_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                        = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 19,
    NAS_CC_CAUSE_RR_CONN_FAIL_CELL_BARRED                             = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 20,
    NAS_CC_CAUSE_RR_CONN_FAIL_FAST_RETURN_TO_LTE                      = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 21,
    NAS_CC_CAUSE_RR_CONN_FAIL_RA_FAIL_NO_VALID_INFO                   = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 22,
    NAS_CC_CAUSE_RR_CONN_FAIL_RJ_INTER_RAT                            = NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN + 23,


    /* AS Rel ind */
    NAS_CC_CAUSE_RR_REL_AUTH_REJ                                      = NAS_CC_CAUSE_RR_REL_BEGIN + 0,
    NAS_CC_CAUSE_RR_REL_NORMAL_EVENT                                  = NAS_CC_CAUSE_RR_REL_BEGIN + 1,
    NAS_CC_CAUSE_RR_REL_NORMAL_UNSPECIFIED                            = NAS_CC_CAUSE_RR_REL_BEGIN + 2,
    NAS_CC_CAUSE_RR_REL_PREEMPTIVE_RELEASE                            = NAS_CC_CAUSE_RR_REL_BEGIN + 3,
    NAS_CC_CAUSE_RR_REL_CONGESTION                                    = NAS_CC_CAUSE_RR_REL_BEGIN + 4,
    NAS_CC_CAUSE_RR_REL_REEST_REJ                                     = NAS_CC_CAUSE_RR_REL_BEGIN + 5,
    NAS_CC_CAUSE_RR_REL_DIRECTED_SIGNAL_CONN_REEST                    = NAS_CC_CAUSE_RR_REL_BEGIN + 6,
    NAS_CC_CAUSE_RR_REL_USER_INACTIVE                                 = NAS_CC_CAUSE_RR_REL_BEGIN + 7,
    NAS_CC_CAUSE_RR_REL_UTRAN_RELEASE                                 = NAS_CC_CAUSE_RR_REL_BEGIN + 8,
    NAS_CC_CAUSE_RR_REL_RRC_ERROR                                     = NAS_CC_CAUSE_RR_REL_BEGIN + 9,
    NAS_CC_CAUSE_RR_REL_RL_FAILURE                                    = NAS_CC_CAUSE_RR_REL_BEGIN + 10,
    NAS_CC_CAUSE_RR_REL_OTHER_REASON                                  = NAS_CC_CAUSE_RR_REL_BEGIN + 11,
    NAS_CC_CAUSE_RR_REL_NO_RF                                         = NAS_CC_CAUSE_RR_REL_BEGIN + 12,
    NAS_CC_CAUSE_RR_REL_RLC_ERR_OR                                    = NAS_CC_CAUSE_RR_REL_BEGIN + 13,
    NAS_CC_CAUSE_RR_REL_CELL_UP_DATE_FAIL                             = NAS_CC_CAUSE_RR_REL_BEGIN + 14,
    NAS_CC_CAUSE_RR_REL_NAS_REL_REQ                                   = NAS_CC_CAUSE_RR_REL_BEGIN + 15,
    NAS_CC_CAUSE_RR_REL_CONN_FAIL                                     = NAS_CC_CAUSE_RR_REL_BEGIN + 16,     /* redial */
    NAS_CC_CAUSE_RR_REL_NAS_DATA_ABSENT                               = NAS_CC_CAUSE_RR_REL_BEGIN + 17,     /* redial */
    NAS_CC_CAUSE_RR_REL_T314_EXPIRED                                  = NAS_CC_CAUSE_RR_REL_BEGIN + 18,
    NAS_CC_CAUSE_RR_REL_W_RL_FAIL                                     = NAS_CC_CAUSE_RR_REL_BEGIN + 19,

    NAS_CC_CAUSE_RR_REL_G_RL_FAIL                                     = NAS_CC_CAUSE_RR_REL_BEGIN + 20,


    /* CSFB LMM Error */
    NAS_CC_CAUSE_CSFB_LMM_FAIL_LMM_LOCAL_FAIL                         = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 0,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_AUTH_REJ                               = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 1,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_T3417_TIME_OUT                         = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 2,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_APP_DETACH_SERVICE                     = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 3,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_CN_DETACH_SERVICE                      = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 4,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_FOR_OTHERS                             = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 5,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_FOR_EMM_STATE                          = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 6,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_SMS_ONLY                               = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 7,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_PS_ONLY                                = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 8,
    NAS_CC_CAUSE_CSFB_LMM_FAIL_TAU_COLL_ABNORMAL                      = NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN + 9,


    /* MM Inter Error */
    NAS_CC_CAUSE_MM_INTER_ERR_FORB_LA                                 = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 0,
    NAS_CC_CAUSE_MM_INTER_ERR_FORB_OTHER                              = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 1,
    NAS_CC_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR                           = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 2,
    NAS_CC_CAUSE_MM_INTER_ERR_CS_DETACH                               = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 3,
    NAS_CC_CAUSE_MM_INTER_ERR_CS_SIM_INVALID                          = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 4,
    NAS_CC_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION                   = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 5,
    NAS_CC_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT                         = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 6,
    NAS_CC_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK                       = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 7,
    NAS_CC_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE                 = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 8,
    NAS_CC_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY        = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 9,
    NAS_CC_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE                         = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 10,
    NAS_CC_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE                    = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 11,
    NAS_CC_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS                     = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 12,
    NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL                       = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 13,
    NAS_CC_CAUSE_MM_INTER_ERR_TI_INVALID                              = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 14,
    NAS_CC_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT                   = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 15,   /* redial */
    NAS_CC_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST                       = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 16,
    NAS_CC_CAUSE_MM_INTER_ERR_UE_INVALID_STATE                        = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 17,
    NAS_CC_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT                  = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 18,
    NAS_CC_CAUSE_MM_INTER_ERR_BACK_TO_LTE                             = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 19,
    NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_EHRPD                         = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 20,
    NAS_CC_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL                          = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 21,   /* 短信业务SAPI3发送失败,不重拨 */
    NAS_CC_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL                          = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 22,   /* 短信业务SAPI3建立时GAS回复失败,重拨 */
    NAS_CC_CAUSE_MM_INTER_ERR_ECALL_INACTIVE                          = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 23,   /* eCall Inactive状态,不重拨 */
    NAS_CC_CAUSE_MM_INTER_ERR_REEST_FAIL                              = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 24,   /* MM reest状态收到est_cnf(失败)或rel ind,不重拨 */
    NAS_CC_CAUSE_MM_INTER_ERR_CC_REL_REQ                              = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 25,
    NAS_CC_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE                     = NAS_CC_CAUSE_MM_INTER_ERR_BEGIN + 26,


    /* CC Inter Error */
    NAS_CC_CAUSE_CC_INTER_ERR_T303_TIME_OUT                           = NAS_CC_CAUSE_CC_INTER_ERR_BEGIN + 0,
    NAS_CC_CAUSE_CC_INTER_ERR_T335_TIME_OUT                           = NAS_CC_CAUSE_CC_INTER_ERR_BEGIN + 1,
    NAS_CC_CAUSE_CC_INTER_ERR_WAIT_RAB_TIME_OUT                       = NAS_CC_CAUSE_CC_INTER_ERR_BEGIN + 2,
    NAS_CC_CAUSE_CC_INTER_ERR_NO_TCH                                  = NAS_CC_CAUSE_CC_INTER_ERR_BEGIN + 3,
    NAS_CC_CAUSE_CC_INTER_ERR_HOLD_REJ_IN_DISC_STATE                  = NAS_CC_CAUSE_CC_INTER_ERR_BEGIN + 4,

    NAS_CC_CAUSE_BUTT                                                 = 0xFFFFFFFF
};
typedef VOS_UINT32   NAS_CC_CAUSE_VALUE_ENUM_U32;


/* [10.5.4.11a] CLIR suppression */
/*============================================================================*/


/* [10.5.4.11b] CLIR invocation */
/*============================================================================*/


/* [10.5.4.12] Congestion level */
/*============================================================================*/
enum NAS_CC_CONGESTION_LEVEL_ENUM                                               /* Congestion level (octet 1)        */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_RECEIVER_READY                                   =  0,               /*      0 0 0 0 receiver ready       */
    NAS_CC_RECEIVER_NOT_READY                               = 15                /*      1 1 1 1 receiver not ready   */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_CONGESTION_LEVEL_ENUM_U8;

/* [10.5.4.13] Connected number */
/*============================================================================*/


/* [10.5.4.14] Connected subaddress */
/*============================================================================*/


/* [10.5.4.15] Facility */
/*============================================================================*/
/* 10.5.101/3GPP TS 24.008. */


/* [10.5.4.16] High layer compatibility */
/*============================================================================*/
/* ITU Recommendation Q.931 */


/* [10.5.4.16.1] Static conditions for the HL compatibility IE contents */
/*============================================================================*/
/* Either the value part of the IE is empty,
   or it contains at least octet 3 and 4. */


/* [10.5.4.17] Keypad facility */
/*============================================================================*/


/* [10.5.4.18] Low layer compatibility */
/*============================================================================*/

/* [10.5.4.19] More data */
/*============================================================================*/


/* [10.5.4.20] Notification indicator */
/*============================================================================*/
enum NAS_CC_NOTIFICATION_DESCRIPTION_ENUM                                       /* Notification description (octet 2)*/
{                                                                               /* Bits 7 6 5 4 3 2 1                */
    NAS_CC_USER_SUSPENDED                                   = 0,                /*      0 0 0 0 0 0 0 User suspended */
    NAS_CC_USER_RESUMED                                     = 1,                /*      0 0 0 0 0 0 1 User resumed   */
    NAS_CC_BEARER_CHANGE                                    = 2                 /*      0 0 0 0 0 1 0 Bearer change  */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8  NAS_CC_NOTIFICATION_DESCRIPTION_ENUM_U8;


/* [10.5.4.21] Progress indicator */
/*============================================================================*/
/* Table 10.5.127/3GPP TS 24.008: Progress indicator information element      */
/* [Defined] Coding standard (octet 3) */
/* [Defined] Location (octet 3) */
enum NAS_CC_PROGRESS_DESCRIPTION_ENUM                                           /* Progress description (octet 4)    */
{                                                                               /* No.                               */
    NAS_CC_PROGRESS_NOT_END_TO_END                          =  1,               /*  1. Call is not end-to-end        */
    NAS_CC_PROGRESS_DEST_IN_NON                             =  2,               /*  2. Dest address in non-PLMN/ISDN */
    NAS_CC_PROGRESS_ORIG_IN_NON                             =  3,               /*  3. Orig address in non-PLMN/ISDN */
    NAS_CC_PROGRESS_CALL_RET                                =  4,               /*  4. Call has returned             */
    NAS_CC_PROGRESS_IN_BAND                                 =  8,               /*  8. In-band information           */
    NAS_CC_PROGRESS_END_TO_END                              = 32,               /* 32. Call is end-to-end PLMN/ISDN  */
    NAS_CC_PROGRESS_QUEUEING                                = 64                /* 64. Queueing                      */
};                                                                              /* All other values Unspecific       */
typedef VOS_UINT8   NAS_CC_PROGRESS_DESCRIPTION_ENUM_U8;


/* [10.5.4.21a] Recall type $(CCBS)$ */
/*============================================================================*/
/* Table 10.5.128/3GPP TS 24.008: Recall type information element */
enum NAS_CC_RECALL_TYPE_ENUM                                                    /* recall type (octet 2)             */
{                                                                               /* Bits 3 2 1                        */
   NAS_CC_RECALL_TYPE_CCBS                                  = 0,                /*      0 0 0 - CCBS                 */
   NAS_CC_RECALL_TYPE_RESERVED                              = 7                 /*      1 1 1 - reserved             */
};
typedef VOS_UINT8   NAS_CC_RECALL_TYPE_ENUM_U8;


/* [10.5.4.21b] Redirecting party BCD number */
/*============================================================================*/


/* [10.5.4.21c] Redirecting party subaddress */
/*============================================================================*/


/* [10.5.4.22] Repeat indicator */
/*============================================================================*/
/* Table 10.5.129/3GPP TS 24.008: Repeat indicator information element */
enum NAS_CC_REPEAT_INDICATION_ENUM                                              /* Repeat indication (octet 1)       */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_REPEAT_MODE1_MODE2                               = 1,                /*      0 0 0 1 "mode 1 / mode 2"    */
    NAS_CC_REPEAT_FALLBACK                                  = 2,                /*      0 0 1 0 Support of fallback  */
    NAS_CC_REPEAT_RESERVED                                  = 3,                /*      0 0 1 1 reserved             */
    NAS_CC_REPEAT_CHANGE_FALLBACK                           = 4                 /*      0 1 0 0 change and fallback  */
};                                                                              /* All other values are reserved.    */
typedef VOS_UINT8   NAS_CC_REPEAT_INDICATION_ENUM_U8;


/* [10.5.4.22a] Reverse call setup direction */
/*============================================================================*/


/* [10.5.4.22b] SETUP Container $(CCBS)$ */
/*============================================================================*/


/* [10.5.4.23] Signal */
/*============================================================================*/
/* Table 10.5.130/3GPP TS 24.008: Signal information element */
enum NAS_CC_SIGNAL_VALUE_ENUM                                                   /* Signal value (octet 2)          */
{                                                                               /* Bits 8 7 6 5 4 3 2 1            */
    NAS_CC_DIAL_TONE_ON                                     =  0,               /*  0. dial tone on                */
    NAS_CC_RING_BACK_TONE_ON                                =  1,               /*  1. ring back tone on           */
    NAS_CC_INTERCEPT_TONE_ON                                =  2,               /*  2. intercept tone on           */
    NAS_CC_NETWORK_CONGESTION_TONE_ON                       =  3,               /*  3. network congestion tone on  */
    NAS_CC_BUSY_TONE_ON                                     =  4,               /*  4. busy tone on                */
    NAS_CC_CONFIRM_TONE_ON                                  =  5,               /*  5. confirm tone on             */
    NAS_CC_ANSWER_TONE_ON                                   =  6,               /*  6. answer tone on              */
    NAS_CC_CALL_WAITING_TONE_ON                             =  7,               /*  7. call waiting tone on        */
    NAS_CC_OFF_HOOK_WARNING_TONE_ON                         =  8,               /*  8. off-hook warning tone on    */
    NAS_CC_TONES_OFF                                        = 63,               /* 63. tones off                   */
    NAS_CC_ALERTING_OFF                                     = 79                /* 79. alerting off                */
};                                                                              /* All other values are reserved.  */
typedef VOS_UINT8   NAS_CC_SIGNAL_VALUE_ENUM_U8;


/* [10.5.4.24] SS Version Indicator */
/*============================================================================*/
/* The usage of the SS version information field is defined in 3GPP TS 24.080 */


/* [10.5.4.25] User-user */
/*============================================================================*/


/* [10.5.4.26] Alerting Pattern $(NIA)$ */
/*============================================================================*/
/* Table 10.5.132/3GPP TS 24.008: Alerting Pattern information element */
enum NAS_CC_ALERTING_PATTERN_ENUM                                               /* Alerting Pattern value (octet 3)  */
{                                                                               /* Bits 4 3 2 1                      */
    NAS_CC_ALERTING_PATTERN_1                               = 0,                /*      0 0 0 0 alerting pattern 1   */
    NAS_CC_ALERTING_PATTERN_2                               = 1,                /*      0 0 0 1 alerting pattern 2   */
    NAS_CC_ALERTING_PATTERN_3                               = 2,                /*      0 0 1 0 alerting pattern 3   */
    NAS_CC_ALERTING_PATTERN_5                               = 4,                /*      0 1 0 0 alerting pattern 5   */
    NAS_CC_ALERTING_PATTERN_6                               = 5,                /*      0 1 0 1 alerting pattern 6   */
    NAS_CC_ALERTING_PATTERN_7                               = 6,                /*      0 1 1 0 alerting pattern 7   */
    NAS_CC_ALERTING_PATTERN_8                               = 7,                /*      0 1 1 1 alerting pattern 8   */
    NAS_CC_ALERTING_PATTERN_9                               = 8                 /*      1 0 0 0 alerting pattern 9   */
};                                                                              /* all other values are reserved     */
typedef VOS_UINT8   NAS_CC_ALERTING_PATTERN_ENUM_U8;


/* [10.5.4.27] Allowed actions $(CCBS)$ */
/*============================================================================*/
/* Table 10.5.133/3GPP TS 24.008: Allowed actions information element         */
enum NAS_CC_CCBS_ACTIVATION_ENUM                                                /* CCBS activation (octet 3)         */
{                                                                               /* Bits 8                            */
    NAS_CCBS_ACTIVATION_NOT_POSSIBLE                        = 0,                /*      0 not possible               */
    NAS_CCBS_ACTIVATION_POSSIBLE                            = 1                 /*      1 possible                   */
};
typedef VOS_UINT8   NAS_CC_CCBS_ACTIVATION_ENUM_U8;


/* 10.5.4.28 Stream Identifier */
/*============================================================================*/
/* Table 10.5.134/3GPP TS 24.008: Stream Identifier information element       */


/* 10.5.4.29 Network Call Control Capabilities */
/*============================================================================*/
/* Table 10.5.135/3GPP TS 24.008: Network Call Control Capabilities */
enum NAS_CC_MCS_ENUM                                                            /* MCS (octet 3)                     */
{                                                                               /* Bit 1                             */
    NAS_CC_MCS_NOT_SUPPORT                                 = 0,                 /*     0 not support the multicall   */
    NAS_CC_MCS_SUPPORT                                     = 1                  /*     1 supports the multicall      */
};
typedef VOS_UINT8   NAS_CC_MCS_ENUM_U8;


/* [10.5.4.30] Cause of No CLI */
/*============================================================================*/
/* Table 10.5.135a/3GPP TS 24.008: Cause of No CLI information element */
enum NAS_CC_CAUSE_OF_NO_CLI_ENUM                                                /* Cause of No CLI (octet 3)         */
{                                                                               /* Bits 8 7 6 5 4 3 2 1              */
    NAS_CC_NO_CLI_UNAVAILABLE                               = 0,                /*      0 0 0 0 0 0 0 0 Unavailable  */
    NAS_CC_NO_CLI_REJECT                                    = 1,                /*      0 0 0 0 0 0 0 1 Reject       */
    NAS_CC_NO_CLI_INTERACTION                               = 2,                /*      0 0 0 0 0 0 1 0 Interaction  */
    NAS_CC_NO_CLI_COIN_LINE                                 = 3                 /*      0 0 0 0 0 0 1 1 Coin line    */
};                                                                              /* Other values as "Unavailable".    */
typedef VOS_UINT8   NAS_CC_CAUSE_OF_NO_CLI_ENUM_U8;


/* [10.5.4.31] Void */
/*============================================================================*/


/* [10.5.4.32] Supported codec list */
/*============================================================================*/


/* [10.5.4.33] Service category */
/*============================================================================*/
/* Table 10.5.135d/3GPP TS 24.008: Service Category information element */
enum NAS_CC_EMERGENCY_CAT_ENUM                                                  /* Emergency Service Category Value  */
{
    NAS_CC_EMERGENCY_POLICE                                 =  1,               /* Bit 1 Police                      */
    NAS_CC_EMERGENCY_AMBULANCE                              =  2,               /* Bit 2 Ambulance                   */
    NAS_CC_EMERGENCY_FIRE                                   =  4,               /* Bit 3 Fire Brigade                */
    NAS_CC_EMERGENCY_MARINE                                 =  8,               /* Bit 4 Marine Guard                */
    NAS_CC_EMERGENCY_MOUNTAIN                               = 16,               /* Bit 5 Mountain Rescue             */
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-16, begin */
    NAS_CC_EMERGENCY_MIEC                                   = 0x20,             /* Bit 6 manually initiated eCall    */
    NAS_CC_EMERGENCY_AIEC                                   = 0x40              /* Bit 7 auto initiated eCall        */
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-16, end */
};
typedef VOS_UINT8  NAS_CC_EMERGENCY_CAT_ENUM_U8;


/* [10.5.4.34] Redial */
/*============================================================================*/


/* [10.5.4.35] Network-initiated Service Upgrade indicator */
/*============================================================================*/







/******************************************************************************/
/* IE Sturct Definition                                                       */
/******************************************************************************/


/* [10.5.4.1] Extensions of codesets */
/*============================================================================*/


/* [10.5.4.2] Locking shift procedure */
/*============================================================================*/
/* Figure 10.5.85/3GPP TS 24.008 Locking shift element */
/*      8       7       6       5       4       3       2       1
    ┌───┬───────────┬───┬───────────┐
    │  1   │  0       0       1   │  0   │      New codeset     │
    │      │  (Shift identifier)  │      │    identification    │Octet 1
    └───┴───────────┴───┴───────────┘
                                        |
                                "0" in this position indicates locking shift
*/


/* [10.5.4.3] Non-locking shift procedure */
/*============================================================================*/
/* Figure 10.5.86/3GPP TS 24.008 non-Locking shift element */
/*      8       7       6       5       4       3       2       1
    ┌───┬───────────┬───┬───────────┐
    │  1   │  0       0       1   │  1   │   Temporary codeset  │
    │      │  (Shift identifier)  │      │    identification    │Octet 1
    └───┴───────────┴───┴───────────┘
                                        |
                            "1" in this position indicates non-locking shift
*/


/* [10.5.4.4] Auxiliary states */
/*============================================================================*/
/* Figure 10.5.87/3GPP TS 24.008 Auxiliary states information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                  Auxiliary state IEI                 │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │              Length of auxiliary states contents             │Octet 2
    ├───┬───────────┬───────┬───────┤
    │  1   │  0       0       0   │   hold aux.  │   MPTY aux.  │
    │ ext  │        spare         │    state     │    state     │Octet 3
    └───┴───────────┴───────┴───────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_MPTY_AUX_STATE_ENUM_U8       MptyAuxState        : 2;
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       HoldAuxState        : 2;
    VOS_UINT8                           Spare               : 3;
    VOS_UINT8                           Ext                 : 1;
}NAS_CC_IE_AUX_STATE_STRU;


/* [10.5.4.4a] Backup bearer capability */
/*============================================================================*/
/* Figure 10.5.87a/3GPP TS 24.008 Backup bearer capability information element*/
/*
       8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │              Backup bearer capability IEI            │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │         Length of the backup bearer capability contents      │Octet 2
    ├───┬───────┬───┬───┬───────────┤
    │  1   │radio channel │coding│trans.│ information transfer │
    │ ext  │ requirement  │ std. │ mode │      capability      │Octet 3
    ├───┼───┬───┴───┼───┼───┬───┬───┤
    │  1   │ comp │              │ dupl.│confi │ NIRR │esta- │
    │ ext  │-ress.│  Structure   │ mode │ gur. │      │ bli. │Octet 4*
    ├───┼───┴───┬───┴───┼───┴───┴───┤
    │ 0/1  │  0       0   │     rate     │       signaling      │
    │ ext  │  access id.  │   adaption   │    access protocol   │Octet 5*
    ├───┼───────┼───────┼───────────┤
    │  1   │   Other IT   │  Other rate  │  0       0       0   │
    │ ext  │      C       │   adaption   │        Spare         │Octet 5a*
    ├───┼───────┼───────┴───────┬───┤
    │ 0/1  │  0       1   │       User information       │sync/ │
    │ ext  │ layer 1 id.  │       layer 1 protocol       │ async│Octet 6*
    ├───┼───┬───┼───┬───────────┴───┤
    │ 0/1  │numb. │nego- │numb. │                              │
    │ ext  │stop  │ tia- │ data │        user rate             │Octet 6a*
    │      │ bit  │ tion │ bits │                              │
    ├───┼───┴───┼───┼───┬───────────┤
    │ 0/1  │   intermed.  │ NIC  │ NIC  │                      │
    │ ext  │     rate     │on TX │on RX │        Parity        │Octet 6b*
    ├───┼───────┼───┴───┴───────────┤
    │ 0/1  │  connection  │                                      │
    │ ext  │   element    │              modem type              │Octet 6c*
    ├───┼───────┼───────────────────┤
    │ 0/1  │     Other    │                                      │
    │ ext  │  modem type  │        Fixed network user rate       │Octet 6d*
    ├───┼───────┴───────┬───────────┤
    │ 0/1  │      Acceptable channel      │   Maximum number of  │
    │ ext  │            codings           │    traffic channels  │Octet 6e*
    ├───┼───────────┬───┴───────────┤
    │ 0/1  │         UIMI         │      Wanted air interface    │
    │ ext  │                      │           user rate          │Octet 6f*
    ├───┼───────────┼───────────────┤
    │  1   │  Acceptable channel  │      Wanted air interface    │
    │ ext  │   codings Extended   │           user rate          │Octet 6g*
    ├───┼───────┬───┴───────────────┤
    │ 0/1  │  1       0   │           User information           │
    │ ext  │ layer 2 id.  │           layer 2 protocol           │Octet 7*
    └───┴───────┴───────────────────┘
*/
typedef struct
{
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    InfoTransCap        :3;
    NAS_CC_TRANSFER_MODE_ENUM_U8        TransferMode        :1;
    NAS_CC_BC_CODING_STANDARD_ENUM_U8   CodingStd           :1;
    NAS_CC_RADIO_CH_REQUIREMENT_ENUM_U8 RadioChReq          :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET3_STRU;

typedef struct
{
    NAS_CC_ESTABLISHMENT_ENUM_U8        Establishment       :1;
    NAS_CC_NIRR_ENUM_U8                 Nirr                :1;
    NAS_CC_CONFIGURATION_ENUM_U8        Configuation        :1;
    NAS_CC_DUPLEX_MODE_ENUM_U8          DuplexMode          :1;
    NAS_CC_STRUCTURE_ENUM_U8            Structure           :2;
    NAS_CC_COMPRESSION_ENUM_U8          Compression         :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET4_STRU;

typedef struct
{
    NAS_CC_SIG_ACCESS_PROTOCOL_ENUM_U8  SigAccProtocol      :3;
    NAS_CC_RATE_ADAPTION_ENUM_U8        RateAdaption        :2;
    NAS_CC_ACCESS_IDENTITY_ENUM_U8      AccessId            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET5_STRU;

typedef struct
{
    VOS_UINT8                           Spare               :3;
    NAS_CC_OTHER_RATE_ADAPTION_ENUM_U8  OtherRA             :2;
    NAS_CC_OTHER_ITC_ENUM_U8            OtherITC            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET5A_STRU;

typedef struct
{
    NAS_CC_SYNC_ASYNC_ENUM_U8           SyncAsync           :1;
    NAS_CC_UIL1P_ENUM_U8                UserInfoL1          :4;
    NAS_CC_L2_IDENTITY_ENUM_U8          Layer1Id            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6_STRU;

typedef struct
{
    NAS_CC_USER_RATE_ENUM_U8            UserRate            :4;
    NAS_CC_NUM_OF_DATA_BITS_ENUM_U8     NumOfDataBits       :1;
    NAS_CC_NEGOTIATION_ENUM_U8          Negotiation         :1;
    NAS_CC_NUM_OF_STOP_BITS_ENUM_U8     NumOfStopBits       :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6A_STRU;

typedef struct
{
    NAS_CC_PARITY_INFO_ENUM_U8          ParityInfo          :3;
    NAS_CC_NIC_ON_RX_ENUM_U8            RxNIC               :1;
    NAS_CC_NIC_ON_TX_ENUM_U8            TxNIC               :1;
    NAS_CC_INTER_RATE_ENUM_U8           InterRate           :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6B_STRU;

typedef struct
{
    NAS_CC_MODEM_TYPE_ENUM_U8           ModemType           :5;
    NAS_CC_CONNECTION_ELEMENT_ENUM_U8   ConnElement         :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6C_STRU;

typedef struct
{
    NAS_CC_FNUR_ENUM_U8                 FNUR                :5;
    NAS_CC_OTHER_MODEM_TYPE_ENUM_U8     OtherModemType      :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6D_STRU;

typedef struct
{
    VOS_UINT8                           Spare               :7;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6E_STRU;

typedef struct
{
    NAS_CC_WAIUR_ENUM_U8                WAIUR               :4;
    NAS_CC_UIMI_ENUM_U8                 UIMI                :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6F_STRU;

typedef struct
{
    VOS_UINT8                           Spare               :7;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET6G_STRU;

typedef struct
{
    NAS_CC_UIL2P_ENUM_U8                UserInfoL2          :5;
    NAS_CC_L2_IDENTITY_ENUM_U8          Layer2Id            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BAK_BC_OCTET7_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_BAK_BC_OCTET3_STRU        Octet3;
    NAS_CC_IE_BAK_BC_OCTET4_STRU        Octet4;
    NAS_CC_IE_BAK_BC_OCTET5_STRU        Octet5;
    NAS_CC_IE_BAK_BC_OCTET5A_STRU       Octet5a;
    NAS_CC_IE_BAK_BC_OCTET6_STRU        Octet6;
    NAS_CC_IE_BAK_BC_OCTET6A_STRU       Octet6a;
    NAS_CC_IE_BAK_BC_OCTET6B_STRU       Octet6b;
    NAS_CC_IE_BAK_BC_OCTET6C_STRU       Octet6c;
    NAS_CC_IE_BAK_BC_OCTET6D_STRU       Octet6d;
    NAS_CC_IE_BAK_BC_OCTET6E_STRU       Octet6e;
    NAS_CC_IE_BAK_BC_OCTET6F_STRU       Octet6f;
    NAS_CC_IE_BAK_BC_OCTET6G_STRU       Octet6g;
    NAS_CC_IE_BAK_BC_OCTET7_STRU        Octet7;
}NAS_CC_IE_BAK_BC_STRU;


/* [10.5.4.4a.1] Static conditions for the backup BC IE contents */
/*============================================================================*/


/* [10.5.4.5] Bearer capability */
/*============================================================================*/
/* Figure 10.5.88/3GPP TS 24.008 Bearer capability information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                 Bearer capability IEI                │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │             Length of the bearer capability contents         │Octet 2
    ├───┬───────┬───┬───┬───────────┤
    │ 0/1  │radio channel │coding│trans.│ information transfer │
    │ ext  │ requirement  │ std. │ mode │      capability      │Octet 3
    ├───┼───┬───┴───┼───┴───────────┤
    │ 0/1  │  0   │ CTM      0   │       speech version         │
    │ ext  │coding│        spare │         indication           │Octet 3a*
    ├───┼───┼───┬───┼───────────────┤
    │ 0/1  │  0   │  0   │  0   │       speech version         │
    │ ext  │coding│spare │spare │         indication           │Octet 3b*
    ├───┼───┼───┼───┼───────────────┤
    │ 0/1  │  0   │  0   │  0   │       speech version         │
    │ ext  │coding│spare │spare │         indication           │Octet 3c*
    ├───┼───┼───┼───┼───────────────┤
    │ 0/1  │  0   │  0   │  0   │       speech version         │
    │ ext  │coding│spare │spare │         indication           │Octet 3d*
    ├───┼───┼───┼───┼───────────────┤
    │  1   │  0   │  0   │  0   │       speech version         │
    │ ext  │coding│spare │spare │         indication           │Octet 3e*
    ├───┼───┼───┴───┼───┬───┬───┬───┤
    │  1   │ comp │              │ dupl.│confi │ NIRR │esta- │
    │ ext  │-ress.│  Structure   │ mode │ gur. │      │ bli. │Octet 4*
    ├───┼───┴───┬───┴───┼───┴───┴───┤
    │ 0/1  │  0       0   │     rate     │       signaling      │
    │ ext  │  access id.  │   adaption   │    access protocol   │Octet 5*
    ├───┼───────┼───────┼───────────┤
    │ 0/1  │   Other IT   │  Other rate  │  0       0       0   │
    │ ext  │      C       │   adaption   │        Spare         │Octet 5a*
    ├───┼───┬───┼───┬───┼───┬───┬───┤
    │  1   │ Hdr/ │Multi │ Mode │ LLI  │Assig │ Inb. │   0  │
    │ ext  │noHdr │frame │      │      │nor/e │ neg  │ Spare│Octet 5b*
    ├───┼───┴───┼───┴───┴───┴───┼───┤
    │ 0/1  │  0       1   │       User information       │sync/ │
    │ ext  │ layer 1 id.  │       layer 1 protocol       │ async│Octet 6*
    ├───┼───┬───┼───┬───────────┴───┤
    │ 0/1  │numb. │nego- │numb. │                              │
    │ ext  │stop  │ tia- │ data │        user rate             │Octet 6a*
    │      │ bit  │ tion │ bits │                              │
    ├───┼───┴───┼───┼───┬───────────┤
    │ 0/1  │   intermed.  │ NIC  │ NIC  │                      │
    │ ext  │     rate     │on TX │on RX │        Parity        │Octet 6b*
    ├───┼───────┼───┴───┴───────────┤
    │ 0/1  │  connection  │                                      │
    │ ext  │   element    │              modem type              │Octet 6c*
    ├───┼───────┼───────────────────┤
    │ 0/1  │     Other    │                                      │
    │ ext  │  modem type  │        Fixed network user rate       │Octet 6d*
    ├───┼───────┴───────┬───────────┤
    │ 0/1  │      Acceptable channel      │   Maximum number of  │
    │ ext  │            codings           │    traffic channels  │Octet 6e*
    ├───┼───────────┬───┴───────────┤
    │ 0/1  │         UIMI         │      Wanted air interface    │
    │ ext  │                      │           user rate          │Octet 6f*
    ├───┼───────────┼───────────────┤
    │  1   │  Acceptable channel  │      Wanted air interface    │
    │ ext  │   codings Extended   │           user rate          │Octet 6g*
    ├───┼───────┬───┴───────────────┤
    │ 0/1  │  1       0   │           User information           │
    │ ext  │ layer 2 id.  │           layer 2 protocol           │Octet 7*
    └───┴───────┴───────────────────┘
*/
typedef struct
{
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    InfoTransCap        :3;
    NAS_CC_TRANSFER_MODE_ENUM_U8        TransferMode        :1;
    NAS_CC_BC_CODING_STANDARD_ENUM_U8   CodingStd           :1;
    NAS_CC_RADIO_CH_REQUIREMENT_ENUM_U8 RadioChReq          :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET3_STRU;

typedef struct
{
    NAS_CC_SPEECH_VER_ENUM_U8           SpeechVer           :4;
    VOS_UINT8                           Spare               :1;
    NAS_CC_CTM_ENUM_U8                  Ctm                 :1;
    NAS_CC_BC_CODING_STANDARD_ENUM_U8   Coding              :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET3A_STRU;

typedef struct
{
    NAS_CC_SPEECH_VER_ENUM_U8           SpeechVer           :4;
    VOS_UINT8                           Spare               :2;
    NAS_CC_BC_CODING_STANDARD_ENUM_U8   Coding              :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET3B_STRU;


 typedef struct
{
    NAS_CC_ESTABLISHMENT_ENUM_U8        Establishment       :1;
    NAS_CC_NIRR_ENUM_U8                 Nirr                :1;
    NAS_CC_CONFIGURATION_ENUM_U8        Configuation        :1;
    NAS_CC_DUPLEX_MODE_ENUM_U8          DuplexMode          :1;
    NAS_CC_STRUCTURE_ENUM_U8            Structure           :2;
    NAS_CC_COMPRESSION_ENUM_U8          Compression         :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET4_STRU;

typedef struct
{

    NAS_CC_SIG_ACCESS_PROTOCOL_ENUM_U8  SigAccProtocol      :3;
    NAS_CC_RATE_ADAPTION_ENUM_U8        RateAdaption        :2;
    NAS_CC_ACCESS_IDENTITY_ENUM_U8      AccessId            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET5_STRU;

typedef struct
{
    VOS_UINT8                           Spare               :3;
    NAS_CC_OTHER_RATE_ADAPTION_ENUM_U8  OtherRA             :2;
    NAS_CC_OTHER_ITC_ENUM_U8            OtherITC            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET5A_STRU;

typedef struct
{
    VOS_UINT8                           Spare               :1;
    NAS_CC_IN_OUT_BAND_NEG_ENUM_U8      InOutBandNeg        :1;
    NAS_CC_ASSIGNOR_ASSIGNEE_ENUM_U8    Assignore           :1;
    NAS_CC_LLI_NEGOTIATION_ENUM_U8      LLI                 :1;
    NAS_CC_OP_MODE_ENUM_U8              OpMode              :1;
    NAS_CC_MULTI_FRAME_EST_ENUM_U8      MultiFrame          :1;
    NAS_CC_RATE_ADAPTION_HEADER_ENUM_U8 Header              :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET5B_STRU;

typedef struct
{
    NAS_CC_SYNC_ASYNC_ENUM_U8           SyncAsync           :1;
    NAS_CC_UIL1P_ENUM_U8                UserInfoL1          :4;
    NAS_CC_L2_IDENTITY_ENUM_U8          Layer1Id            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6_STRU;

typedef struct
{
    NAS_CC_USER_RATE_ENUM_U8            UserRate            :4;
    NAS_CC_NUM_OF_DATA_BITS_ENUM_U8     NumOfDataBits       :1;
    NAS_CC_NEGOTIATION_ENUM_U8          Negotiation         :1;
    NAS_CC_NUM_OF_STOP_BITS_ENUM_U8     NumOfStopBits       :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6A_STRU;

typedef struct
{
    NAS_CC_PARITY_INFO_ENUM_U8          ParityInfo          :3;
    NAS_CC_NIC_ON_RX_ENUM_U8            RxNIC               :1;
    NAS_CC_NIC_ON_TX_ENUM_U8            TxNIC               :1;
    NAS_CC_INTER_RATE_ENUM_U8           InterRate           :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6B_STRU;

typedef struct
{
    NAS_CC_MODEM_TYPE_ENUM_U8           ModemType           :5;
    NAS_CC_CONNECTION_ELEMENT_ENUM_U8   ConnElement         :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6C_STRU;

typedef struct
{
    NAS_CC_FNUR_ENUM_U8                 FNUR                :5;
    NAS_CC_OTHER_MODEM_TYPE_ENUM_U8     OtherModemType      :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6D_STRU;

typedef struct
{
    NAS_CC_MAX_TCH_NUM_ENUM_U8          MaxTchNum           :3;
    NAS_CC_TCH_F4_8_ENUM_U8             TchF48              :1;
    NAS_CC_TCH_F9_6_ENUM_U8             TchF96              :1;
    VOS_UINT8                           Spare               :1;
    NAS_CC_TCH_F14_4_ENUM_U8            TchF144             :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6E_STRU;

typedef struct
{
    NAS_CC_WAIUR_ENUM_U8                WAIUR               :4;
    NAS_CC_UIMI_ENUM_U8                 UIMI                :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6F_STRU;

typedef struct
{
    VOS_UINT8                           Spare               :2;
    NAS_CC_CCAI_ENUM_U8                 CCAI                :2;
    NAS_CC_TCH_F43_2_ENUM_U8            TchF432             :1;
    NAS_CC_TCH_F32_0_ENUM_U8            TchF320             :1;
    NAS_CC_TCH_F28_8_ENUM_U8            TchF288             :1;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET6G_STRU;

typedef struct
{
    NAS_CC_UIL2P_ENUM_U8                UserInfoL2          :5;
    NAS_CC_L2_IDENTITY_ENUM_U8          Layer2Id            :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_BC_OCTET7_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_BC_OCTET3_STRU            Octet3;
    NAS_CC_IE_BC_OCTET3A_STRU           Octet3a;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3b;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3c;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3d;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3e;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3f;
    NAS_CC_IE_BC_OCTET4_STRU            Octet4;
    NAS_CC_IE_BC_OCTET5_STRU            Octet5;
    NAS_CC_IE_BC_OCTET5A_STRU           Octet5a;
    NAS_CC_IE_BC_OCTET5B_STRU           Octet5b;
    NAS_CC_IE_BC_OCTET6_STRU            Octet6;
    NAS_CC_IE_BC_OCTET6A_STRU           Octet6a;
    NAS_CC_IE_BC_OCTET6B_STRU           Octet6b;
    NAS_CC_IE_BC_OCTET6C_STRU           Octet6c;
    NAS_CC_IE_BC_OCTET6D_STRU           Octet6d;
    NAS_CC_IE_BC_OCTET6E_STRU           Octet6e;
    NAS_CC_IE_BC_OCTET6F_STRU           Octet6f;
    NAS_CC_IE_BC_OCTET6G_STRU           Octet6g;
    NAS_CC_IE_BC_OCTET7_STRU            Octet7;

}NAS_CC_IE_BC_STRU;


/* [10.5.4.5.1] Static conditions for the bearer capability IE contents */
/*============================================================================*/


/* [10.5.4.5a] Call Control Capabilities */
/*============================================================================*/
/* Figure 10.5.89/3GPP TS 24.008 Call Control Capabilities information element*/
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │            Call Control Capabilities IEI             │Octet 1
    ├───┴───────────────────────────┤
    │         Length of Call Control Capabilities contents         │Octet 2
    ├───────────────┬───┬───┬───┬───┤
    │ Maximum number of supported  │  0   │ENICM │ PCP  │ DTMF │
    │            bearers           │spare │      │      │      │Octet 3
    ├───────────────┼───┴───┴───┴───┤
    │  0       0       0       0   │       Maximum number of      │
    │            spare             │        speech bearers        │Octet 4
    └───────────────┴───────────────┘
*/
typedef struct
{
    NAS_CC_DTMF_ENUM_U8                 DTMF                :1;
    NAS_CC_PCP_ENUM_U8                  PCP                 :1;
    NAS_CC_ENICM_ENUM_U8                ENICM               :1;
    VOS_UINT8                           Spare               :1;
    NASC_MAX_SUPPORT_BEARERS_ENUM_U8    MaxBearers          :4;
}NAS_CC_IE_CC_CAP_OCTET3_STRU;

typedef struct
{
    NAS_CC_MAX_SPEECH_BEARERS_ENUM_U8   MaxSpeechBearers    :4;
    VOS_UINT8                           Spare               :4;
}NAS_CC_IE_CC_CAP_OCTET4_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CC_CAP_OCTET3_STRU        Octet3;
    NAS_CC_IE_CC_CAP_OCTET4_STRU        Octet4;
}NAS_CC_IE_CC_CAP_STRU;


/* [10.5.4.6] Call state */
/*============================================================================*/
/* Figure 10.5.90/3GPP TS 24.008 Call state information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                      call state IEI                  │Octet 1
    ├───┴───┬───────────────────────┤
    │    coding    │                                              │
    │   standard   │      call state value (coded in binary)      │Octet 2
    └───────┴───────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_CALL_STATE_ENUM_U8           CallState           :6;
    NAS_CC_CODING_STANDARD_ENUM_U8      CodingStd           :2;
}NAS_CC_IE_CALL_STATE_STRU;


/* [10.5.4.7] Called party BCD number */
/*============================================================================*/
/* Figure 10.5.91/3GPP TS 24.008 Called party BCD number information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │             Called party BCD number IEI              │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │           Length of called party BCD number contents         │Octet 2
    ├───┬───────────┬───────────────┤
    │  1   │       type of        │       Numbering plan         │
    │ ext  │        number        │       identification         │Octet 3
    ├───┴───────────┼───────────────┤
    │                              │                              │
    │       Number digit 2         │        Number digit 1        │Octet 4*
    ├───────────────┼───────────────┤
    │                              │                              │
    │       Number digit 4         │        Number digit 3        │Octet 5*
    ├───────────────┼───────────────┤
    │                              │                              │    :
    │                              │                              │    :
    ┊                              ┊                              ┊
    └───────────────┴───────────────┘
*/
typedef struct
{
    NAS_CC_NPI_ENUM_U8                  NPI                 :4;
    NAS_CC_TON_ENUM_U8                  TON                 :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CALLED_NUM_OCTET3_STRU;

#define NAS_CC_MAX_BCD_NUM_LEN          40
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CALLED_NUM_OCTET3_STRU    Octet3;

    VOS_UINT8                           BCDNum[NAS_CC_MAX_BCD_NUM_LEN];
}NAS_CC_IE_CALLED_NUM_STRU;


/* [10.5.4.8] Called party subaddress */
/*============================================================================*/
/* Figure 10.5.92/3GPP TS 24.008 Called party subaddress */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │             Called party Subaddress IEI              │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │           Length of called party Subaddress contents         │Octet 2
    ├───┬───────────┬───┬───────────┤
    │  1   │       type of        │odd/ev│  0       0       0   │
    │ ext  │      Subaddress      │Indica│        spare         │Octet 3
    ├───┴───────────┴───┴───────────┤
    │                                                              │
    │                     Subaddress information                   │Octet 4*
    │                                                              │
    ┊                                                              ┊
    ┊                                                              ┊etc.
    └───────────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           Spare               :3;
    NAS_CC_ODD_EVEN_IND_ENUM_U8         OddEvenInd          :1;
    NAS_CC_TYPE_OF_SUBADDR_ENUM_U8      TypeOfSubaddr       :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CALLED_SUBADDR_OCTET3_STRU;

#define NAS_CC_MAX_SUBADDR_INFO_LEN     20
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CALLED_SUBADDR_OCTET3_STRU Octet3;

    VOS_UINT8                           SubAddrInfo[NAS_CC_MAX_SUBADDR_INFO_LEN];
}NAS_CC_IE_CALLED_SUBADDR_STRU;


/* [10.5.4.9] Calling party BCD number */
/*============================================================================*/
/* Figure 10.5.93/3GPP TS 24.008 Calling party BCD number information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │            Calling party BCD number IEI              │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │           Length of calling party BCD number contents        │Octet 2
    ├───┬───────────┬───────────────┤
    │  1   │       type of        │       Numbering plan         │
    │ ext  │        number        │       identification         │Octet 3
    ├───┴───────────┼───────────────┤
    │                              │                              │
    │       Number digit 2         │        Number digit 1        │Octet 4*
    ├───────────────┼───────────────┤
    │                              │                              │
    │       Number digit 4         │        Number digit 3        │Octet 5*
    ├───────────────┼───────────────┤
    │                              │                              │    :
    │                              │                              │    :
    ┊                              ┊                              ┊
    └───────────────┴───────────────┘
*/
typedef struct
{
    NAS_CC_NPI_ENUM_U8                  NPI                 :4;
    NAS_CC_TON_ENUM_U8                  TON                 :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CALLING_NUM_OCTET3_STRU;

typedef struct
{
    NAS_CC_SCREENING_IND_ENUM_U8        ScreeningIndicator      :2;
    VOS_UINT8                           Spare                   :3;
    NAS_CC_PRESENTATION_IND_ENUM_U8     PresentationIndicator   :2;
    VOS_UINT8                           Ext                     :1;
}NAS_CC_IE_CALLING_NUM_OCTET3A_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CALLING_NUM_OCTET3_STRU   Octet3;
    NAS_CC_IE_CALLING_NUM_OCTET3A_STRU  Octet3a;

    VOS_UINT8                           BCDNum[NAS_CC_MAX_BCD_NUM_LEN];
}NAS_CC_IE_CALLING_NUM_STRU;


/* [10.5.4.10] Calling party subaddress */
/*============================================================================*/
/* Figure 10.5.94/3GPP TS 24.008 Calling party subaddress */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │             Calling party Subaddress IEI             │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │           Length of calling party Subaddress contents        │Octet 2
    ├───┬───────────┬───┬───────────┤
    │  1   │       type of        │odd/ev│  0       0       0   │
    │ ext  │      Subaddress      │Indica│        spare         │Octet 3
    ├───┴───────────┴───┴───────────┤
    │                                                              │
    │                     Subaddress information                   │Octet 4*
    │                                                              │
    ┊                                                              ┊
    ┊                                                              ┊etc.
    └───────────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           Spare               :3;
    NAS_CC_ODD_EVEN_IND_ENUM_U8         OddEvenInd          :1;
    NAS_CC_TYPE_OF_SUBADDR_ENUM_U8      TypeOfSubaddr       :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CALLING_SUBADDR_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CALLING_SUBADDR_OCTET3_STRU Octet3;

    VOS_UINT8                           SubAddrInfo[NAS_CC_MAX_SUBADDR_INFO_LEN];
}NAS_CC_IE_CALLING_SUBADDR_STRU;


/* [10.5.4.11] Cause */
/*============================================================================*/
/* Figure 10.5.95/3GPP TS 24.008 Cause information element */
/*
       8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                       Cause IEI                      │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │                        Length of cause contents              │Octet 2
    ├───┬───────┬───┬───────────────┤
    │ 0/1  │   coding     │  0   │                              │
    │ ext  │  standard    │spare │           location           │Octet 3
    ├───┼───────┴───┴───────────────┤
    │  1   │                                                      │
    │ ext  │                  recommendation                      │Octet 3a*
    ├───┼───────────────────────────┤
    │  1   │                                                      │
    │ ext  │                   cause value                        │Octet 4
    ├───┴───────────────────────────┤
    │                                                              │
    │                     diagnostic(s) if any                     │Octet 5*
    │                                                              │
    ┊                                                              ┊
    ┊                                                              ┊Octet N*
    └───────────────────────────────┘
*/
typedef struct
{
    NAS_CC_LOCATION_ENUM_U8             Location            :4;
    VOS_UINT8                           Spare               :1;
    NAS_CC_CODING_STANDARD_ENUM_U8      CodingStd           :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CAUSE_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                           Recommendation      :7;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CAUSE_OCTET3A_STRU;

typedef struct
{
    MN_CALL_CC_CAUSE_ENUM_U8            CauseValue          :7;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CAUSE_OCTET4_STRU;

#define NAS_CC_MAX_DIAGNOSTIC_LEN       27
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CAUSE_OCTET3_STRU         Octet3;
    NAS_CC_IE_CAUSE_OCTET3A_STRU        Octet3a;
    NAS_CC_IE_CAUSE_OCTET4_STRU         Octet4;
    VOS_UINT8                           diagnostic[NAS_CC_MAX_DIAGNOSTIC_LEN];
}NAS_CC_IE_CAUSE_STRU;


/* [10.5.4.11a] CLIR suppression */
/*============================================================================*/
/* Figure 10.5.96/3GPP TS 24.008 CLIR suppression information element */
/*
       8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                 CLIR suppression IEI                 │Octet 1
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
}NAS_CC_IE_CLIR_S_STRU;


/* [10.5.4.11b] CLIR invocation */
/*============================================================================*/
/* Figure 10.5.97/3GPP TS 24.008 CLIR invocation information element */
/*
       8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                  CLIR invocation IEI                 │Octet 1
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
}NAS_CC_IE_CLIR_I_STRU;


/* [10.5.4.12] Congestion level */
/*============================================================================*/
/* Figure 10.5.98/3GPP TS 24.008 Congestion level information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬──────────┬────────────────┐
    │      │Congestion level IEI│                                │Octet 1
    └───┴──────────┴────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
}NAS_CC_IE_CONG_LEVEL_STRU;


/* [10.5.4.13] Connected number */
/*============================================================================*/
/* Figure 10.5.99/3GPP TS 24.008 Connected number information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                 Connected number IEI                 │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │                 Length of connected number contents          │Octet 2
    ├───┬───────────┬───────────────┤
    │ 0/1  │       type of        │       Numbering plan         │
    │ ext  │        number        │       identification         │Octet 3
    ├───┼───────┬───┴───────┬───────┤
    │  1   │ Presentation │  0       0       0   │  Screeening  │
    │ ext  │  indicator   │        Spare         │  indicator   │Octet 3a*
    ├───┴───────┴───┬───────┴───────┤
    │                              │                              │
    │       Number digit 2         │        Number digit 1        │Octet 4*
    ├───────────────┼───────────────┤
    │                              │                              │
    │       Number digit 4         │        Number digit 3        │Octet 5*
    ├───────────────┼───────────────┤
    │                              │                              │    :
    │                              │                              │    :
    ┊                              ┊                              ┊
    └───────────────┴───────────────┘
*/
typedef struct
{
    NAS_CC_NPI_ENUM_U8                  NPI                     :4;
    NAS_CC_TON_ENUM_U8                  TON                     :3;
    VOS_UINT8                           Ext                     :1;
}NAS_CC_IE_CONN_NUM_OCTET3_STRU;

typedef struct
{
    NAS_CC_SCREENING_IND_ENUM_U8        ScreeningIndicator      :2;
    VOS_UINT8                           Spare                   :3;
    NAS_CC_PRESENTATION_IND_ENUM_U8     PresentationIndicator   :2;
    VOS_UINT8                           Ext                     :1;
}NAS_CC_IE_CONN_NUM_OCTET3A_STRU;

#define NAS_CC_MAX_CONN_BCD_NUM_LEN     10
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CONN_NUM_OCTET3_STRU      Octet3;
    NAS_CC_IE_CONN_NUM_OCTET3A_STRU     Octet3a;

    VOS_UINT8                           BCDNum[NAS_CC_MAX_CONN_BCD_NUM_LEN];
}NAS_CC_IE_CONN_NUM_STRU;


/* [10.5.4.14] Connected subaddress */
/*============================================================================*/
/* Figure 10.5.100/3GPP TS 24.008 Connected subaddress information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                Connected Subaddress IEI              │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │             Length of connected Subaddress contents          │Octet 2
    ├───┬───────────┬───┬───────────┤
    │      │       type of        │odd/ev│  0       0       0   │
    │      │      Subaddress      │Indica│        spare         │Octet 3
    ├───┴───────────┴───┴───────────┤
    │                                                              │
    │                     Subaddress information                   │Octet 4*
    │                                                              │
    ┊                                                              ┊
    ┊                                                              ┊etc.
    └───────────────┴───────────────┘
*/
typedef struct
{
    VOS_UINT8                           Spare               :3;
    NAS_CC_ODD_EVEN_IND_ENUM_U8         OddEvenIndicate     :1;
    NAS_CC_TYPE_OF_SUBADDR_ENUM_U8      TypeOfSubaddr       :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_CONN_ADDR_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CONN_ADDR_OCTET3_STRU     Octet3;

    VOS_UINT8                           SubAddrInfo[NAS_CC_MAX_SUBADDR_INFO_LEN];
}NAS_CC_IE_CONN_ADDR_STRU;


/* [10.5.4.15] Facility */
/*============================================================================*/
/* Figure 10.5.101/3GPP TS 24.008 Facility information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                    Facility IEI                      │Octet 1
    ├───┴───────────────────────────┤
    │                    Length of facility contents               │Octet 2
    ├───────────────────────────────┤
    │         Facility information (see 3GPP TS 24.080)            │Octet 3-?
    └───────────────────────────────┘
*/
#define NAS_CC_MAX_FACILITY_LEN         252
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           aucFacility[NAS_CC_MAX_FACILITY_LEN];
}NAS_CC_IE_FACILITY_STRU;


/* [10.5.4.16] High layer compatibility */
/*============================================================================*/
/* Figure 10.5.102/3GPP TS 24.008 High layer compatibility information element*/
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │             High layer compatibility IEI             │Octet 1
    ├───┴───────────────────────────┤
    │          Length of high layer compatibility contents         │Octet 2
    ├───┬───────┬───────────┬───────┤
    │  1   │    coding    │    interpretation    │presentat. met│
    │ ext  │   standard   │                      │-hod of protoc│
    │      │              │                      │-ol profile   │Octet 3*
    ├───┼───────┴───────────┴───────┤
    │ 0/1  │                                                      │
    │ ext  │       High layer characteristics identification      │Octet 4*
    ├───┼───────────────────────────┤
    │  1   │          Extended high layer characteristics         │
    │ ext  │                   identification                     │Octet 4a*
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           ProtocolProfile     :2;
    VOS_UINT8                           Interpretation      :3;
    NAS_CC_CODING_STANDARD_ENUM_U8      CodingStandard      :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_HLC_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                           HLCI                :7;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_HLC_OCTET4_STRU;

typedef struct
{
    VOS_UINT8                           ExtHLCI             :7;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_HLC_OCTET4A_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_HLC_OCTET3_STRU           Octet3;
    NAS_CC_IE_HLC_OCTET4_STRU           Octet4;
    NAS_CC_IE_HLC_OCTET4A_STRU          Octet4a;
}NAS_CC_IE_HLC_STRU;


/* [10.5.4.16.1] Static conditions for the HLC IE contents */
/*============================================================================*/


/* [10.5.4.17] Keypad facility */
/*============================================================================*/
/* Figure 10.5.103/3GPP TS 24.008 Keypad facility information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                  Keypad facility IEI                 │Octet 1
    ├───┼───────────────────────────┤
    │Spare │                                                      │
    │  0   │          Keypad information (IA5 character)          │Octet 2
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           KeypadInfo          :7;
    VOS_UINT8                           Spare               :1;
}NAS_CC_IE_KEYPAD_FACILITY_STRU;


/* [10.5.4.18] Low layer compatibility */
/*============================================================================*/
/* Figure 10.5.104/3GPP TS 24.008 Low layer compatibility information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │             Low layer compatibility IEI              │Octet 1
    ├───┴───────────────────────────┤
    │         Length of the low layer compatibility contents       │Octet 2
    ├───────────────────────────────┤
    │              The following octets are coded                  │Octet 3*
    │                     as described in                          │    :
    │                ITU Recommendation Q.931                      │    :
    │    (Coding of the modem type according to both Q.931 and     │    :
    │           ETS 300 102-1 (12-90) shall be accepted)           │
    └───────────────────────────────┘
*/
#define NAS_CC_MAX_LLC_CONTENTS_LEN     16
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           LLCContents[NAS_CC_MAX_LLC_CONTENTS_LEN];
}NAS_CC_IE_LLC_STRU;


/* [10.5.4.19] More data */
/*============================================================================*/
/* Figure 10.5.105/3GPP TS 24.008 More data information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                    More data IEI                     │Octet 1
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
}NAS_CC_IE_MORE_DATA_STRU;

/* [10.5.4.20] Notification indicator */
/*============================================================================*/
/* Figure 10.5.106/3GPP TS 24.008 Notification indicator information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │              Notification indicator IEI              │Octet 1
    ├───┼───────────────────────────┤
    │  1   │                                                      │
    │ ext  │               Notification description               │Octet 2
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                               IsExist;

    NAS_CC_NOTIFICATION_DESCRIPTION_ENUM_U8 NotificationDescription :7;
    VOS_UINT8                               Ext                     :1;
}NAS_CC_IE_NOTIFICATION_INDICATOR_STRU;


/* [10.5.4.21] Progress indicator */
/*============================================================================*/
/* Figure 10.5.107/3GPP TS 24.008 Progress indicator information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                Progress indicator IEI                │Octet 1
    ├───┴───────────────────────────┤
    │                Length of progress indicator contents         │Octet 2
    ├───┬───────┬───┬───────────────┤
    │  1   │    coding    │  0   │                              │
    │ ext  │   standard   │spare │            location          │Octet 3
    ├───┼───────┴───┴───────────────┤
    │  1   │                                                      │
    │ ext  │                 progress description                 │Octet 4
    └───┴───────────────────────────┘
*/
typedef struct
{
    NAS_CC_LOCATION_ENUM_U8             Location            :4;
    VOS_UINT8                           Spare               :1;
    NAS_CC_CODING_STANDARD_ENUM_U8      CodingStd           :2;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_PROG_IND_OCTET3_STRU;

typedef struct
{
    NAS_CC_PROGRESS_DESCRIPTION_ENUM_U8 ProgDesc            :7;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_PROG_IND_OCTET4_STRU;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_PROG_IND_OCTET3_STRU      Octet3;
    NAS_CC_IE_PROG_IND_OCTET4_STRU      Octet4;
}NAS_CC_IE_PROGRESS_INDICATOR_STRU;



/* [10.5.4.21a] Recall type $(CCBS)$ */
/*============================================================================*/
/* Figure 10.5.108/3GPP TS 24.008 Recall type information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                   recall type IEI                    │Octet 1
    ├───┴───────────────┬───────────┤
    │                spare                 │      recall type     │
    │  0       0       0       0       0   │                      │Octet 2
    └───────────────────┴───────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    NAS_CC_RECALL_TYPE_ENUM_U8          RecallType          :3;
    VOS_UINT8                           Spare               :5;
}NAS_CC_IE_RECALL_TYPE_STRU;


/* [10.5.4.21b] Redirecting party BCD number */
/*============================================================================*/
/* Figure 10.5.108a/3GPP TS 24.008
   Redirecting party BCD number information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │          Redirecting party BCD number IEI            │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │          Length of redirecting party BCD number contents     │Octet 2
    ├───┬───────────┬───────────────┤
    │ 0/1  │       type of        │       Numbering plan         │
    │ ext  │        number        │       identification         │Octet 3
    ├───┼───────┬───┴───────┬───────┤
    │  1   │ Presentation │  0       0       0   │  Screeening  │
    │ ext  │  indicator   │        Spare         │  indicator   │Octet 3a*
    ├───┴───────┴───┬───────┴───────┤
    │                              │                              │
    │       Number digit 2         │        Number digit 1        │Octet 4*
    ├───────────────┼───────────────┤
    │                              │                              │
    │       Number digit 4         │        Number digit 3        │Octet 5*
    ├───────────────┼───────────────┤
    │                              │                              │    :
    │                              │                              │    :
    ┊                              ┊                              ┊
    └───────────────┴───────────────┘
*/
typedef struct
{
    NAS_CC_NPI_ENUM_U8                  NPI                 :4;
    NAS_CC_TON_ENUM_U8                  TON                 :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_REDIRECTING_NUM_OCTET3_STRU;

typedef struct
{
    NAS_CC_SCREENING_IND_ENUM_U8        ScreeningInd        :2;
    VOS_UINT8                           Octet3aSpare       :3;
    NAS_CC_PRESENTATION_IND_ENUM_U8     PresentationInd     :2;
    VOS_UINT8                           Octet3aExt         :1;
}NAS_CC_IE_REDIRECTING_NUM_OCTET3A_STRU;

#define NAS_CC_MAX_REDIRECTING_BCD_NUM_LEN  10
typedef struct
{
    VOS_UINT8                               IsExist;
    VOS_UINT8                               LastOctOffset;

    NAS_CC_IE_REDIRECTING_NUM_OCTET3_STRU   Octet3;
    NAS_CC_IE_REDIRECTING_NUM_OCTET3A_STRU  Octet3a;

    VOS_UINT8                               BCDNum[NAS_CC_MAX_REDIRECTING_BCD_NUM_LEN];
}NAS_CC_IE_REDIRECTING_NUM_STRU;


/* [10.5.4.21c] Redirecting party subaddress */
/*============================================================================*/
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │           Redirecting party Subaddress IEI           │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │          Length of redirecting party Subaddress contents     │Octet 2
    ├───┬───────────┬───┬───────────┤
    │      │       type of        │odd/ev│  0       0       0   │
    │      │      Subaddress      │Indica│        spare         │Octet 3
    ├───┴───────────┴───┴───────────┤
    │                                                              │
    │                     Subaddress information                   │Octet 4*
    │                                                              │
    ┊                                                              ┊
    ┊                                                              ┊etc.
    └───────────────┴───────────────┘
*/
typedef struct
{
    VOS_UINT8                           Spare               :3;
    NAS_CC_ODD_EVEN_IND_ENUM_U8         OddEvenIndicate     :1;
    NAS_CC_TYPE_OF_SUBADDR_ENUM_U8      TypeOfSubaddr       :3;
    VOS_UINT8                           Ext                 :1;
}NAS_CC_IE_REDIRECTING_SUBADDR_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                                   IsExist;
    VOS_UINT8                                   LastOctOffset;

    NAS_CC_IE_REDIRECTING_SUBADDR_OCTET3_STRU   Octet3;
    VOS_UINT8                                   SubAddrInfo[NAS_CC_MAX_SUBADDR_INFO_LEN];
}NAS_CC_IE_REDIRECTING_SUBADDR_STRU;


/* [10.5.4.22] Repeat indicator */
/*============================================================================*/
/* Figure 10.5.109/3GPP TS 24.008 Repeat indicator information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────┬───────────────┐
    │      │ repeat indicator IEI │       repeat indication      │Octet 1
    └───┴───────────┴───────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           RepeatIndication;
}NAS_CC_IE_REPEAT_INDICATOR_STRU;


/* [10.5.4.22a] Reverse call setup direction */
/*============================================================================*/
/* Figure 10.5.110/3GPP TS 24.008
   Reverse call setup direction information element */
/*
    8       7       6       5       4       3       2       1
┌───┬───────────────────────────┐
│      │           reverse call setup direction IEI           │Octet 1
└───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
}NAS_CC_IE_REVERSE_CALL_SETUP_DIR_STRU;


/* [10.5.4.22b] SETUP Container $(CCBS)$ */
/*============================================================================*/
/* Figure 10.5.111/3GPP TS 24.008
   Octet j (j = 3, 4 ... n) is the unchanged octet j of the SETUP message. */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                 SETUP Container IEI                  │Octet 1
    ├───┴───────────────────────────┤
    │                Length of SETUP container contents            │Octet 2
    ├───────────────────────────────┤
    │                                                              │Octet 3-n
    │                        SETUP message                         │
    │                                                              │
    └───────────────────────────────┘
*/
#define NAS_CC_MAX_SETUP_MSG_LEN        252
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           SetupMessage[NAS_CC_MAX_SETUP_MSG_LEN];
}NAS_CC_IE_SETUP_CONTAINER_STRU;


/* [10.5.4.23] Signal */
/*============================================================================*/
/* Figure 10.5.112/3GPP TS 24.008 Signal information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                     Signal IEI                       │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │                        Signal value                          │Octet 2
    └───────────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_SIGNAL_VALUE_ENUM_U8         SignalValue;
}NAS_CC_IE_SIGNAL_STRU;

/* [10.5.4.24] SS Version Indicator */
/*============================================================================*/
/* Figure 10.5.113/3GPP TS 24.008 SS Version Indicator information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │               SS version indicator IEI               │Octet 1
    ├───┴───────────────────────────┤
    │             Length of SS version indicator contents          │Octet 2
    ├───────────────────────────────┤
    │            SS version information (see 3GPP TS 24.080)       │Octet 3
    └───────────────────────────────┘
*/

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           Version;
}NAS_CC_IE_SS_VER_INDICATOR_STRU;


/* [10.5.4.25] User-user */
/*============================================================================*/
/* Figure 10.5.114/3GPP TS 24.008 User-user information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                   User-user IEI                      │Octet 1
    ├───┴───────────────────────────┤
    │                   Length of user-user contents               │Octet 2
    ├───────────────────────────────┤
    │               User-user protocol discriminator               │Octet 3
    ├───────────────────────────────┤
    │                                                              │Octet 4-n
    │                   User-user information                      │
    ┊                                                              ┊
    └───────────────────────────────┘
*/
#define NAS_CC_MAX_USER_USER_INFO_LEN   128
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           UserUserPD;
    VOS_UINT8                           UserUserInfo[NAS_CC_MAX_USER_USER_INFO_LEN];
}NAS_CC_IE_USER_USER_STRU;


/* [10.5.4.26] Alerting Pattern $(NIA)$ */
/*============================================================================*/
/* Figure 10.5.115/3GPP TS 24.008 Alerting Pattern information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │               Alerting Pattern IEI                   │Octet 1
    ├───┴───────────────────────────┤
    │               Length of alerting pattern content             │Octet 2
    ├───────────────┬───────────────┤
    │  0       0       0       0   │       Alerting Pattern       │
    │            spare             │             value            │Octet 3
    └───────────────┴───────────────┘
*/
typedef struct
{
    NAS_CC_ALERTING_PATTERN_ENUM_U8     AlertingPattern     :4;
    VOS_UINT8                           Spare               :4;
}NAS_CC_IE_ALERTING_PATTERN_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                               IsExist;
    VOS_UINT8                               LastOctOffset;

    NAS_CC_IE_ALERTING_PATTERN_OCTET3_STRU  Octet3;
}NAS_CC_IE_ALERTING_PATTERN_STRU;


/* [10.5.4.27] Allowed actions $(CCBS)$ */
/*============================================================================*/
/* Figure 10.5.116/3GPP TS 24.008 Allowed actions information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                 Allowed Actions IEI                  │Octet 1
    ├───┴───────────────────────────┤
    │               Length of allowed actions contents             │Octet 2
    ├───┬───────────────────────────┤
    │CCBS  │  0       0       0       0       0       0       0   │
    │act.  │                        spare                         │Octet 3
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           Spare               :7;
    NAS_CC_CCBS_ACTIVATION_ENUM_U8      CCBSActivation      :1;
}NAS_CC_IE_ALLOWED_ACTIONS_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                               IsExist;
    VOS_UINT8                               LastOctOffset;

    NAS_CC_IE_ALLOWED_ACTIONS_OCTET3_STRU   Octet3;
}NAS_CC_IE_ALLOWED_ACTIONS_STRU;


/* [10.5.4.28] Stream Identifier */
/*============================================================================*/
/* Figure 10.5.116/3GPP TS 24.008 Allowed actions information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                Stream Identifier IEI                 │Octet 1
    ├───┴───────────────────────────┤
    │               Length of Stream Identifier contents           │Octet 2
    ├───────────────────────────────┤
    │                                                              │
    │                    Stream Identifier Value                   │Octet 3
    └───────────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    VOS_UINT8                           StreamIdentifier;
}NAS_CC_IE_STREAM_IDENTIFIER_STRU;


/* [10.5.4.29] Network Call Control Capabilities */
/*============================================================================*/
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │        Network Call Control Capabilities IEI         │Octet 1
    ├───┴───────────────────────────┤
    │                                                              │
    │           Length of NW Call Control Cap. contents            │Octet 2
    ├───────────────────────────┬───┤
    │  0       0       0       0       0       0       0   │      │
    │                        spare                         │ MCS  │Octet 3
    └───────────────────────────┴───┘
*/
typedef struct
{
    NAS_CC_MCS_ENUM_U8                  MCS                 :1;
    VOS_UINT8                           Spare               :7;

}NAS_CC_IE_NW_CALL_CTRL_CAP_OCTET3_STRU;

typedef struct
{
    VOS_UINT8                               IsExist;
    VOS_UINT8                               LastOctOffset;
    NAS_CC_IE_NW_CALL_CTRL_CAP_OCTET3_STRU  Octet3;
}NAS_CC_IE_NW_CALL_CTRL_CAP_STRU;


/* [10.5.4.30] Cause of No CLI */
/*============================================================================*/
/* Figure 10.5.118a/3GPP TS 24.008 Cause of No CLI information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                 Cause of No CLI IEI                  │Octet 1
    ├───┴───────────────────────────┤
    │                 Length of Cause of No CLI contents           │Octet 2
    ├───────────────────────────────┤
    │                           Cause of No CLI                    │Octet 3
    └───────────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_CAUSE_OF_NO_CLI_ENUM_U8      CauseOfNoCLI;
}NAS_CC_IE_NO_CLI_CAUSE_STRU;


/* [10.5.4.31] Void */
/*============================================================================*/


/* [10.5.4.32] Supported codec list */
/*============================================================================*/
/* Figure 10.5.118c/3GPP TS 24.008 Supported codec list information element */
/*
        8       7       6       5       4       3       2       1
    ┌───────────────────────────────┐
    │                  Supported Codec List IEI                    │Octet 1
    ├───────────────────────────────┤
    │                Length Of Supported Codec list                │Octet 2
    ├───────────────────────────────┤
    │               System Identification 1 (SysID 1)              │Octet 3
    ├───────────────────────────────┤
    │                 Length Of Bitmap for SysID 1                 │Octet 4
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 1, bits 1 to 8            │Octet 5
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 1, bits 9 to 16           │Octet 6
    ├───────────────────────────────┤
    │               System Identification 2 (SysID 2)              │Octet j
    ├───────────────────────────────┤
    │                 Length Of Bitmap for SysID 2                 │Octet j+1
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 2, bits 1 to 8            │Octet j+2
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 2, bits 9 to 16           │Octet j+3
    ├───────────────────────────────┤
    │               System Identification x (SysID x)              │Octet m
    ├───────────────────────────────┤
    │                 Length Of Bitmap for SysID x                 │Octet m+1
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID x, bits 1 to 8            │Octet m+2
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID x, bits 9 to 16           │Octet m+3
    └───────────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           SysId;
    VOS_UINT8                           LastOctOffsetengthOfBitMap;
    VOS_UINT8                           CodecBitmapL;
    VOS_UINT8                           CodecBitmapH;
}NAS_CC_IE_CODEC_INFO_STRU;
#define MAX_CODEC_NUM 10
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CC_IE_CODEC_INFO_STRU           CodecInfo[MAX_CODEC_NUM];
}NAS_CC_IE_SUPPORTED_CODEC_LIST_STRU;


/* [10.5.4.33] Service category */
/*============================================================================*/
/* Figure 10.5.118d/3GPP TS 24.008 Service Category information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │               Service Category IEI                   │Octet 1
    ├───┴───────────────────────────┤
    │                    Length of Service Category                │Octet 2
    ├───┬───────────────────────────┤
    │  0   │          Emergency Service Category Value            │
    │spare │                                                      │Octet 3
    └───┴───────────────────────────┘
*/
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-16, begin */
typedef struct
{
    NAS_CC_EMERGENCY_CAT_ENUM_U8        EmergencyCAT        :7;
    VOS_UINT8                           Spare               :1;
}NAS_CC_IE_SERVICE_CATEGORY_OCTET3_STRU;
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-16, end */

typedef struct
{
    VOS_UINT8                               IsExist;
    VOS_UINT8                               LastOctOffset;

    NAS_CC_IE_SERVICE_CATEGORY_OCTET3_STRU  Octet3;
}NAS_CC_IE_SERVICE_CATEGORY_STRU;


/* [10.5.4.34] Redial */
/*============================================================================*/
/* Figure 10.5.118e/3GPP TS 24.008 Redial information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │                     Redial IEI                       │Octet 1
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
}NAS_CC_IE_REDIAL_STRU;


/* [10.5.4.35] Network-initiated Service Upgrade indicator */
/*============================================================================*/
/* Figure 10.5.118f/3GPP TS 24.008
   Network-initiated Service Upgrade indicator information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────────────────────┐
    │      │   Network-initiated Service Upgrade indicator IEI    │Octet 1
    └───┴───────────────────────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
}NAS_CC_IE_NW_INIT_SERV_UPGRADE_STRU;



/* [10.5.1.11] Priority Level */
/*============================================================================*/
/* Figure 10.5.11/3GPP TS 24.008 Priority Level information element */
/*
        8       7       6       5       4       3       2       1
    ┌───┬───────────┬───┬───────────┐
    │      │    Priority Level    │  0   │     call priority    │
    │      │          IEI         │spare │                      │Octet 1
    └───┴───────────┴───┴───────────┘
*/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;

    NAS_CALL_PRIORITY_ENUM_U8           CallPriority;
}NAS_CC_IE_PRIORITY_LEVEL_STRU;







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

#endif /* __NAS_CC_IE_H__ */

