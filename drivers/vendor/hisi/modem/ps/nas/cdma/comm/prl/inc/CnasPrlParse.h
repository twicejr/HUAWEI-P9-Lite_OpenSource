/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasPrlParse.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年8月2日
  最近修改   :
  功能描述   : PRL参数定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月2日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_PRL_PARSE_H__
#define __CNAS_PRL_PARSE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_PRL_WILDCARD_SID                               (0)

#define CNAS_PRL_WILDCARD_NID                               (65535)

/* 3GPP2 C.S0016-D 3.5.5 Preferred Roaming List: NUM_ACQ_RECS 9bits */
#define CNAS_PRL_ACQ_RECORD_MAX_NUM                         (512)

/* 3GPP2 C.S0016-D 3.5.5 Preferred Roaming List: NUM_SYS_RECS 14bits */
#define CNAS_PRL_SYS_RECORD_MAX_NUM                         (16384)

/* 3GPP2 C.S0016-D 3.5.5.2.1.3: NUM_CHANS 5bits */
#define CNAS_PRL_ACQ_CUSTOM_CHAN_RECORD_MAX_NUM             (32)

/* 3GPP2 C.S0016-D 3.5.5.2.1.5: NUM_BLOCKS 3bits */
#define CNAS_PRL_ACQ_BLOCK_RECORD_MAX_NUM                   (8)

#define CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM                 (128)

#define CNAS_PRL_PRL_LIST_SIZE_BYTE_LEN                     (2)

/* 3GPP2 C.S0016-D 3.5.5.3.2.2-4: NUM_SID 4bits */
#define CNAS_PRL_MCC_MNC_SID_MAX_NUM                        (16)

/* 3GPP2 C.S0016-D 3.5.5.3.2.2-5: NUM_NID 4bits */
#define CNAS_PRL_MCC_MNC_NID_MAX_NUM                        (16)

/* 3GPP2 C.S0016-D 3.5.5.3.2.2-6: SUBNET_ID 3bits */
#define CNAS_PRL_MCC_MNC_SUBNET_MAX_NUM                     (16)
#define CNAS_PRL_MCC_MNC_SUBNET_MAX_LEN                     (16)

#define CNAS_PRL_BYTES_IN_SUBNET                            (16)                /* SUBNET字节数 */
#define CNAS_PRL_MAX_SUBNET_LEN_IN_BITS                     (128)               /* SUBNET最大位数 */

#define CNAS_PRL_BIT_LEN_1_BIT                              (1)
#define CNAS_PRL_BIT_LEN_2_BIT                              (2)
#define CNAS_PRL_BIT_LEN_3_BIT                              (3)
#define CNAS_PRL_BIT_LEN_4_BIT                              (4)
#define CNAS_PRL_BIT_LEN_5_BIT                              (5)
#define CNAS_PRL_BIT_LEN_6_BIT                              (6)
#define CNAS_PRL_BIT_LEN_7_BIT                              (7)
#define CNAS_PRL_BIT_LEN_8_BIT                              (8)
#define CNAS_PRL_BIT_LEN_9_BIT                              (9)
#define CNAS_PRL_BIT_LEN_11_BIT                             (11)
#define CNAS_PRL_BIT_LEN_12_BIT                             (12)
#define CNAS_PRL_BIT_LEN_14_BIT                             (14)
#define CNAS_PRL_BIT_LEN_15_BIT                             (15)
#define CNAS_PRL_BIT_LEN_16_BIT                             (16)

#define CNAS_PRL_CALC_NEXT_PARA_BIT_OFFSET(curBitOffset)    ((curBitOffset)%CNAS_PRL_BIT_LEN_8_BIT)

#define CNAS_PRL_CALC_NEXT_PARA_BYTE_OFFSET(curBitOffset)   ((curBitOffset)/CNAS_PRL_BIT_LEN_8_BIT)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_PRL_SYS_MODE_ENUM
 结构说明  : CDMA系统模式
 1.日    期   : 2014年08月02日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SYS_MODE_ENUM
{
    CNAS_PRL_SYS_MODE_AMPS                                  = 0,
    CNAS_PRL_SYS_MODE_CDMA                                  = 1,
    CNAS_PRL_SYS_MODE_HDR                                   = 2,

    CNAS_PRL_SYS_MODE_BUTT
};
typedef VOS_UINT8 CNAS_PRL_SYS_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_SSPR_P_REV_ENUM
 结构说明  : PRL版本编号(参考3GPP2 C.S0016-D Table 3.5.1.7-1 Feature Identifier)
 1.日    期   : 2014年08月02日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SSPR_P_REV_ENUM
{
    CNAS_PRL_SSPR_P_REV_NONE                                = 0,
    CNAS_PRL_SSPR_P_REV_1                                   = 1,    /* PRL */
    CNAS_PRL_SSPR_P_REV_3                                   = 3,    /* EPRL */
    CNAS_PRL_SSPR_P_REV_4                                   = 4     /* RESERVED */
};
typedef VOS_UINT8 CNAS_PRL_SSPR_P_REV_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_SYS_ROAMING_IND_ENUM
 结构说明  : roaming display indication (参考3GPP2 C.R1001-A中8.2章节中Table 8.1-1)

 1.日    期   : 2014年08月02日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SYS_ROAMING_IND_ENUM
{
    /* Roaming Indicator On */
    CNAS_PRL_SYS_ROAMING_STATUS_ON                              = 0,

    /* Roaming Indicator Off */
    CNAS_PRL_SYS_ROAMING_STATUS_OFF                             = 1,

    /* Roaming Indicator Flashing */
    CNAS_PRL_SYS_ROAMING_STATUS_FLASHING                        = 2,

    /* Out of Neighborhood */
    CNAS_PRL_SYS_ROAMING_STATUS_OUT_OF_NEIGHBORHOOD             = 3,

    /* Out of Building */
    CNAS_PRL_SYS_ROAMING_STATUS_OUT_OF_BUILDING                 = 4,

    /* Roaming - Preferred System */
    CNAS_PRL_SYS_ROAMING_STATUS_PREFERRED_SYSTEM                = 5,

    /* Roaming - Available System */
    CNAS_PRL_SYS_ROAMING_STATUS_AVAILABLE_SYSTEM                = 6,

    /* Roaming - Alliance Partner */
    CNAS_PRL_SYS_ROAMING_STATUS_ALLIANCE_PARTNER                = 7,

    /* Roaming - Premium Partner */
    CNAS_PRL_SYS_ROAMING_STATUS_PREMIUM_PARTER                  = 8,

    /* Roaming - Full Service Functionality */
    CNAS_PRL_SYS_ROAMING_STATUS_FULL_SRVICE_FUNCTIONALITY       = 9,

    /* Roaming - Partial Service Functionality */
    CNAS_PRL_SYS_ROAMING_STATUS_PARTIAL_SRVICE_FUNCTIONALITY    = 10,

    /* Roaming Banner On */
    CNAS_PRL_SYS_ROAMING_STATUS_BANNER_ON                       = 11,

    /* Roaming Banner Off */
    CNAS_PRL_SYS_ROAMING_STATUS_BANNER_OFF                      = 12,

    CNAS_PRL_SYS_ROAMING_STATUS_RESERVED_FOR_STARDARD_EN        = 13,

    /* 01000000 through 01111111 Reserved for Non-Standard Enhanced Roaming Indicator Numbers */
    CNAS_PRL_SYS_ROAMING_STATUS_RESERVED_FOR_NON_STARDARD_EN    = 64,

    /* 10000000 through 11111111 Reserved */
    CNAS_PRL_SYS_ROAMING_STATUS_RESERVED                        = 128
};
typedef VOS_UINT8 CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_ACQ_TYPE_ENUM
 结构说明  : 捕获记录类型acquire record type (参考3GPP2 C.S0016-D中3.5.5.2章节中Table 3.5.5.2-2 )

 1.日    期   : 2014年08月02日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_ACQ_TYPE_ENUM
{
    /* Reserved */
    CNAS_PRL_ACQ_TYPE_RESERVED                              = 0,

    /* Cellular Analog */
    CNAS_PRL_ACQ_TYPE_CELLULAR_ANALOG                       = 1,

    /* Cellular CDMA (Standard Channels) */
    CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS       = 2,

    /* Cellular CDMA (Custom Channels) */
    CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS         = 3,

    /* Cellular CDMA Preferred */
    CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED               = 4,

    /* PCS CDMA (Using Blocks) */
    CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS                 = 5,

    /* PCS CDMA (Using Channels) */
    CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS               = 6,

    /* JTACS CDMA (Standard Channels) */
    CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS          = 7,

    /* JTACS CDMA (Custom Channels) */
    CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS            = 8,

    /* 2GHz Band (Using Channels) */
    CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS                = 9,

    /* Generic Acquisition Record for cdma2000 1x and IS-95 */
    CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95    = 10,

    /* Generic Acquisition Record for HRPD */
    CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD           = 11,

    /* Reserved for Obsolete Identification ‘00001100’- ‘00001110’*/
    CNAS_PRL_ACQ_TYPE_Reserved_FOR_OBSOLETE_IDENTIFICATION  = 12,

    /* Common Acquisition table record for UMB */
    CNAS_PRL_ACQ_TYPE_COMMON_ACQ_TABLE_RECORD_FOR_UMB       = 15,

    /* Common Acquisition record for UMB */
    CNAS_PRL_ACQ_TYPE_COMMON_ACQ_RECORD_FOR_UMB             = 16,

    /* Reserved */
    CNAS_PRL_ACQ_TYPE_ALL_OTHER_RESERVED                    = 17
};
typedef VOS_UINT8 CNAS_PRL_ACQ_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_SYS_SEL_TYPE_ENUM
 结构说明  : System A/B Selection Type (参考3GPP2 C.S0016-D中Table 3.5.5.2.1.1-1 )

 1.日    期   : 2014年08月03日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SYS_SEL_TYPE_ENUM
{
    CNAS_PRL_SYS_SEL_TYPE_A,            /* system A */
    CNAS_PRL_SYS_SEL_TYPE_B,            /* system B */
    CNAS_PRL_SYS_SEL_TYPE_RESERVED,     /* reserved */
    CNAS_PRL_SYS_SEL_TYPE_A_OR_B,       /* system A OR B */

    CNAS_PRL_SYS_SEL_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_PRL_BAND10_SYS_SEL_TYPE_ENUM
 结构说明  : System A/B Selection Type (参考3GPP2 C.S0016-D中Table 3.5.5.2.1.1-1 )

 1.日    期   : 2014年08月03日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_BAND10_SYS_SEL_TYPE_ENUM
{
    CNAS_PRL_BAND10_SYS_SEL_TYPE_A,            /* system A */
    CNAS_PRL_BAND10_SYS_SEL_TYPE_B,            /* system B */
    CNAS_PRL_BAND10_SYS_SEL_TYPE_C,            /* system C */
    CNAS_PRL_BAND10_SYS_SEL_TYPE_D,            /* system D */
    CNAS_PRL_BAND10_SYS_SEL_TYPE_E,            /* system E */
    CNAS_PRL_BAND10_SYS_SEL_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_PRL_BAND10_SYS_SEL_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM
 结构说明  : Standard Channel Selection Type (参考3GPP2 C.S0016-D中Table 3.5.5.2.1.2-1 )

 1.日    期   : 2014年08月03日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM
{
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_RESERVED,                   /* Reserved */
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,              /* Primary CDMA Channel */
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,              /* Secondary CDMA Channel */
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN,       /* Primary or Secondary CDMA Channel */

    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM
 结构说明  : PCS CDMA Frequency Block (参考3GPP2 C.S0016-D中Table Table 3.5.5.2.1.5-1 )

 1.日    期   : 2014年08月05日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM
{
    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_A                     = 0,    /* Block A ‘000’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_B                     = 1,    /* Block B ‘001’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_C                     = 2,    /* Block C ‘010’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_D                     = 3,    /* Block D ‘011’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_E                     = 4,    /* Block E ‘100’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_F                     = 5,    /* Block F ‘101’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_RESERVED              = 6,    /* Reserved ‘110’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ANY_BLOCK             = 7,    /* Any Block ‘111’*/

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ANY_BUTT
};
typedef VOS_UINT8 CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_PRL_NID_INCL_TYPE_ENUM
 结构说明  : NID included (参考3GPP2 C.S0016-D中Table Table Table 3.5.5.3-1 )

 1.日    期   : 2014年08月05日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_NID_INCL_TYPE_ENUM
{
    CNAS_PRL_NID_NOT_INCL_WILD_CARD                         = 0, /* NID not included. Assume NID value ‘1111111111111111’*/
    CNAS_PRL_NID_INCL                                       = 1, /* NID included */
    CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM                    = 2, /* NID not included. Assume NID value ‘0000000000000000’*/
    CNAS_PRL_NID_RESERVED                                   = 3  /* Reserved */
};
typedef VOS_UINT8 CNAS_PRL_NID_INCL_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_MCC_MNC_SUBTYPE_ENUM
 结构说明  : Mcc mnc subtype (参考3GPP2 C.S0016-D中Table  3.5.5.3.2.2-2 SYS_RECORD_SUBTYPE Values  )

 1.日    期   : 2014年12月02日
   作    者   : d00212987
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_MCC_MNC_SUBTYPE_ENUM
{
    CNAS_PRL_MCC_MNC_SUBTYPE_ONLY                           = 0, /* MCC MNC only */
    CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID                   = 1, /* MCC MNC with multiple SID */
    CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID               = 2, /* MCC MNC with multiple SID/NID*/
    CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID             = 3, /* MCC MNC with multiple subnet IDs */
    CNAS_PRL_MCC_MNC_SUBTYPE_RESERVED                       = 4  /* Reserved */
};
typedef VOS_UINT32 CNAS_PRL_MCC_MNC_SUBTYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_PRL_PREF_NEG_SYS_ENUM
 结构说明  : Preferred/negative system

 1.日    期   : 2014年08月05日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_PREF_NEG_SYS_ENUM
{
    CNAS_PRL_PREF_NEG_SYS_NEG                               = 0, /* This field is set to '0' if the mobile station is
                                                                                    not allowed to operate on the system associated
                                                                                    with this record */
    CNAS_PRL_PREF_NEG_SYS_PREF                              = 1, /* This field is set to ‘1’ if the mobile station
                                                                                    is allowed to operate on the system associated with
                                                                                    this record */
    CNAS_PRL_PREF_NEG_SYS_BUTT
};
typedef VOS_UINT8 CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_GEO_REGION_IND_ENUM
 结构说明  : Geographical region indicator

 1.日    期   : 2014年08月05日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_GEO_REGION_IND_ENUM
{
    CNAS_PRL_GEO_REGION_IND_NEW                             = 0,    /* If this is the first system record, this field is set to ‘0’. */

    CNAS_PRL_GEO_REGION_IND_SAME                            = 1,    /* If this is not the first system record, then this field is set as
                                                                                        follows: If the system associated with this record is in the
                                                                                        same geographical region as the system associated with the
                                                                                        previous system record, this field is set to ‘1’; otherwise, this
                                                                                        field is set to ‘0’. */
    CNAS_PRL_GEO_REGION_IND_BUTT
};
typedef VOS_UINT8 CNAS_PRL_GEO_REGION_IND_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_RELATIVE_PRI_IND_ENUM
 结构说明  : Relative priority indicator

 1.日    期   : 2014年08月05日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_RELATIVE_PRI_IND_ENUM
{
    CNAS_PRL_RELATIVE_PRI_SAME                              = 0,    /* If this is the last system record in the specific geographical
                                                                                        region, or if the PREF_NEG field in the next system record is
                                                                                        equal to’0’, this field is set to ‘0’ and has no meaning. Or
                                                                                        If the system associated with this system record is as
                                                                                        desirable as the system associated with the next system
                                                                                        record, this field is set to ‘0’. */

    CNAS_PRL_RELATIVE_PRI_MORE                              = 1,    /* If the system associated with this system record is more
                                                                                        desirable than the system associated with the next system
                                                                                        record, this field is set to ‘1’. */

    CNAS_PRL_RELATIVE_PRI_BUTT
};
typedef VOS_UINT8 CNAS_PRL_RELATIVE_PRI_IND_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_SYS_RECORD_TYPE_ENUM
 结构说明  : Extended System Record Type. This field is set to the type of this
             Extended System Record. (参考3GPP2 C.S0016-D中Table Table 3.5.5.3.2-1 )

 1.日    期   : 2014年08月05日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SYS_RECORD_TYPE_ENUM
{
    CNAS_PRL_SYS_RECORD_TYPE_1X_IS95                        = 0,    /* cdma2000 1x and IS-95 Systems */

    CNAS_PRL_SYS_RECORD_TYPE_HRPD                           = 1,    /* HRPD System */

    CNAS_PRL_SYS_RECORD_TYPE_RESERVED                       = 2,    /* Reserved for Obsolete Identification */

    CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED                  = 3,    /* MCC-MNC based System Record */

    CNAS_PRL_SYS_RECORD_TYPE_OTHER_RESERVED                 = 4     /* Reserved */
};
typedef VOS_UINT8 CNAS_PRL_SYS_RECORD_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_PARSE_CAUSE_ENUM
 结构说明  : PRL解析cause值

 1.日    期   : 2014年08月05日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_PARSE_CAUSE_ENUM
{
    CNAS_PRL_PARSE_SUCCESS                                  = 0,    /* PRL parse success */

    CNAS_PRL_PARSE_CRC_FAIL                                 = 1,    /* PRL CRC校验失败 */

    CNAS_PRL_PARSE_INVALID_LIST_SIZE                        = 2,    /* PR_LIST_SIZE无效 */

    CNAS_PRL_PARSE_VERSION_MISMATCH                         = 3,    /* PR 版本不匹配 */

    CNAS_PRL_PARSE_HEADER_FAIL                              = 4,    /* PRL头解析失败 */

    CNAS_PRL_PARSE_ACQ_RECORD_FAIL                          = 5,    /* PRL捕获记录解析失败 */

    CNAS_PRL_PARSE_SYS_RECORD_FAIL                          = 6,    /* PRL系统记录解析失败 */

    CNAS_PRL_PARSE_SUBNET_COMM_FAIL                         = 7,    /* PRL系统记录解析失败 */

    CNAS_PRL_PARSE_BUTT
};
typedef VOS_UINT32 CNAS_PRL_PARSE_CAUSE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM
 结构说明  : BAND SUBCLASS TYPE

 1.日    期   : 2014年08月07日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM
{
    CNAS_PRL_BAND_SUBCLASS_TYPE_0                           = 0,
    CNAS_PRL_BAND_SUBCLASS_TYPE_1                           = 1,
    CNAS_PRL_BAND_SUBCLASS_TYPE_2                           = 2,
    CNAS_PRL_BAND_SUBCLASS_TYPE_3                           = 3,
    CNAS_PRL_BAND_SUBCLASS_TYPE_4                           = 4,

    CNAS_PRL_BAND_SUBCLASS_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_BAND_CLASS_ENUM
 结构说明  : List of Band Classes (参考3GPP2 C.S0057-E中Table 1.5-1: )

 1.日    期   : 2014年08月06日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_BAND_CLASS_ENUM
{
    CNAS_PRL_BAND_CLASS_TYPE_0                              = 0,    /* 800 MHz cellular band */

    CNAS_PRL_BAND_CLASS_TYPE_1                              = 1,    /* 1.8 to 2.0 GHz PCS band */

    CNAS_PRL_BAND_CLASS_TYPE_2                              = 2,    /* 872 to 960 MHz TACS band */

    CNAS_PRL_BAND_CLASS_TYPE_3                              = 3,    /* 832 to 925 MHz JTACS band */

    CNAS_PRL_BAND_CLASS_TYPE_4                              = 4,    /* 1.75 to 1.87 GHz Korean PCS band */

    CNAS_PRL_BAND_CLASS_TYPE_5                              = 5,    /* 450 MHz NMT band */

    CNAS_PRL_BAND_CLASS_TYPE_6                              = 6,    /* 2 GHz IMT-2000 band */

    CNAS_PRL_BAND_CLASS_TYPE_7                              = 7,    /* 700 MHz band */

    CNAS_PRL_BAND_CLASS_TYPE_8                              = 8,    /* 1800 MHz band */

    CNAS_PRL_BAND_CLASS_TYPE_9                              = 9,    /* 900 MHz band */

    CNAS_PRL_BAND_CLASS_TYPE_10                             = 10,   /* Secondary 800 MHz band */

    CNAS_PRL_BAND_CLASS_TYPE_11                             = 11,   /* 400 MHz European PAMR band */

    CNAS_PRL_BAND_CLASS_TYPE_12                             = 12,   /* 800 MHz PAMR band */

    CNAS_PRL_BAND_CLASS_TYPE_13                             = 13,   /* 2.5 GHz IMT-2000 Extension Band */

    CNAS_PRL_BAND_CLASS_TYPE_14                             = 14,   /* US PCS 1.9GHz Band */

    CNAS_PRL_BAND_CLASS_TYPE_15                             = 15,   /* AWS Band */

    CNAS_PRL_BAND_CLASS_TYPE_16                             = 16,   /* US 2.5GHz Band */

    CNAS_PRL_BAND_CLASS_TYPE_17                             = 17,   /* US 2.5GHz Forward Link Only Band */

    CNAS_PRL_BAND_CLASS_TYPE_18                             = 18,   /* 700 MHz Public Safety Band */

    CNAS_PRL_BAND_CLASS_TYPE_19                             = 19,   /* Lower 700 MHz Band */

    CNAS_PRL_BAND_CLASS_TYPE_20                             = 20,   /* L-Band */

    CNAS_PRL_BAND_CLASS_TYPE_21                             = 21,   /* S-Band */

    CNAS_PRL_BAND_CLASS_TYPE_31                             = 31,   /* Wildcard Band Class */

    CNAS_PRL_BAND_CLASS_BUTT
};
typedef VOS_UINT16 CNAS_PRL_BAND_CLASS_ENUM_UINT16;

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
/*****************************************************************************
 结构名    : CNAS_PRL_FREQENCY_CHANNEL_STRU
 结构说明  : 频段和频点信息
   1.日    期   : 2013年8月6日
    作    者   : h00246512
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_PRL_BAND_CLASS_ENUM_UINT16                         enBandClass;
    VOS_UINT16                                              usChannel;
}CNAS_PRL_FREQENCY_CHANNEL_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_1X_SYSTEM_STRU
 结构说明  : CDMA 1x系统数据结构
  1.日    期   : 2014年08月02日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;
}CNAS_PRL_1X_SYSTEM_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_1X_SYSTEM_ID_STRU
 结构说明  : CDMA 1x系统ID数据结构
  1.日    期   : 2014年08月16日
    作    者   : l60609
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
}CNAS_PRL_1X_SYSTEM_ID_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_HDR_SYS_TYPE_STRU
 结构说明  : EVDO系统数据结构
  1.日    期   : 2014年08月02日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usBand;
    VOS_UINT16                                              usChan;
    VOS_UINT8                                               aucSubNet[6];
    VOS_UINT8                                               aucResvered[2];
}CNAS_PRL_HDR_SYS_TYPE_STRU;


/*****************************************************************************
 结构名    : CNAS_PRL_PRL_HEADER_INFO_STRU
 结构说明  : PRL头信息数据结构(见3GPP2 C.S0016-D 3.5.5 Preferred Roaming List
             and Extended Preferred Roaming List)

  1.日    期   : 2014年08月02日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrListSize;
    VOS_UINT16                                              usPrListId;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8                          enSsprPRev;
    VOS_UINT8                                               ucPreferOnly;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enDefRoamInd;
    VOS_UINT8                                               aucReserved0[1];
    VOS_UINT16                                              usNumAcqRecs;
    VOS_UINT16                                              usNumSubnetRecs;
    VOS_UINT16                                              usNumSysRecs;
    VOS_UINT16                                              usAcqTabBitOffset;
    VOS_UINT32                                              ulComSubnetBitOffset;
    VOS_UINT32                                              ulComSubnetBitSize;
}CNAS_PRL_HEADER_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_JTACS_CDMA_SYS_ACQ_STANDARD_RECORD_STRU
 结构说明  : Cellular CDMA and JTACS CDMA System Acquisition (Standard Channels)
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.1.2)

  1.日    期   : 2014年08月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8                        enSysSelType;

    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType;

    VOS_UINT8                                               aucResvered[2];
}CNAS_PRL_JTACS_CDMA_SYS_ACQ_STANDARD_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU
 结构说明  : Cellular CDMA and JTACS CDMA System Acquisition (Standard Channels)
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.1.2)，解析存储共用该数据
             结构
  1.日    期   : 2014年08月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8                        enSysSelType;

    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType;

    VOS_UINT8                                               aucResvered[2];
}CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU
 结构说明  : 存放Cellular CDMA and JTACS CDMA System Acquisition (Custom Channels)
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.1.3)
  1.日    期   : 2014年08月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;   /* channel个数 */
    VOS_UINT8                                               aucResvered[3];

    VOS_UINT16                                              ausChan[0];        /* 存放channel首地址 */
}CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_JTACS_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU
 结构说明  : Cellular CDMA and JTACS CDMA System Acquisition (Custom Channels)
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.1.3)
  1.日    期   : 2014年08月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;   /* channel数目 */
    VOS_UINT8                                               aucResvered[3];

    VOS_UINT16                                              ausChan[0];  /* channel指针 */
}CNAS_PRL_JTACS_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_CELLUAR_CDMA_PREFERRED_SYS_ACQ_RECORD_STRU
 结构说明  : Cellular CDMA Preferred System Acquisition Record数据结构
             (见3GPP2 C.S0016-D 3.5.5.2.1.4)

  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8                        enSysSelType;

    VOS_UINT8                                               aucResvered[3];

}CNAS_PRL_CELLUAR_CDMA_PREFERRED_SYS_ACQ_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_STRU
 结构说明  : PCS CDMA System Acquisition (Using Blocks) Record数据结构
             (见3GPP2 C.S0016-D 3.5.5.2.1.5)，用于存储使用

  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfBlocks;   /* block数目 */
    VOS_UINT8                                               aucResvered[3];

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM_UINT8            aenBlock[0];        /* block指针 */

}CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_PCS_CDMA_SYS_ACQ_CHANNELS_STRU
 结构说明  : PCS CDMA and 2 GHz Band CDMA System Acquisition (Using Channels)
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.1.6)
  1.日    期   : 2014年08月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;   /* channel数目 */
    VOS_UINT8                                               aucResvered[3];

    VOS_UINT16                                              ausChan[0];        /* channel指针 */
}CNAS_PRL_PCS_CDMA_SYS_ACQ_CHANNELS_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_2GHZ_BAND_CDMA_SYS_ACQ_CHANNELS_STRU
 结构说明  : PCS CDMA and 2 GHz Band CDMA System Acquisition (Using Channels)
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.1.6)
  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;   /* channel数目 */
    VOS_UINT8                                               aucResvered[3];

    VOS_UINT16                                              ausChan[0];        /* channel指针 */
}CNAS_PRL_2GHZ_BAND_CDMA_SYS_ACQ_CHANNELS_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_STRU
 结构说明  : Generic Acquisition Record for cdma2000 1x and IS-95
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.2.10)
  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;
    VOS_UINT8                                               aucReseved[3];

    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[0];        /* band + channel */

}CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_SYS_TYPE_1X_IS95_ID_STRU
 结构说明  : 1X and IS95 system ID record数据结构(见3GPP2 C.S0016-D Table 3.5.5.3.2-2)

  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_NID_INCL_TYPE_ENUM_UINT8                       enNidIncl;          /* NID included */
    VOS_UINT8                                               aucReseved[3];
    VOS_UINT16                                              usSid;              /* System identification */
    VOS_UINT16                                              usNid;              /* Network identification */
}CNAS_PRL_SYS_TYPE_1X_IS95_ID_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_EVDO_SYSTEM_STRU
 结构说明  : CDMA EVDO系统数据结构
  1.日    期   : 2014年12月10日
    作    者   : C00299064
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucSubnet[CNAS_PRL_BYTES_IN_SUBNET];
    VOS_UINT8                                               ucSubnetMask;
    VOS_UINT8                                               aucRcv[3];
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;
}CNAS_PRL_HRPD_SYSTEM_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_COMM_SUBNET_INFO_STRU
 结构说明  : Common Subnet Table for the HRPD Extended System Record(见3GPP2 C.S0016-D Table 3.5.5.3.2.1-1 Common Subnet Record)

  1.日    期   : 2014年12月01日
    作    者   : d00212987
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                              aucResvered[2];
    VOS_UINT8                                              ucSubnetCommLen;
    VOS_UINT8                                              aucSubnetComm[1];
}CNAS_PRL_COMM_SUBNET_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_GENERIC_ACQ_FOR_HRPD_STRU
 结构说明  : Generic Acquisition Record for HRPD
             Record数据结构(见3.5.5.2.2.11 )
  1.日    期   : 2014年12月01日
    作    者   : d00212987
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;
    VOS_UINT8                                               aucReseved[3];
    /*保持风格统一*/
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[0];        /* band + channel */

}CNAS_PRL_GENERIC_ACQ_FOR_HRPD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_SYS_TYPE_HRPD_ID_STRU
 结构说明  : HRPD System 数据结构(见3GPP2 C.S0016-D Table 3.5.5.3.2-4)

  1.日    期   : 2014年08月05日
    作    者   : d00212987
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucSubnetBitLen;
    VOS_UINT8                                               ucSubnetCommInc;
    VOS_UINT8                                               ucSubnetLsbLen;
    VOS_UINT8                                               ucSubnetCommLen;
    VOS_UINT8                                               aucSubnet[CNAS_PRL_BYTES_IN_SUBNET];
}CNAS_PRL_SYS_TYPE_HRPD_ID_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU
 结构说明  : Type-specific System ID Record of type ‘0011’数据结构(见3GPP2 C.S0016-D 3.5.5.3.2.2 )

  1.日    期   : 2014年08月05日
    作    者   : d00212987
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucSidNidNum;                        /* SID NID mum */
    VOS_UINT8                               aucResvered[3];
    VOS_UINT16                              asSid[CNAS_PRL_MCC_MNC_SID_MAX_NUM];/* System ID*/
    VOS_UINT16                              asNid[CNAS_PRL_MCC_MNC_NID_MAX_NUM];/* NetWork ID*/

}CNAS_PRL_SYS_TYPE_SID_NID_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU
 结构说明  : Type-specific System ID Record of type ‘0011’数据结构(见3GPP2 C.S0016-D 3.5.5.3.2.2 )

  1.日    期   : 2014年08月05日
    作    者   : d00212987
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucSubnetNum;
    VOS_UINT8                               aucResvered[3];
    VOS_UINT8                               aucSubnetLen[CNAS_PRL_MCC_MNC_SUBNET_MAX_NUM];
    VOS_UINT8                               aucSubnetID[CNAS_PRL_MCC_MNC_SUBNET_MAX_NUM][CNAS_PRL_MCC_MNC_SUBNET_MAX_LEN];

}CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU
 结构说明  : Type-specific System ID Record of type ‘0011’数据结构(见3GPP2 C.S0016-D 3.5.5.3.2.2 )

  1.日    期   : 2014年08月05日
    作    者   : d00212987
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_MCC_MNC_SUBTYPE_ENUM_UINT32                    enMccMncSubType;    /* mcc mnc sub type included */
    VOS_UINT16                                              usMcc;              /* Mobile Country Code */
    VOS_UINT16                                              usMnc;              /* Mobile Network Code */
    union
    {
        CNAS_PRL_SYS_TYPE_SID_NID_STRU                      stSidNid;

        CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU                   *pstSubnetId;

    }u;

}CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_ACQ_RECORD_STRU
 结构说明  : PRL捕获记录(acquire record)数据结构(见3GPP2 C.S0016-D  3.5.5.2 Acquisition Records)
  1.日    期   : 2014年08月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8                                enAcqType;
    VOS_UINT8                                                   ucAcqValid;      /* 标识该条acq记录是否有效。
                                                                                    ucAcqValid = 1 有效
                                                                                    ucAcqValid = 0 无效 */
    VOS_UINT8                                                   aucResvered[2];

    union
    {
        CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU     stCellularStandardSys;
        CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU       stCelluarCustomSys;
        CNAS_PRL_JTACS_CDMA_SYS_ACQ_STANDARD_RECORD_STRU        stJtacsStandardSys;
        CNAS_PRL_JTACS_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU          stJtacsCustomSys;
        CNAS_PRL_CELLUAR_CDMA_PREFERRED_SYS_ACQ_RECORD_STRU     stCellularPreSys;
        CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_STRU            stPcsBlocksSys;
        CNAS_PRL_PCS_CDMA_SYS_ACQ_CHANNELS_STRU                 stPcsChannelsSys;
        CNAS_PRL_2GHZ_BAND_CDMA_SYS_ACQ_CHANNELS_STRU           st2GhzChannelSys;
        CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_STRU               st1xAndIs95Sys;
        CNAS_PRL_GENERIC_ACQ_FOR_HRPD_STRU                      stHrpdSys;
    }u;

}CNAS_PRL_ACQ_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_EXT_SYS_RECORD_STRU
 结构说明  : PRL系统表记录(extended system record)数据结构(见3GPP2 C.S0016-D  3.5.5.3.2 Extended System Record Format)
  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_SYS_RECORD_TYPE_ENUM_UINT8                     enRecordType;       /* SYS_RECORD_TYPE */
    CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8                        enPrefNegSys;       /* Preferred/negative system */
    CNAS_PRL_GEO_REGION_IND_ENUM_UINT8                      enGeoInd;           /* Geographical region indicator */
    CNAS_PRL_RELATIVE_PRI_IND_ENUM_UINT8                    enPriInd;           /* Relative priority indicator */
    VOS_UINT16                                              usAcqIndex;         /* Acquisition record index */
    VOS_UINT8                                               ucSysRecValid;      /* 标识该条系统记录是否有效。
                                                                                   ucSysRecValid = 1 有效
                                                                                   ucSysRecValid = 0 无效 */
    VOS_UINT8                                               aucReserved0[1];
    union
    {
        CNAS_PRL_SYS_TYPE_1X_IS95_ID_STRU                   st1xAndIs95Id;
        CNAS_PRL_SYS_TYPE_HRPD_ID_STRU                      stIs856Id;
        CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU                   stMccMncId;
    }u;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enRoamingInd;       /* If the PREF_NEG field of this record is equal to ‘1’, this field is
                                                                                                        included and is set to the roaming indication value for the system
                                                                                                        associated with this record; otherwise, this field is omitted. */
    VOS_UINT8                                               ucAssociationIncl;  /* Association tag included flag */
    VOS_UINT8                                               ucAssociationTag;   /* If included, this field is set to 1 the 8-bit number that specifies
                                                                                                       the set to which this system record belongs. The value of the
                                                                                                       ASSOCIATION_TAG field is only unique within a GEO. The
                                                                                                       set is defined as a set of systems (specified by the system
                                                                                                       records) for which at least one the following two conditions
                                                                                                       hold:
                                                                                                       The members of the set have the same PN offset assignment (i.e., collocated), or
                                                                                                       The members of the set can reach the same set of PDSNs (i.e., associated). */
    VOS_UINT8                                               ucPnAssociation;    /* PN association flag.
                                                                                                       This field is only included if the ASSOCIATION_INC field is set
                                                                                                       to ‘1’. If included, this field shall be set to ‘1’ if the system
                                                                                                       identified by this system record has the same PN assignment
                                                                                                       as other systems in the same GEO that are members of the
                                                                                                       set identified by ASSOCIATION_TAG and whose
                                                                                                       PN_ASSOCIATION field is also set to ‘1’. Otherwise, this field
                                                                                                       shall be set to ‘0’.*/
    VOS_UINT8                                               ucDataAssociation;  /* Data association flag.
                                                                                                       This field is only included if the ASSOCIATION_INC field is set
                                                                                                       to ‘1’. If included, this field shall be set to ‘1’ if the system
                                                                                                       identified by this system record can reach the same set of
                                                                                                       PDSNs as other systems in the same GEO that are members
                                                                                                       of the set identified by ASSOCIATION_TAG and whose
                                                                                                       DATA_ASSOCIATION field is also set to ‘1’. Otherwise, this
                                                                                                       field shall be set to ‘0’. */

    VOS_UINT8                                               aucReserved1[1];
    VOS_UINT16                                              usPriLvl;
}CNAS_PRL_EXT_SYS_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_ACQ_RECORD_INFO_STRU
 结构说明  : PRL获取表信息数据结构
  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usAcqRecordNum;
    VOS_UINT8                                               ucReserved[2];
    CNAS_PRL_ACQ_RECORD_STRU                               *pastPrlAcqRecord[CNAS_PRL_ACQ_RECORD_MAX_NUM];

}CNAS_PRL_ACQ_RECORD_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_SYS_RECORD_INFO_STRU
 结构说明  : PRL系统表信息数据结构
  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSysRecordNum;
    VOS_UINT8                                               ucReserved[2];
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord;
}CNAS_PRL_SYS_RECORD_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_INFO_STRU
 结构说明  : PRL数据结构
  1.日    期   : 2014年08月05日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIsPrlValid;
    CNAS_PRL_HEADER_INFO_STRU                               stPrlHeader;
    CNAS_PRL_ACQ_RECORD_INFO_STRU                           stPrlAcqInfo;
    CNAS_PRL_SYS_RECORD_INFO_STRU                           stPrlSysInfo;
}CNAS_PRL_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_BANDCLASS0_SUBCLASS_CHAN_STRU
 结构说明  : bandclass0 subclass频点数据结构
  1.日    期   : 2014年08月07日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM_UINT8                  enSubclass;
    CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8                        enSysType;
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanType;
    VOS_UINT8                                               ucReseved0;
    VOS_UINT16                                              usChan;
    VOS_UINT16                                              usReseved1;
}CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU
 结构说明  : bandclass10 subclass频点数据结构
  1.日    期   : 2015年07月07日
    作    者   : h00313353
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM_UINT8                  enSubclass;
    CNAS_PRL_BAND10_SYS_SEL_TYPE_ENUM_UINT8                 enSysType;
    VOS_UINT16                                              usChan;
} CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_PARSE_ACQ_TYPE_REC_PROC_FUNC_PTR
 结构说明  : 处理不同获取表类型的解析函数指针
  1.日    期   : 2013年8月6日
   作    者   : h00246512
   修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT32 (*CNAS_PRL_PARSE_ACQ_TYPE_REC_PROC_FUNC_PTR)(
    VOS_UINT8                                              *pucSrc,
    VOS_UINT32                                              ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU                              **pstPrlAcqRecord,
    VOS_UINT32                                             *pulCurOffsetPos
);

/*****************************************************************************
 结构名    : CNAS_PARSE_ACQ_TYPE_REC_PROC_ENTITY
 结构说明  : 捕获记录类型(acquire record type)，处理实体
   1.日    期   : 2013年8月6日
    作    者   : h00246512
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              enAcqType;
    CNAS_PRL_PARSE_ACQ_TYPE_REC_PROC_FUNC_PTR               pParseAcqTypeRecProcFunc;
}CNAS_PARSE_ACQ_TYPE_REC_PROC_ENTITY;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_CheckPrlCrcChecksum(
    VOS_UINT8                          *pPrl
);

VOS_UINT8  CNAS_PRL_ExtractBitStringToOctet(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
);

VOS_UINT16 CNAS_PRL_ExtractBitStringToWord(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
);

CNAS_PRL_INFO_STRU* CNAS_PRL_GetPrlInfoAddr(VOS_VOID);

VOS_UINT32 CNAS_PRL_IsAcqRecTabValid(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqRecInfo
);

VOS_UINT32 CNAS_PRL_IsSysRecTabValid(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstSysRecInfo
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_2gBandUsingChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularAnalog(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaCustom(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaPrefered(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaStandard(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_GenericCdma1X(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_NotSupportRecType(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
VOS_UINT32 CNAS_PRL_ParseExAcqRecTbl(
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8        enAcqType,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
);
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlAcqRec(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulCurOffsetPos
);

VOS_VOID CNAS_PRL_ParsePrlCalcComSubnetBits(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usNumSubnetRecs,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulBitOffset
);

CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlHeader(
    VOS_UINT8                          *pucSrc,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
);
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlInfo(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
);
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlSysRec(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulCurOffsetPos
);

VOS_VOID CNAS_PRL_ParseSysIdRec_1X(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_1X_IS95_ID_STRU  *pst1xAndIs95Id,
    VOS_UINT32                         *pulCurOffsetPos
);

VOS_VOID CNAS_PRL_ParseSysIdRec_Is856(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_HRPD_ID_STRU     *pstIs586Id,
    VOS_UINT32                         *pulCurOffsetPos
);

VOS_UINT32 CNAS_PRL_ParseSysIdRec_Mcc(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU  *pstMccMncIdId,
    VOS_UINT32                         *pulCurOffsetPos
);

VOS_VOID CNAS_PRL_ParseSysRec_REV3(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRecord,
    VOS_UINT32                         *pulCurOffsetPos
);

VOS_VOID CNAS_PRL_ParseSysRec_REV1(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRecord,
    VOS_UINT32                         *pulCurOffsetPos
);

VOS_UINT32 CNAS_PRL_IsConcatenatedPrlProbable(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    VOS_UINT16                          usFirstPrlListSize
);

VOS_UINT32 CNAS_PRL_ParseEprlBitStream(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen
);

VOS_UINT32 CNAS_PRL_ParsePrlBitStream(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen
);


#endif

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

#endif /* end of __CNAS_PRL_PARSE_H__ */
