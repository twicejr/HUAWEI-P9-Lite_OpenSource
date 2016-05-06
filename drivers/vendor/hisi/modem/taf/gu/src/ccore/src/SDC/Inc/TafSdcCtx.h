/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSdcCtx.h
  版 本 号   : 初稿
  作    者   : s46746
  生成日期   : 2012年12月25日
  最近修改   :
  功能描述   : TafSdcCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月25日
    作    者   : s46746
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SDC_CTX_H_
#define _TAF_SDC_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "ComInterface.h"
#include  "errorlog.h"
#include  "NasErrorLog.h"
#include  "product_config.h"
#include  "NVIM_Interface.h"

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */
#include  "NasNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */

#include "omringbuffer.h"

#include "TafNvInterface.h"
#include "UsimPsInterface.h"

#include "NasMsccPifInterface.h"


#include "TafAppMma.h"
#include "NasOmTrans.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_SDC_PLATFORM_MAX_RAT_NUM                        (7)                 /* 平台支持的最大接入技术数目 */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
#if (FEATURE_ON == FEATURE_LTE)
#define TAF_SDC_MAX_RAT_NUM                             (3)                     /* 当前支持的接入技术个数 */
#else
#define TAF_SDC_MAX_RAT_NUM                             (2)                     /* 当前支持的GU接入技术个数 */
#endif

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-29, begin */
#define TAF_SDC_MAX_IMSI_LEN                                (9)                 /* IMSI的最大长度 */
#define TAF_SDC_IMSI_INVALID                                (0xFF)              /* IMSI的无效值的宏定义     */
#define TAF_SDC_INVALID_MCC                                 (0xFFFFFFFF)        /* MCC的无效值 */
#define TAF_SDC_INVALID_MNC                                 (0xFFFFFFFF)        /* MNC的无效值 */
#define TAF_SDC_RAC_INVALID                                 (0xFF)              /* RAC的为无效值 */
#define TAF_SDC_CELLID_INVALID                              (0xFFFFFFFF)
#define TAF_SDC_LAC_INVALID                                 (0xFFFF)
#define TAF_SDC_IMSI_INVALID                                (0xFF)                  /* IMSI的无效值的宏定义     */

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-29, end */

#define TAF_SDC_SIM_FORMAT_PLMN_LEN                         (3)                 /* SIM卡中PLMN ID的长度 */

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
#define TAF_SDC_RPT_CFG_MAX_SIZE                            (8)                 /* 主动上报标识最大的长度 */
#define TAF_SDC_MAX_SIGN_THRESHOLD                          (5)                 /* RSSI/CERSSI最大上报门限值:5DB */

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

#define TAF_SDC_ASCII2BCDLENGTH(ulAsciiLength)              ((ulAsciiLength + 1) / 2)
#define TAF_SDC_BITS_PER_OCTET                              (8)
#define TAF_SDC_BITS_PER_SEPTET                             (7)
#define TAF_SDC_USSD_7BIT_PAD                               (0x1a)

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
#define TAF_SDC_EMER_NUM_MAX_LENGTH                         (46)                             /* Emergency Number information的最大字节数 */
#define TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER                   (16)
#define TAF_SDC_NUMOF_EMER_NUMS_NO_USIM                     (8)
#define TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM                   (2)
#define TAF_SDC_MAX_CUSTOM_ECC_NUM                          (20)                             /* 用户定制的紧急呼号码最大条数 */
#define TAF_SDC_MAX_BCD_NUM_LEN                             (20)                             /* 该宏定义的取值与MN_CALL_MAX_BCD_NUM_LEN的取值保持一致 */
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */


/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
#define TAF_SDC_ECALL_BCD_NUM_MAX_LEN                        (20)
/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */

#define TAF_SDC_SRV_TYPE_CS_MO_NORMAL_CALL                   (0x1)
#define TAF_SDC_SRV_TYPE_CS_MO_EMERGENCY_CALL                (0x2)
#define TAF_SDC_SRV_TYPE_CS_MO_SS                            (0x4)
#define TAF_SDC_SRV_TYPE_CS_MO_SMS                           (0x8)
#define TAF_SDC_SRV_TYPE_PS_CONVERSAT_CALL                   (0x10)
#define TAF_SDC_SRV_TYPE_PS_STREAM_CALL                      (0x20)
#define TAF_SDC_SRV_TYPE_PS_INTERACT_CALL                    (0x40)
#define TAF_SDC_SRV_TYPE_PS_BACKGROUND_CALL                  (0x80)
#define TAF_SDC_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL            (0x100)


#define TAF_SDC_MAX_UCIM_ECC_NUM                              (5)                             /* UIM或CSIM卡中最大的紧急呼叫号码条数 */

#define TAF_SDC_BLER_INVALID            (99)                                    /* 无效值 */
#define TAF_SDC_RSRP_UNVALID            (99)                                    /* 无效值 */
#define TAF_SDC_RSRQ_UNVALID            (99)                                    /* 无效值 */
#define TAF_SDC_UE_RFPOWER_INVALID      (0x1fff)                                /* 无效值 */
#define TAF_SDC_UE_FREQ_INVALID         (0xffff)                                /* UE FREQ的无效值 */
#define TAF_SDC_RSSI_UNVALID            (-140)                                  /* RSSI的无效值 */
#define TAF_SDC_RSSI_VALUE_UNVALID      (0)                                     /*已转换为等级表示的信号强度的无效值*/

#define TAF_SDC_CDMA_INVALID_RSSI_VALUE     (0x7FFF)
#define TAF_SDC_CDMA_INVALID_ECIO_VALUE     (0x7FFF)
#define TAF_SDC_HRPD_INVALID_RSSI_VALUE     (0x7FFF)
#define TAF_SDC_HRPD_INVALID_SNR_VALUE      (0x7FFF)
#define TAF_SDC_HRPD_INVALID_ECIO_VALUE     (0x7FFF)

#define TAF_SDC_OPL_MAX_RECORD_NUM                           (60)
#define TAF_SDC_PNN_MAX_RECORD_NUM                           (60)
#define TAF_SDC_MAX_OPER_NAME_NUM                            (100)
#define TAF_SDC_MAX_OPER_LONG_NAME_LEN                       (100)                    /* spn 采用ucs2编码时需要的长度为32，添加一个\0 对齐到36位,因为最大有39的long name ,调整到40*/
#define TAF_SDC_MAX_OPER_SHORT_NAME_LEN                      (100)                    /* spn 采用ucs2编码时需要的长度为32 ,添加一个\0 对齐到36位 */
#define TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM                (50)
#define TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN                 (50)
#define TAF_SDC_MAX_OPER_NAME_PRIO_NUM                       (4)
#define TAF_SDC_INVALID_PLMN_PNN_INDEX                       (0xFFFFFFFF)
#define TAF_SDC_VALID_PNN_LOW_INDEX                          (0x01)
#define TAF_SDC_VALID_PNN_HIGH_INDEX                         (0xFE)
#define TAF_SDC_INVALID_PNN_INDEX                            (0xFF)
#define TAF_SDC_VALID_LAC_RANGE_LOW                          (0x0)
#define TAF_SDC_VALID_LAC_RANGE_HIGH                         (0xFFFE)

#define TAF_SDC_OCTET_LOW_FOUR_BITS                     (0x0f)                  /* 获取一个字节中的低4位 */
#define TAF_SDC_OCTET_HIGH_FOUR_BITS                    (0xf0)                  /* 获取一个字节中的高4位 */
#define TAF_SDC_OCTET_MOVE_FOUR_BITS                    (0x04)                  /* 将一个字节移动4位 */
#define TAF_SDC_OCTET_MOVE_EIGHT_BITS                   (0x08)                  /* 将一个字节移动8位 */
#define TAF_SDC_OCTET_MOVE_SEVEN_BITS                   (0x07)                  /* 将一个字节移动7位 */
#define TAF_SDC_OCTET_MOVE_TWELVE_BITS                  (0x0C)                  /* 将一个字节移动8位 */
#define TAF_SDC_OCTET_MOVE_SIXTEEN_BITS                 (0x10)                  /* 将一个字节移动16位 */
#define TAF_SDC_OCTET_MOVE_THREE_BYTES                  (0x03)                  /* 移动3个字节 */
#define TAF_SDC_OCTET_MOVE_FOUR_BYTES                   (0x04)                  /* 移动4个字节 */
#define TAF_SDC_OCTET_MOVE_FIVE_BYTES                   (0x05)                  /* 移动5个字节 */
#define TAF_SDC_OCTET_MOVE_SIX_BYTES                    (0x06)                  /* 移动6个字节 */
#define TAF_SDC_OCTET_MOVE_SEVEN_BYTES                  (0x07)                  /* 移动7个字节 */

#define TAF_SDC_OPL_BYTE_POSITION_OF_LAC_RANG_LOW       (0x03)                  /* OPL文件中第4,5字节表示LAC下限 */
#define TAF_SDC_OPL_BYTE_POSITION_OF_LAC_RANG_HIGHT     (0x05)                  /* OPL文件中第6,7字节表示LAC上限 */
#define TAF_SDC_OPL_BYTE_POSITION_OF_PNN_INDEX          (0x07)                  /* OPL文件中第8字节表示PLMN network name record Index */

#define TAF_SDC_PNN_CODING_SCHEME_BIT_MASK              (0x70)                  /* PNN文件中bit7-bit5表示coding scheme */
#define TAF_SDC_PNN_SPARE_BIT_MASK                      (0x07)                  /* PNN文件中bit3-bit1表示Number of spare bits */

#define TAF_SDC_SPN_DISPLAY_CONDITION_BIT_MASK          (0x03)                  /* 根据SPN bit1-bit2,是否显示SPN */
#define TAF_SDC_SPN_SPARE_BIT_MASK                      (0x07)                  /* SPN文件中bit3-bit1表示Number of spare bits */
#define TAF_SDC_SPN_UCS2_CODING_FORM1                   (0x80)                  /* SPN Byte1 是0x80,0x81,0x82时 表示UCS2编码 */
#define TAF_SDC_SPN_UCS2_CODING_FORM2                   (0x81)                  /* SPN Byte1 是0x80,0x81,0x82时 表示UCS2编码 */
#define TAF_SDC_SPN_UCS2_CODING_FORM3                   (0x82)                  /* SPN Byte1 是0x80,0x81,0x82时 表示UCS2编码 */

#define TAF_SDC_PLMN_MCC_LEN                             (3)                     /* PLMN 中的MCC的长度 */
#define TAF_SDC_PLMN_MNC_LEN                             (3)                     /* PLMN 中的MNC的长度 */
#define TAF_SDC_MCC_MNC_BYTE_VALUE_MASK                  (0x000000FF)

#define TAF_SDC_MCC_LOW_TWO_BYTE_VALUE_MASK              (0x0000FFFF)
#define TAF_SDC_MCC_THIRD_BYTE_VALUE_MASK                (0x00FF0000)
#define TAF_SDC_PCS1900_MCC_LOW_VALUE                    (0x00000103)
#define TAF_SDC_PCS1900_MCC_HIGH_VALUE_RANGE             (0x00060000)
#define TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_0           (0x00)
#define TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_F           (0x0F)

#define TAF_SDC_LOW_BYTE_INVALID                         (0x0F)

#define TAF_SDC_MAX_DIGIT_VALUE                         (9)
#define NAS_SDC_ONE_THOUSAND_MILLISECOND                (1000)                  /* 1000MS */
#define NAS_MML_SIXTY_SECOND                            (60)                    /* 60秒 */


#define TAF_SDC_GET_STK_MCC(NUM)        (100 * ((NUM  % 1000 / 100 + 9) % 10) \
                                        + 10* ((NUM % 100 / 10 + 9) % 10) \
                                        + (NUM % 10 + 9) %10)

#define TAF_SDC_GET_STK_MNC(NUM)        (10* ((NUM % 100 / 10 + 9) % 10) \
                                        + (NUM % 10 + 9) %10)

#define TAF_SDC_ICC_ID_MAX_NUM                          (10)
#define TAF_SDC_MAX_EHPLMN_NUM                          (16)
#define TAF_SDC_MNC_LENGTH_TWO_BYTES_IN_IMSI            (2)

#if (FEATURE_ON == FEATURE_CSG)
#define TAF_SDC_MAX_HOME_NODEB_NAME_LEN         (48)
#define TAF_SDC_MAX_CSG_ID_LIST_NUM             (35)
#else
#define TAF_SDC_MAX_HOME_NODEB_NAME_LEN         (4)
#define TAF_SDC_MAX_CSG_ID_LIST_NUM             (1)
#endif

#define TAF_SDC_INVALID_CSG_ID_VALUE            (0xFFFFFFFF)

#define TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT                (8)
#define TAF_SDC_EFIMSI_OCTET_LEN_EIGHT          (10)
#define TAF_SDC_MOVEMENT_28_BITS                (28UL)
#define TAF_SDC_MOVEMENT_24_BITS                (24UL)
#define TAF_SDC_MOVEMENT_20_BITS                (20UL)
#define TAF_SDC_MOVEMENT_16_BITS                (16UL)
#define TAF_SDC_MOVEMENT_12_BITS                (12UL)
#define TAF_SDC_MOVEMENT_8_BITS                 (8UL)
#define TAF_SDC_MOVEMENT_4_BITS                 (4UL)

#define TAF_SDC_NUMOF_CDMA_PRESET_EMC_NUM       (6)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_SDC_USSD_TRAN_MODE_ENUM
 枚举说明  : USSD的传输模式
 1.日    期   : 2013年5月17日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_USSD_TRAN_MODE_ENUM
{
    TAF_SDC_USSD_NON_TRAN_MODE,                                     /* 非透传:单板支持编解码 */
    TAF_SDC_USSD_TRAN_MODE,                                         /* 透传:  单板不编解码，只是透传，由后台来编解码 */
    TAF_SDC_USSD_TRAN_MODE_BUTT
};
typedef VOS_UINT8 TAF_SDC_USSD_TRAN_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_ENUM
 枚举说明  : ALPHA转换为ascii的转换表类型
 1.日    期   : 2013年5月17日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_ENUM
{
    TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_DEF   = 0X0,                          /* 默认的字符表转换，*/
    TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME,                                  /* TEM字符表转换*/
    TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_BUTT
};
typedef VOS_UINT8 TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_PLATFORM_RAT_TYPE_ENUM
 枚举说明  : 平台接入技术类型
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新建
 2.日    期   : 2014年07月08日
   作    者   : y00245242
   修改内容   : 为1X feature开发增加
*****************************************************************************/
enum TAF_SDC_PLATFORM_RAT_TYPE_ENUM
{
    TAF_SDC_PLATFORM_RAT_GSM   = 0X0,
    TAF_SDC_PLATFORM_RAT_WCDMA,
    TAF_SDC_PLATFORM_RAT_LTE,
    TAF_SDC_PLATFORM_RAT_TDS,
    TAF_SDC_PLATFORM_RAT_1X,
    TAF_SDC_PLATFORM_RAT_HRPD,
    TAF_SDC_PLATFORM_RAT_EHRPD,
    TAF_SDC_PLATFORM_RAT_BUTT
};
typedef VOS_UINT8 TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8
 结构说明  : 初始化SDC CTX信息类型
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_INIT_CTX_TYPE_ENUM
{
    TAF_SDC_INIT_CTX_STARTUP                    = 0,
    TAF_SDC_INIT_CTX_POWEROFF                   = 1,
    TAF_SDC_INIT_CTX_BUTT
};
typedef VOS_UINT8 TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8;

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-29, begin */

/*****************************************************************************
 枚举名    : TAF_SDC_SYS_SUBMODE_ENUM_UINT8
 结构说明  : 驻留网络的系统子模式枚举
 1.日    期   : 2013年3月22日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核项目mma部分全局变量调整对应原ucSysSubMode
*****************************************************************************/
enum TAF_SDC_SYS_SUBMODE_ENUM
{
    TAF_SDC_SYS_SUBMODE_NONE                = 0,                                /* 无服务 */
    TAF_SDC_SYS_SUBMODE_GSM                 = 1,                                /* GSM模式 */
    TAF_SDC_SYS_SUBMODE_GPRS                = 2,                                /* GPRS模式 */
    TAF_SDC_SYS_SUBMODE_EDGE                = 3,                                /* EDGE模式 */
    TAF_SDC_SYS_SUBMODE_WCDMA               = 4,                                /* WCDMA模式 */
    TAF_SDC_SYS_SUBMODE_HSDPA               = 5,                                /* HSDPA模式 */
    TAF_SDC_SYS_SUBMODE_HSUPA               = 6,                                /* HSUPA模式 */
    TAF_SDC_SYS_SUBMODE_HSDPA_HSUPA         = 7,                                /* HSDPA+HSUPA模式 */
    TAF_SDC_SYS_SUBMODE_TD_SCDMA            = 8,                                /* TD_SCDMA模式 */
    TAF_SDC_SYS_SUBMODE_HSPA_PLUS           = 9,                                /* HSPA+模式 */
    TAF_SDC_SYS_SUBMODE_LTE                 = 10,                               /* LTE模式 */
    TAF_SDC_SYS_SUBMODE_DC_HSPA_PLUS        = 17,                               /* DC-HSPA+模式 */
    TAF_SDC_SYS_SUBMODE_DC_MIMO             = 18,                               /* MIMO-HSPA+模式 */

    TAF_SDC_SYS_SUBMODE_CDMA_1X             = 23,                               /* CDMA2000 1X*/
    TAF_SDC_SYS_SUBMODE_EVDO_REL_0          = 24,                               /* EVDO Rel0*/
    TAF_SDC_SYS_SUBMODE_EVDO_REL_A          = 25,                               /* EVDO RelA*/
    TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0   = 28,                               /* Hybrid(EVDO Rel0)*/
    TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A   = 29,                               /* Hybrid(EVDO RelA)*/

    TAF_SDC_SYS_SUBMODE_EHRPD               = 31,                               /* EHRPD模式*/

    TAF_SDC_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  TAF_SDC_SYS_SUBMODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_SDC_SYS_MODE_ENUM_UINT8
 结构说明  : 驻留网络的系统模式枚举
 1.日    期   : 2013年3月22日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核项目mma部分全局变量调整对应原ucCurRaForSysInfo
*****************************************************************************/
enum TAF_SDC_SYS_MODE_ENUM
{
    TAF_SDC_SYS_MODE_GSM,
    TAF_SDC_SYS_MODE_WCDMA,
    TAF_SDC_SYS_MODE_LTE,

    TAF_SDC_SYS_MODE_CDMA_1X,
    TAF_SDC_SYS_MODE_EVDO,
    TAF_SDC_SYS_MODE_HYBRID,
    TAF_SDC_SYS_MODE_SVLTE,

    TAF_SDC_SYS_MODE_BUTT
};
typedef VOS_UINT8  TAF_SDC_SYS_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8
 结构说明  : cops设置显示类型
 1.日    期   : 2015年2月12日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
enum TAF_SDC_COPS_FORMAT_TYPE_ENUM
{
    TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH,          /* cops设置显示长字符串运营商名称*/
    TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH,         /* cops设置显示短字符串运营商名称*/
    TAF_SDC_COPS_FORMAT_TYPE_NUMERIC,            /* cops设置显示数字格式运营商名称   */
    TAF_SDC_COPS_FORMAT_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_FILE_TYPE_ENUM_UINT8
 结构说明  : 文件类型
 1.日    期   : 2015年2月12日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
enum TAF_SDC_FILE_TYPE_ENUM
{
    TAF_SDC_FILE_TYPE_SIM = 1,
    TAF_SDC_FILE_TYPE_USIM,
    TAF_SDC_FILE_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_FILE_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8
 结构说明  : 运营商名称类型
 1.日    期   : 2015年2月12日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
enum TAF_SDC_OPER_NAME_TYPE_ENUM
{
    TAF_SDC_OPER_NAME_TYPE_PNN = 1,
    TAF_SDC_OPER_NAME_TYPE_CPHS,
    TAF_SDC_OPER_NAME_TYPE_SPN,
    TAF_SDC_OPER_NAME_TYPE_MMINFO,
    TAF_SDC_OPER_NAME_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8;



/*****************************************************************************
 枚举名    : TAF_SDC_SERVICE_STATUS_ENUM_UINT8
 结构说明  : cs/ps域服务状态
 1.日    期: 2013年3月28日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum TAF_SDC_SERVICE_STATUS_ENUM
{
    TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* 正常服务 */
    TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* 限制服务 */
    TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* 有限制区域服务 */
    TAF_SDC_SERVICE_STATUS_NO_IMSI                  = 3,                        /* 无imsi */
    TAF_SDC_SERVICE_STATUS_NO_SERVICE               = 4,                        /* 无服务 */
    TAF_SDC_SERVICE_STATUS_NO_CHANGE                = 5,
    TAF_SDC_SERVICE_STATUS_DEEP_SLEEP               = 6,
    TAF_SDC_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SDC_SERVICE_STATUS_ENUM_UINT8;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
/*****************************************************************************
    枚举名    : TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM
    枚举说明  : ims的普通注册状态
*****************************************************************************/
enum TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM
{
    TAF_SDC_IMS_NORMAL_REG_STATUS_DEREG        = 0x00,
    TAF_SDC_IMS_NORMAL_REG_STATUS_DEREGING     = 0x01,
    TAF_SDC_IMS_NORMAL_REG_STATUS_REGING       = 0x02,
    TAF_SDC_IMS_NORMAL_REG_STATUS_REG          = 0x03,

    TAF_SDC_IMS_NORMAL_REG_STATUS_BUTT         = 0xFF
};
typedef VOS_UINT8 TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

/*****************************************************************************
 枚举名    : TAF_SDC_REPORT_SRVSTA_ENUM_UINT8
 结构说明  : ^srvst上报的ue的服务状态
 1.日    期: 2013年3月28日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum TAF_SDC_RPT_SRVSTA_ENUM
{
    TAF_SDC_REPORT_SRVSTA_NO_SERVICE               = 0,                         /* 无服务 */
    TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE          = 1,                         /* 限制服务 */
    TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE           = 2,                         /* 正常服务 */
    TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE = 3,                         /* 有限的区域服务 */
    TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP               = 4,                         /* 省电和深睡眠状态 */
    TAF_SDC_REPORT_SRVSTA_BUTT
};
typedef VOS_UINT8  TAF_SDC_REPORT_SRVSTA_ENUM_UINT8;


/******************************************************************************
结构名    : TAF_SDC_CELL_RESTRICTION_TYPE_ENUM_UINT8
结构说明  : 小区接入禁止信息枚举类型
1. 日    期: 2013年3月28日
   作    者: z00161729
   修改内容: 新建
******************************************************************************/
enum  TAF_SDC_CELL_RESTRICTION_TYPE_ENUM
{
    TAF_SDC_CELL_RESTRICTION_TYPE_NONE                   = 0,                   /* 当前小区不限制任何业务 */
    TAF_SDC_CELL_RESTRICTION_TYPE_NORMAL_SERVICE         = 1,                   /* 当前小区限制正常业务 */
    TAF_SDC_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE      = 2,                   /* 当前小区限制紧急业务 */
    TAF_SDC_CELL_RESTRICTION_TYPE_ALL_SERVICE            = 3,                   /* 当前小区限制正常业务和紧急业务 */
    TAF_SDC_CELL_RESTRICTION_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_CELL_RESTRICTION_TYPE_ENUM_UINT8;

/******************************************************************************
结构名    : TAF_SDC_USIM_STATUS_ENUM_UINT8
结构说明  : 卡状态 0：USIM卡状态无效；1:USIM卡状态有效；2：USIM在CS下无效
             3：USIM在PS下无效；4：USIM在PS+CS下均无效；255：USIM卡不存在
1. 日    期: 2013年3月28日
   作    者: z00161729
   修改内容: 新建

2. 日    期   : 2013年7月19日
   作    者   : w00167002
   修改内容   : DTS2013071900570:SVLTE特性开启时候，MODEM1解pin后，MODEM0收到
                卡状态为AVAILABLE时候，没有发起重启。原因在于:
                当前解PIN码之前，SDC中维护的卡状态为TAF_SDC_USIM_STATUS_VALID，
                MODEM在收到解PIN的RSP消息时候，才会将SDC的卡状态重新设置为TAF_SDC_USIM_STATUS_UNVALID
                ，这样再收到USIM上报的卡状态为AVAILABLE时候，会发起重启。
                修改为SDC存储SIM卡的原始状态，MODEM在收到解PIN的RSP消息时候,
                不需重新设置SIM状态为TAF_SDC_USIM_STATUS_UNVALID。MODEM的重启
                由SIM卡状态的变迁来决定。如:卡状态由SIM_PIN--->AVAIALBLE,则触发
                重启动。

 3.日    期   : 2014年2月27日
   作    者   : z00234330
   修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
                卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用
                at^cpin命令查询的会不正确。
******************************************************************************/
enum  TAF_SDC_USIM_STATUS_ENUM
{
    TAF_SDC_USIM_STATUS_UNVALID         = 0,                                    /* 初始化卡状态 */
    TAF_SDC_USIM_STATUS_VALID           = 1,                                    /* 卡存在且CS/PS卡都有效 */
    TAF_SDC_USIM_STATUS_CS_UNVALID      = 2,
    TAF_SDC_USIM_STATUS_PS_UNVALID      = 3,
    TAF_SDC_USIM_STATUS_CS_PS_UNVALID   = 4,
    TAF_SDC_USIM_STATUS_SIM_PIN         = 5,                                    /* SIM卡服务由于PIN码原因不可用 */
    TAF_SDC_USIM_STATUS_SIM_PUK         = 6,                                    /* SIM卡服务由于PUK码原因不可用 */
    TAF_SDC_USIM_STATUS_NET_LCOK        = 7,                                    /* SIM卡服务由于网络锁定原因不可用 */
    TAF_SDC_USIM_STATUS_IMSI_LCOK       = 8,                                    /* SIM卡服务由于IMSI锁定原因不可用 */

    TAF_SDC_USIM_STATUS_READY_TIMEROUT  = 9,                                    /* 等待usim定时器超时原因不可用 */

    TAF_SDC_USIM_STATUS_ROMSIM          = 240,
    TAF_SDC_USIM_STATUS_NO_PRESENT      = 255,
    TAF_SDC_USIM_STATUS_BUTT            = 254
};

typedef VOS_UINT8  TAF_SDC_USIM_STATUS_ENUM_UINT8;

/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
/*****************************************************************************
 枚举名    : TAF_SDC_SIM_TYPE_ENUM_UINT8
 枚举说明  : 当前SIM卡的类型,SIM卡或USIM卡
 1.日    期   : 2013年7月30日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_SIM_TYPE_ENUM
{
    TAF_SDC_SIM_TYPE_SIM                ,                   /* SIM卡 */
    TAF_SDC_SIM_TYPE_USIM               ,                   /* USIM卡 */
    TAF_SDC_SIM_TYPE_ROM_SIM            ,
    TAF_SDC_SIM_TYPE_UIM                ,                   /*UIM卡*/
    TAF_SDC_SIM_TYPE_CSIM               ,                   /*CSIM卡*/
    TAF_SDC_SIM_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_SIM_TYPE_ENUM_UINT8;

/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */


/*****************************************************************************
 枚举名    : TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8
 结构说明  : sysinfo查询时上报的服务域信息
 1.日    期: 2013年3月28日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
enum TAF_SDC_SERVICE_DOMAIN_ENUM
{
    TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN = 0,                                       /* 无服务 */
    TAF_SDC_SERVICE_DOMAIN_CS        = 1,                                       /* 仅CS服务 */
    TAF_SDC_SERVICE_DOMAIN_PS        = 2,                                       /* 仅PS服务 */
    TAF_SDC_SERVICE_DOMAIN_CS_PS     = 3,                                       /* PS+CS服务 */
    TAF_SDC_SERVICE_DOMAIN_SEARCHING = 4,                                       /* CS、PS均未注册，并处于搜索状态 */
    TAF_SDC_SERVICE_DOMAIN_BUTT
};
typedef VOS_UINT8  TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_REG_STATUS_ENUM_UINT8
 结构说明  : 注册结果
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_REG_STATUS_ENUM
{
    TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH,                                      /* 未注册未搜索 */
    TAF_SDC_REG_REGISTERED_HOME_NETWORK,                                        /* 注册，注册在 HOME PLMN */
    TAF_SDC_REG_NOT_REGISTERED_SEARCHING,                                       /* 未注册，正在搜索PLMN或者正在附着过程 */
    TAF_SDC_REG_REGISTERED_DENIED,                                              /* 注册被拒绝，当前用户不可以启动注册，启动服务被禁止 */
    TAF_SDC_REG_UNKNOWN,                                                        /* 其余情况 */
    TAF_SDC_REG_REGISTERED_ROAM,                                                /* 注册，注册在非 HOME PLMN */
    TAF_SDC_REG_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SDC_REG_STATUS_ENUM_UINT8;

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-29, end */

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
/*****************************************************************************
 枚举名    : TAF_SDC_RPT_CMD_ENUM
 结构说明  : CURC主动上报命令枚举

  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
enum TAF_SDC_RPT_CMD_INDEX_ENUM
{
    TAF_SDC_RPT_CMD_MODE                     = 0,
    TAF_SDC_RPT_CMD_RSSI,
    TAF_SDC_RPT_CMD_REJINFO,
    TAF_SDC_RPT_CMD_SRVST,
    TAF_SDC_RPT_CMD_PLMNSELEINFO,
    TAF_SDC_RPT_CMD_SIMST,
    TAF_SDC_RPT_CMD_TIME,
    TAF_SDC_RPT_CMD_SMMEMFULL,
    TAF_SDC_RPT_CMD_CTZV,
    TAF_SDC_RPT_CMD_CTZE,
    TAF_SDC_RPT_CMD_DSFLOWRPT,
    TAF_SDC_RPT_CMD_ORIG,
    TAF_SDC_RPT_CMD_CONF,
    TAF_SDC_RPT_CMD_CONN,
    TAF_SDC_RPT_CMD_CEND,
    TAF_SDC_RPT_CMD_STIN,
    TAF_SDC_RPT_CMD_CERSSI,
    TAF_SDC_RPT_CMD_ANLEVEL,
    TAF_SDC_RPT_CMD_SRCHEDPLMNINFO,
    TAF_SDC_RPT_CMD_LWCLASH,
    TAF_SDC_RPT_CMD_XLEMA,
    TAF_SDC_RPT_CMD_ACINFO,
    TAF_SDC_RPT_CMD_PLMN,
    TAF_SDC_RPT_CMD_CALLSTATE,

    /* 补充单个命令主动上报的枚举 */
    TAF_SDC_RPT_CMD_CREG,
    TAF_SDC_RPT_CMD_CGREG,
    TAF_SDC_RPT_CMD_CEREG,
    TAF_SDC_RPT_CMD_CTZR,
    TAF_SDC_RPT_CMD_CUSD,
    TAF_SDC_RPT_CMD_CSSI,
    TAF_SDC_RPT_CMD_CSSU,
    TAF_SDC_RPT_CMD_LWURC,
    TAF_SDC_RPT_CMD_CUUS1I,
    TAF_SDC_RPT_CMD_CUUS1U,
    TAF_SDC_RPT_CMD_NCELLMONITOR,

    TAF_SDC_RPT_CMD_MIPICLK,

    TAF_SDC_RPT_CMD_CTIME,
    TAF_SDC_RPT_CMD_XPASSINFO,

    TAF_SDC_RPT_CMD_FILECHANGE,

    TAF_SDC_RPT_CMD_CCONTDTMF,
    TAF_SDC_RPT_CMD_CBURSTDTMF,

    TAF_SDC_RPT_CMD_CSID,

    TAF_SDC_RPT_CMD_CLOCINFO,
    TAF_SDC_RPT_CMD_BUTT
};
typedef VOS_UINT8 TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_CALL_STATE_RPT_STATUS_ENUM
 结构说明  : 主动上报AT命令状态枚举

  1.日    期   : 2012年09月18日
    作    者   : l00198894
    修改内容   : STK补充特性及DCM需求开发项目新增枚举

*****************************************************************************/
enum TAF_SDC_CALL_STATE_RPT_STATUS_ENUM
{
    TAF_SDC_CALL_STATE_RPT_STATUS_DISABLE,                 /* 不允许主动上报 */
    TAF_SDC_CALL_STATE_RPT_STATUS_ENABLE,                  /* 允许主动上报 */
    TAF_SDC_CALL_STATE_RPT_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SDC_CALL_STATE_RPT_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8
 结构说明  : 主动上报受控类型
 1.日    期   : 2013年4月10日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM
{
    TAF_SDC_CMD_RPT_CTRL_BY_CURC,               /* 主动上报受CURC控制 */
    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,        /* 主动上报受单独的命令控制 */
    TAF_SDC_CMD_RPT_CTRL_BUTT
};
typedef VOS_UINT8 TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8;
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, end */

/*****************************************************************************
 枚举名    : TAF_SDC_STATUS_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8
 结构说明  : curc主动上报类型
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_STATUS_RPT_GENERAL_CTRL_TYPE_ENUM
{
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_NO_REPORT = 0,
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT    = 1,
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_CUSTOM    = 2,
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_STATUS_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, begin */
/*****************************************************************************
 枚举名    : TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8
 结构说明  : IMS voice capability
 1.日    期   : 2013年7月13日
   作    者   : y0024524
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_NW_IMS_VOICE_CAP_ENUM
{
    TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    TAF_SDC_NW_IMS_VOICE_SUPPORTED        = 1,

    TAF_SDC_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8
 结构说明  : network EMC BS capability
 1.日    期   : 2013年7月13日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_NW_EMC_BS_CAP_ENUM
{
    TAF_SDC_NW_EMC_BS_NOT_SUPPORTED       = 0,
    TAF_SDC_NW_EMC_BS_SUPPORTED           = 1,

    TAF_SDC_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8
 结构说明  : network EMC BS capability
 1.日    期   : 2013年7月13日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_LTE_CS_CAPBILITY_ENUM
{
    TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    TAF_SDC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    TAF_SDC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    TAF_SDC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 TAF_SDC_LTE_CS_CAPBILITY_ENUM_UINT8;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, end */

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
/*****************************************************************************
 枚举名    : TAF_SDC_VOICE_DOMAIN_ENUM_UINT32
 结构说明  : VOICE优选域
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_VOICE_DOMAIN_ENUM
{
    TAF_SDC_VOICE_DOMAIN_CS_ONLY            = 0,                                /**< CS voice only */
    TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY        = 1,                                /**< IMS PS voice only */
    TAF_SDC_VOICE_DOMAIN_CS_PREFERRED       = 2,                                /**< CS voice preferred, IMS PS Voice as secondary */
    TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,                                /**< IMS PS voice preferred, CS Voice as secondary */

    TAF_SDC_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32 TAF_SDC_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_SDC_SMS_DOMAIN_ENUM_UINT8
 结构说明  : 短信优选域
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_SMS_DOMAIN_ENUM
{
    TAF_SDC_SMS_DOMAIN_NOT_USE_SMS_OVER_IP                  = 0,                /**< not to use SMS over ip */
    TAF_SDC_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP            = 1,                /**< prefer to use SMS over ip, CS/PS SMS as secondary */

    TAF_SDC_SMS_DOMAIN_BUTT
};
typedef VOS_UINT8 TAF_SDC_SMS_DOMAIN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8
 枚举说明  : L模支持的cs域业务能力的类型
 1.日    期   : 2013年9月24日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_LTE_CS_SERVICE_ENUM
{
    TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS = 1,                              /* 支持cs fallback和sms over sgs*/
    TAF_SDC_LTE_SUPPORT_SMS_OVER_SGS_ONLY,                                      /* 支持sms over sgs only*/
    TAF_SDC_LTE_SUPPORT_1XCSFB,                                                 /* 支持1XCSFB */
    TAF_SDC_LTE_SUPPORT_BUTT
};
typedef VOS_UINT8 TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8
 枚举说明  : UE的使用设定
 1.日    期   : 2013年10月08日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_UE_USAGE_SETTING_ENUM
{
    TAF_SDC_UE_USAGE_VOICE_CENTRIC      = 0,                                    /* 语音中心 */
    TAF_SDC_UE_USAGE_DATA_CENTRIC,                                              /* 数据中心 */

    TAF_SDC_UE_USAGE_BUTT
};
typedef VOS_UINT8 TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8;
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
/*****************************************************************************
 枚举名    : TAF_SDC_PHONE_MODE_ENUM
 枚举说明  : 手机模式枚举
 1.日    期   : 2013年12月25日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_PHONE_MODE_ENUM
{
    TAF_SDC_PHONE_MODE_MINI                = 0,   /* minimum functionality*/
    TAF_SDC_PHONE_MODE_FULL                = 1,   /* full functionality */
    TAF_SDC_PHONE_MODE_TXOFF               = 2,   /* disable phone transmit RF circuits only */
    TAF_SDC_PHONE_MODE_RXOFF               = 3,   /* disable phone receive RF circuits only */
    TAF_SDC_PHONE_MODE_RFOFF               = 4,   /* disable phone both transmit and receive RF circuits */
    TAF_SDC_PHONE_MODE_FT                  = 5,   /* factory-test functionality */
    TAF_SDC_PHONE_MODE_RESET               = 6,   /* reset */
    TAF_SDC_PHONE_MODE_VDFMINI             = 7,   /* mini mode required by VDF*/
    TAF_SDC_PHONE_MODE_POWEROFF            = 8,   /* 关机下电模式 */
    TAF_SDC_PHONE_MODE_LOWPOWER            = 9,
    TAF_SDC_PHONE_MODE_BUTT
};
typedef VOS_UINT8 TAF_SDC_PHONE_MODE_ENUM_UINT8;


/* Added by s00261364 for V3R360_eCall项目, 2014-4-1, begin */
/*****************************************************************************
 枚举名    : TAF_SDC_CALL_MODE_INFO_ENUM
 结构说明  : 呼叫模式枚举
 1.日    期   : 2014年4月1日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_CALL_MODE_ENUM
{
    TAF_SDC_ECALL_ONLY            = 0,
    TAF_SDC_ECALL_AND_NORMAL_CALL = 1,
    TAF_SDC_CALL_MODE_BUTT
};
typedef VOS_UINT32 TAF_SDC_CALL_MODE_ENUM_UINT8;
/* Added by s00261364 for V3R360_eCall项目, 2014-4-1, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

/*****************************************************************************
 枚举名    : TAF_SDC_LMM_ACCESS_TYPE_ENUM
 结构说明  : LTE的接入模式EUTRAN_TDD/FDD
 1.日    期   : 2014年8月14日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_LMM_ACCESS_TYPE_ENUM
{
    TAF_SDC_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    TAF_SDC_LMM_ACCESS_TYPE_EUTRAN_FDD         ,
    TAF_SDC_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8
 结构说明  : 网络名称编码方式
 1.日    期   : 2015年2月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM
{
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT         = 0,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2    = 1,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2    = 2,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_BUTT
};
typedef VOS_UINT8 TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_SDC_CREG_TYPE_ENUM_UINT8
 结构说明  : CREG注册枚举类型
 1.日    期   : 2014年8月18日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_CREG_TYPE_ENUM
{
    TAF_SDC_CREG_TYPE_NOT_REPORT        = 0,
    TAF_SDC_CREG_TYPE_BREVITE           = 1,
    TAF_SDC_CREG_TYPE_ENTIRE            = 2,
    TAF_SDC_CREG_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_CREG_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_CGREG_TYPE_ENUM_UINT8
 结构说明  : CGREG注册枚举类型
 1.日    期   : 2014年8月18日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_CGREG_TYPE_ENUM
{
    TAF_SDC_CGREG_TYPE_NOT_REPORT       = 0,
    TAF_SDC_CGREG_TYPE_BREVITE          = 1,
    TAF_SDC_CGREG_TYPE_ENTIRE           = 2,
    TAF_SDC_CGREG_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_CGREG_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_CEREG_TYPE_ENUM_UINT8
 结构说明  : CEREG注册枚举类型
 1.日    期   : 2014年8月18日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_CEREG_TYPE_ENUM
{
    TAF_SDC_CEREG_TYPE_NOT_REPORT       = 0,
    TAF_SDC_CEREG_TYPE_BREVITE          = 1,
    TAF_SDC_CEREG_TYPE_ENTIRE           = 2,
    TAF_SDC_CEREG_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_CEREG_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_SDC_CDMACSQ_MODE_ENUM_UINT8
 结构说明  :
 1.日    期   : 2014年12月27日
   作    者   : m00312079
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_CDMACSQ_MODE_ENUM
{
    TAF_SDC_CDMACSQ_MODE_DISABLE      = 0,
    TAF_SDC_CDMACSQ_MODE_ENABLE       = 1,
    TAF_SDC_CDMACSQ_MODE_BUTT
};

typedef VOS_UINT8 TAF_SDC_CDMACSQ_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_SDC_HDR_CSQ_MODE_ENUM_UINT8
 结构说明  :
 1.日    期   : 2015年10月21日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_HDR_CSQ_MODE_ENUM
{
    TAF_SDC_HDR_CSQ_MODE_DISABLE      = 0,
    TAF_SDC_HDR_CSQ_MODE_ENABLE       = 1,
    TAF_SDC_HDR_CSQ_MODE_BUTT
};

typedef VOS_UINT8 TAF_SDC_HDR_CSQ_MODE_ENUM_UINT8;



/*****************************************************************************
 枚举名    : TAF_SDC_SYS_ROAMING_IND_ENUM
 结构说明  : roaming display indication (参考3GPP2 C.R1001-A中8.2章节中Table 8.1-1)

 1.日    期   : 2015年1月15日
   作    者   : h00246512
   修改内容   : 新增

*****************************************************************************/
enum TAF_SDC_SYS_ROAMING_IND_ENUM
{
    /* Roaming Indicator On */
    TAF_SDC_SYS_ROAMING_STATUS_ON                              = 0,

    /* Roaming Indicator Off */
    TAF_SDC_SYS_ROAMING_STATUS_OFF                             = 1,

    /* Roaming Indicator Flashing */
    TAF_SDC_SYS_ROAMING_STATUS_FLASHING                        = 2,

    /* Out of Neighborhood */
    TAF_SDC_SYS_ROAMING_STATUS_OUT_OF_NEIGHBORHOOD             = 3,

    /* Out of Building */
    TAF_SDC_SYS_ROAMING_STATUS_OUT_OF_BUILDING                 = 4,

    /* Roaming - Preferred System */
    TAF_SDC_SYS_ROAMING_STATUS_PREFERRED_SYSTEM                = 5,

    /* Roaming - Available System */
    TAF_SDC_SYS_ROAMING_STATUS_AVAILABLE_SYSTEM                = 6,

    /* Roaming - Alliance Partner */
    TAF_SDC_SYS_ROAMING_STATUS_ALLIANCE_PARTNER                = 7,

    /* Roaming - Premium Partner */
    TAF_SDC_SYS_ROAMING_STATUS_PREMIUM_PARTER                  = 8,

    /* Roaming - Full Service Functionality */
    TAF_SDC_SYS_ROAMING_STATUS_FULL_SRVICE_FUNCTIONALITY       = 9,

    /* Roaming - Partial Service Functionality */
    TAF_SDC_SYS_ROAMING_STATUS_PARTIAL_SRVICE_FUNCTIONALITY    = 10,

    /* Roaming Banner On */
    TAF_SDC_SYS_ROAMING_STATUS_BANNER_ON                       = 11,

    /* Roaming Banner Off */
    TAF_SDC_SYS_ROAMING_STATUS_BANNER_OFF                      = 12,

    TAF_SDC_SYS_ROAMING_STATUS_RESERVED_FOR_STARDARD_EN        = 13,

    /* 01000000 through 01111111 Reserved for Non-Standard Enhanced Roaming Indicator Numbers */
    TAF_SDC_SYS_ROAMING_STATUS_RESERVED_FOR_NON_STARDARD_EN    = 64,

    /* 10000000 through 11111111 Reserved */
    TAF_SDC_SYS_ROAMING_STATUS_RESERVED                        = 128
};
typedef VOS_UINT8 TAF_SDC_PRL_SYS_ROAMING_IND_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8
 结构说明  : IMS协议栈开关机状态枚举类型
 1.日    期   : 2015年02月04日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_IMS_SWITCH_STATE_ENUM
{
    TAF_SDC_IMS_SWITCH_STATE_OFF        = 0,
    TAF_SDC_IMS_SWITCH_STATE_ON         = 1,
    TAF_SDC_IMS_SWITCH_STATE_BUTT
};
typedef VOS_UINT8 TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_SRV_ACQ_RAT_TYPE_ENUM_UINT8
 枚举说明  : 业务触发搜网的RAT类型
 1.日    期   : 2014年5月15日
   作    者   : l00301449
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_SRV_ACQ_RAT_TYPE_ENUM
{
    TAF_SDC_SRV_ACQ_RAT_TYPE_3GPP,
    TAF_SDC_SRV_ACQ_RAT_TYPE_1X,
    TAF_SDC_SRV_ACQ_RAT_TYPE_HRPD,
    TAF_SDC_SRV_ACQ_RAT_TYPE_BUTT
};

typedef VOS_UINT8 TAF_SDC_SRV_ACQ_RAT_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_SDC_1X_UE_STATUS_ENUM
 枚举说明  : CDMA 当前的UE MAIN STATUS
 1.日    期   : 2015年9月19日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum TAF_SDC_1X_UE_MAIN_STATUS_ENUM
{
    TAF_SDC_1X_UE_MAIN_STATUS_INIT_STATE            = 0x00,
    TAF_SDC_1X_UE_MAIN_STATUS_IDLE_STATE            = 0x01,
    TAF_SDC_1X_UE_MAIN_STATUS_ACCESS_STATE          = 0x02,
    TAF_SDC_1X_UE_MAIN_STATUS_TCH_STATE             = 0x03,
    TAF_SDC_1X_UE_MAIN_STATUS_NO_SERVICE_STATE      = 0x04,
    TAF_SDC_1X_UE_MAIN_STATUS_STATE_ENUM_BUTT       = 0x05
};

typedef VOS_UINT8 TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SDC_1X_UE_SUB_STATUS_ENUM
 枚举说明  : CDMA 当前的UE SUB STATUS
 1.日    期   : 2015年9月19日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/

enum TAF_SDC_1X_UE_SUB_STATUS_ENUM
{
    TAF_SDC_1X_UE_SUB_STATUS_NULL                                    = 0x00,
    TAF_SDC_1X_UE_SUB_STATUS_INIT_DETERM_SUB_STATE                   = 0x01,
    TAF_SDC_1X_UE_SUB_STATUS_PILOT_CH_ACQ_SUB_STATE                  = 0x02,
    TAF_SDC_1X_UE_SUB_STATUS_SYNC_CH_ACQ_SUB_STATE                   = 0x03,
    TAF_SDC_1X_UE_SUB_STATUS_TIMING_CHNG_SUB_STATE                   = 0x04,
    TAF_SDC_1X_UE_SUB_STATUS_IDLE_SUB_STATE                          = 0x10,
    TAF_SDC_1X_UE_SUB_STATUS_UPDATE_OVERHEAD_SUB_STATE               = 0x20,
    TAF_SDC_1X_UE_SUB_STATUS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE      = 0x21,
    TAF_SDC_1X_UE_SUB_STATUS_PAG_RESP_SUB_STATE                      = 0x22,
    TAF_SDC_1X_UE_SUB_STATUS_MOB_STATION_ORDR_RESP_SUB_STATE         = 0x23,
    TAF_SDC_1X_UE_SUB_STATUS_REG_ACCESS_SUB_STATE                    = 0x24,
    TAF_SDC_1X_UE_SUB_STATUS_MOB_STATION_MSG_TRANS_SUB_STATE         = 0x25,
    TAF_SDC_1X_UE_SUB_STATUS_TCH_INIT_SUB_STATE                      = 0x30,
    TAF_SDC_1X_UE_SUB_STATUS_REL_SUB_STATE                           = 0x31,
    TAF_SDC_1X_UE_SUB_STATUS_WAIT_FOR_SERVICE_SUB_STATE              = 0x40,
    TAF_SDC_1X_UE_SUB_STATUS_SUB_STATE_ENUM_BUTT                     = 0x41

};

typedef VOS_UINT8 TAF_SDC_1X_UE_SUB_STATUS_ENUM_UINT8;





enum TAF_SDC_NETWORK_EXISTANCE_ENUM
{
    TAF_SDC_1X_NETWORK_EXIST                           = 0,              /* 1x has network */
    TAF_SDC_1X_NETWORK_NOT_EXIST                       = 1,              /* 1x does not have network */
    TAF_SDC_HRPD_NETWORK_EXIST                         = 2,              /* hrpd has network */
    TAF_SDC_HRPD_NETWORK_NOT_EXIST                     = 3,              /* hrpd does not have network */
    TAF_SDC_LTE_NETWORK_EXIST                          = 4,
    TAF_SDC_LTE_NETWORK_NOT_EXIST                      = 5,
    TAF_SDC_NETWORK_BUT
};
typedef VOS_UINT32 TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32;

/*****************************************************************************
Structure Name     :   TAF_SDC_SERVICE_INFO_STRU
Description        :   服务相关消息结构
Modify History     :
1)  Date           : 2015-06-01
    Author         : w00242748
    Modify content : Create
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                   bitOpCsSrvSta     : 1;
    VOS_UINT32                                   bitOpPsSrvSta     : 1;
    VOS_UINT32                                   bitOpCsRegSta     : 1;
    VOS_UINT32                                   bitOpPsRegSta     : 1;
    VOS_UINT32                                   bitOpSrvDomain    : 1;
    VOS_UINT32                                   bitOpSrvSta       : 1;
    VOS_UINT32                                   bitSpare          : 26;

    TAF_SDC_SERVICE_STATUS_ENUM_UINT8            enCsSrvSta;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8            enPsSrvSta;
    TAF_SDC_REG_STATUS_ENUM_UINT8                enCsRegSta;
    TAF_SDC_REG_STATUS_ENUM_UINT8                enPsRegSta;
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8            enSrvDomain;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8             enSrvSta;
}TAF_SDC_SRV_REG_INFO_STRU;

/*****************************************************************************
 结构名    : NA
 结构说明  : 更新服务状态和注册状态函数
 1.日    期   : 2014年8月05日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef VOS_VOID  (*pTafSdcSysmodServiceRegStaUpdateFunc)(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);


typedef struct
{
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurSysMode;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enNewSysMode;
    TAF_SYS_SUBMODE_ENUM_UINT8                              enNewSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pfuncSysmodServiceRegStatusUpdate;
}TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_MODIFY_SYSMODE_MAP_TLB_STRU
 结构说明  : 现有系统模式和子模式中增加或者删除一个模式
 1.日    期   : 2016年01月09日
   作    者   : l00301449
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurAppSysMode;
    TAF_SYS_SUBMODE_ENUM_UINT8                              enCurAppSubMode;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enNewAppSysMode;
    TAF_SYS_SUBMODE_ENUM_UINT8                              enNewAppSubMode;
}TAF_SDC_MODIFY_SYSMODE_MAP_TLB_STRU;
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
 结构名    : TAF_SDC_PLATFORM_RAT_CAP_STRU
 结构说明  : 平台接入技术能力信息
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     ucRatNum;
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8          aenRatList[TAF_SDC_PLATFORM_MAX_RAT_NUM];
}TAF_SDC_PLATFORM_RAT_CAP_STRU;

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
/*****************************************************************************
 结构名    : TAF_SDC_RAT_PRIO_STRU
 结构说明  : 当前UE的接入技术优先级
 1.日    期 : 2013年11月20日
   作    者 : w00176964
   修改内容 : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatNum;
    TAF_SDC_SYS_MODE_ENUM_UINT8         aenRatPrio[TAF_SDC_MAX_RAT_NUM];
}TAF_SDC_RAT_PRIO_STRU;

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-25, begin */
/*****************************************************************************
 结构名    : TAF_SDC_IMS_RAT_SUPPORT_STRU
 结构说明  : IMS支持信息
 1.日    期   : 2013年7月25日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGsmImsSupportFlag;    /**< GSM IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUtranImsSupportFlag;  /**< UNTRAN IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucGsmEmsSupportFlag;    /**< GSM EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUtranEmsSupportFlag;  /**< UNTRAN EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           aucReserved[2];
}TAF_SDC_IMS_RAT_SUPPORT_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_IMS_CAPABILITY_STRU
 结构说明  : IMS能力:包括IMS语音是否支持，IMS短信是否支持，IMS VIDEO CALL是否支持
 1.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目
 2.日    期   : 2014年04月01日
   作    者   : y00245242
   修改内容   : 为DTS2014040203732修改，增加NV控制USSD业务域选择；USSD业务NV打开，
                进行正常域选择，否则选择CS域
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag;            /* IMS语音使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSmsOnImsSupportFlag;                  /* IMS短信使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucVideoCallOnImsSupportFlag;            /* IMS域VIDEO CALL使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUssdOnImsSupportFlag;                 /* IMS USSD业务使能项，VOS_TRUE :支持，VOS_FALSE :不支持 */
}TAF_SDC_IMS_CAPABILITY_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU
 结构说明  :
 1.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucImsRedialCauseNum;                                                  /* IMS call重拨原因值个数 */
    VOS_UINT8                 ucImsaRedialCauseNum;                                                 /* IMSA call重拨原因值个数 */
    VOS_UINT8                 aucReserve[2];
    VOS_UINT16                ausImsRedialCause[TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM];
    VOS_UINT16                ausImsaRedialCause[TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM];
}TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_IMS2CS_REDIAL_CONFIG_STRU
 结构说明  :
 1.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallRedial;                           /* call重拨flag */
    VOS_UINT8                                               ucSmsRedial;                            /* SMS 重拨flag */
    VOS_UINT8                                               ucSsRedial;                             /* SS  重拨flag */
    VOS_UINT8                                               aucReserve[1];
    TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU       stCallRedialCauseCfg;
}TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU
 结构说明  :
 1.日    期   : 2013年12月24日
   作    者   : y00245242
   修改内容   : 增加IMS与CS之间的换域重拨功能
 2.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallRedial;                           /* call重拨flag */
    VOS_UINT8                                               ucSmsRedial;                            /* SMS 重拨flag */
    VOS_UINT8                                               ucSsRedial;                             /* SS  重拨flag */
    VOS_UINT8                                               aucReserve[1];
}TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SWITCH_DOMAIN_REDIAL_STRU
 结构说明  : 重拨数据结构定义，包括呼叫重拨、短信重拨、补充业务重拨
 1.日    期   : 2013年12月24日
   作    者   : y00245242
   修改内容   : 增加IMS与CS之间的换域重拨功能
 2.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 修改
*****************************************************************************/
typedef struct
{
    TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU             stRedialImsToCs;                        /* IMS to CS重拨数据结构  */
    TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU             stRedialCsToIms;                        /* CS to IMS 重拨数据结构 */
}TAF_SDC_SWITCH_DOMAIN_REDIAL_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_IMS_CONFIG_PARA_STRU
 结构说明  : IMS配置信息
 1.日    期   : 2013年7月25日
   作    者   : s00217060
   修改内容   : 新建
 2.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，增加IMS语音使能项、IMS短信使能项、voice优选域
 3.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 增加IMS域到CS域的换域重拨功能
 4.日    期   : 2015年01月30日
   作    者   : y00245242
   修改内容   : 迭代9开发，下移IMSA接口到MSCC模块
*****************************************************************************/
typedef struct
{
    TAF_SDC_IMS_RAT_SUPPORT_STRU        stImsRatSupport;
    TAF_SDC_IMS_CAPABILITY_STRU         stImsCapability;
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCfg;                      /* L模支持的cs域业务能力的类型 */
    TAF_SDC_SMS_DOMAIN_ENUM_UINT8       enSmsDomain;                            /* sms domain preferrece */
/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    VOS_UINT8                           ucRoamingSupport;
    VOS_UINT8                           aucReserved[1];
    TAF_SDC_SWITCH_DOMAIN_REDIAL_STRU   stRedial;                               /* IMS<-->CS换域重拨标志 */
/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, end */
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain;                          /* voice domain preferrece */

}TAF_SDC_IMS_CONFIG_PARA_STRU;
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-25, end */

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/*****************************************************************************
 结构名    : TAF_SDC_EMERGENCY_CONTENT_STRU
 结构说明  : 紧急呼内容结构体，包括紧急呼类型，紧急呼号码长度，紧急呼号码
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                      ucCategoryValue;                                 /* Emergency Service Category Value         */
    VOS_UINT8                      ucEmcNumLen;                                     /* 紧急呼号码长度，即aucEmergencyList的有效长度*/
    VOS_UINT8                      aucEmergencyList[TAF_SDC_EMER_NUM_MAX_LENGTH];   /* 紧急呼列表 */
}TAF_SDC_EMERGENCY_CONTENT_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_MM_EMERGENCY_LIST_STRU
 结构说明  : 紧急呼列表结构体，包括Mcc，紧急呼列表个数，紧急呼列表
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulMcc;                                               /* MCC */
    VOS_UINT8                          ucEmergencyNumber;                                   /* 紧急呼个数 */
    VOS_UINT8                          aucReserved[3];
    TAF_SDC_EMERGENCY_CONTENT_STRU     astEmergencyLists[TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER];/* 紧急呼列表 */
}TAF_SDC_MM_EMERGENCY_LIST_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CUSTOM_ECC_NUM_STRU
 结构说明  : 运营商定制紧急呼号码结构
 1.日    期   : 2013年12月24日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII新增结构，与MN_CALL_CUSTOM_ECC_NUM_STRU的定义保持一致

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCategory;                             /* 紧急呼号码类型 */
    VOS_UINT8                           ucValidSimPresent;                      /* 紧急呼号码是有卡时有效还是无卡时有效，1有卡时有效，0无卡时有效 */
    VOS_UINT8                           ucAbnormalServiceFlg;                   /* 紧急呼号码有卡时是否仅在非正常服务时有效，0:任何服务时均有效，1:仅非正常服务时有效 */
    VOS_UINT8                           ucEccNumLen;                            /* 紧急呼号码长度 */
    VOS_UINT8                           aucEccNum[TAF_SDC_MAX_BCD_NUM_LEN];     /* 紧急呼号码 */
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
} TAF_SDC_CUSTOM_ECC_NUM_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU
 结构说明  : 运营商定制紧急呼号码结构
 1.日    期   : 2012年06月11日
   作    者   : W00166186
   修改内容   : AT&T&DCM项目新增结构

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccNumCount;                                  /* 紧急号个数 */
    VOS_UINT8                           aucReseve[3];
    TAF_SDC_CUSTOM_ECC_NUM_STRU         astCustomEccNumList[TAF_SDC_MAX_CUSTOM_ECC_NUM];/* 紧急呼列表 */
} TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CUSTOM_ECC_CTX_STRU
 结构说明  : 运营商定制紧急呼号码控制结构
 1.日    期   : 2012年06月11日
   作    者   : W00166186
   修改内容   : AT&T&DCM项目新增结构

****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucCustomSetFlg;                     /* VOS_TRUE,标书APP正在设置定制紧急呼号码，VOS_FALSE,表示没有开始定制 */
    VOS_UINT8                               aucReserve[3];
    TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU        stCustomEccNumList;                 /* APP定制的紧急呼列表 */
} TAF_SDC_CUSTOM_ECC_CTX_STRU;
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/* Added by s00261364 for L-C互操作项目, 2014-01-27, Begin */
/*****************************************************************************
 结构名    : TAF_NV_LC_CTRL_PARA_STRU
 协议表格  : 无
 结构说明  : 用于记录L+C共SIM卡功能是否处于使能状态

 修改历史      :
  1.日    期   : 2014年01月23日
    作    者   : s00246516
    修改内容   : L-C互操作项目新增NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     ucLCEnableFlg;
    TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8           enRatCombined;
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8               enLCWorkCfg;
    VOS_UINT8                                     aucReserved[1];
}TAF_SDC_LC_CONFIG_PARA_STRU;
/* Added by s00261364 for L-C互操作项目, 2014-01-27, End */

/*****************************************************************************
 结构名    : TAF_SDC_MS_CAP_INFO_STRU
 结构说明  : MS的能力信息
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新建
 2.日    期   : 2013年6月3日
   作    者   : s00217060
   修改内容   : for V9R1_SVLTE:新增是否支持SVLTE标志
 3.日    期   : 2013年07月25日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseI项目:新增是否支持IMS标志
 4.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，新增IMS是否支持语音/短信标志
*****************************************************************************/
typedef struct
{
    TAF_SDC_PLATFORM_RAT_CAP_STRU       stPlatformRatCap;                       /* 平台接入技术能力信息 */

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
    VOS_UINT8                           ucSvlteSupportFlag;                     /* 是否支持SVLTE标志 */
    VOS_UINT8                           aucReserved[3];

    TAF_SDC_IMS_CONFIG_PARA_STRU       stImsConfigPara;                       /* IMS相关配置信息 */
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

    /* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */
    TAF_SDC_LC_CONFIG_PARA_STRU        stLcConfigPara;
    /* Added by s00261364 for L-C互操作项目, 2014-1-27, end */
#if (FEATURE_ON == FEATURE_BASTET)
    VOS_UINT8                           ucBastetSupportFlag;                     /* 是否支持Bastet标志 */
    VOS_UINT8                           aucBstReserved[3];
#endif

}TAF_SDC_MS_CAP_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MML_SIM_FORMAT_PLMN_ID
 结构说明  : Sim PLMN ID的存储结构
 1.日    期   : 2015年2月17日
   作    者   : b00269685
   修改内容   : 新建
*****************************************************************************/

typedef struct {
    VOS_UINT8                           aucSimPlmn[TAF_SDC_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
} TAF_SDC_SIM_FORMAT_PLMN_ID;

/* Added by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-22, begin */
/*****************************************************************************
 结构名    : TAF_SDC_PLMN_ID_STRU
 结构说明  : plmn信息
 1.日    期   : 2013年3月22日
   作    者   : s46746
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
} TAF_SDC_PLMN_ID_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_3GPP_SYS_INFO_STRU
 结构说明  : 服务小区信息
 1.日    期   : 2013年3月22日
   作    者   : s46746
   修改内容   : 新建
 2.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : VOLTE_PhaseII项目:增加漫游参数和是否驻留标记
 3.日    期   : 2014年6月13日
   作    者   : w00167002
   修改内容   : DSDS III增加area lost no rf标志
 4.日    期   : 2014年8月14日
   作    者   : s00217060
   修改内容   : DTS2014080700822:增加LTE驻留的小区是FDD还是TDD

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLac;
    VOS_UINT8                           aucReserve1[2];
    TAF_SDC_PLMN_ID_STRU                stPlmnId;
    VOS_UINT8                           ucRac;
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, begin */
    VOS_UINT8                           ucRoamFlag;                     /* 当前驻留网络是否漫游 VOS_TRUE:漫游网络 VOS_FALSE:非漫游网络 */
    VOS_UINT8                           ucCampOnFlg;                    /* 当前是否驻留,收到系统消息认为驻留,收到搜网或丢网指示认为未驻留 */
    VOS_UINT8                           uc3GppRfAvailFlg;

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, end */
    VOS_UINT32                          ulCellId;
    TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8  enLmmAccessType;
    VOS_UINT8                           aucReserve2[3];
    VOS_UINT32                          ulLteArfcn;                             /* LTE驻留频点信息 */

} TAF_SDC_3GPP_SYS_INFO_STRU;

/** ****************************************************************************
 * Name        : TAF_SDC_1X_SIG_QUALITY_RPT_INFO_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_SDC_CDMACSQ_MODE_ENUM_UINT8     enMode;
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           ucRssiRptThreshold;
    VOS_UINT8                           ucEcIoRptThreshold;
    VOS_INT16                           sCdmaRssi;
    VOS_INT16                           sCdmaEcIo;
    VOS_INT8                            cDelayRptFLag;      /*延迟上报信号质量标志，VOS_TRUE时表示处于延迟上报阶段*/
    VOS_UINT8                           aucReserve[3];
}TAF_SDC_1X_SIG_QUALITY_INFO_STRU;



/** ****************************************************************************
 * Name        : TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_SDC_HDR_CSQ_MODE_ENUM_UINT8     enMode;
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           ucRssiThreshold;
    VOS_UINT8                           ucSnrThreshold;
    VOS_INT16                           sHdrRssi;
    VOS_INT16                           sHdrSnr;
    VOS_INT16                           sHdrEcio;
    VOS_UINT8                           ucEcioThreshold;
    VOS_UINT8                           ucIsDelayReportEnable;  /*  TRUE: ENABLE */
}TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU;





/*****************************************************************************
 结构名    : TAF_SDC_ACCESS_RESTRICTION_STRU
 结构说明  : 接入禁止信息
 1.日    期   : 2013年3月22日
   作    者   : s46746
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_CELL_RESTRICTION_TYPE_ENUM_UINT8    enCellAcType;                   /* 小区受限类型 */
    VOS_UINT8                                   ucRestrictRegister;             /* 是否限制注册VOS_TRUE:限制；VOS_FALSE:不限制 */
    VOS_UINT8                                   ucRestrictPagingRsp;            /* 是否限制响应寻呼VOS_TRUE:限制；VOS_FALSE:不限制 */
    VOS_UINT8                                   ucReserved;
}TAF_SDC_ACCESS_RESTRICTION_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_CS_DOMAIN_INFO_STRU
 结构说明  : CS域信息
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : VOLTE PhaseII项目修改:增加CS域的SIM卡注册状态
 3.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0
*****************************************************************************/
typedef struct
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8      enCsServiceStatus;                   /* cs服务状态 */
    TAF_SDC_REG_STATUS_ENUM_UINT8          enCsRegStatus;                       /* cs注册状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    VOS_UINT8                              ucSimCsRegStatus;    /* SIM卡CS域的注册结果导致的卡是否有效VOS_TRUE:CS域的卡有效,VOS_FALSE:CS域的卡无效*/

    VOS_UINT8                              ucCsAttachAllowFlg;                  /* cs是否允许注册标识 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */
    TAF_SDC_ACCESS_RESTRICTION_STRU        stCsAcRestriction;                   /* 当前CS域接入受限情况 */
}TAF_SDC_CS_DOMAIN_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_PS_DOMAIN_INFO_STRU
 结构说明  : PS域信息
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : VOLTE PhaseII项目修改:增加PS域的SIM卡注册状态

 3.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
typedef struct
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8      enPsServiceStatus;                                                            /* ps服务状态 */
    TAF_SDC_REG_STATUS_ENUM_UINT8          enPsRegStatus;                       /* ps注册状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    VOS_UINT8                              ucSimPsRegStatus;                    /* SIM卡PS域的注册结果导致的卡是否有效VOS_TRUE:CS域的卡有效,VOS_FALSE:CS域的卡无效*/
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */
    VOS_UINT8                              ucPsAttachAllowFlg;                  /* ps是否允许注册标识 */
    TAF_SDC_ACCESS_RESTRICTION_STRU        stPsAcRestriction;                   /* 当前PS域接入受限情况 */

}TAF_SDC_PS_DOMAIN_INFO_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
/*****************************************************************************
 结构名    : TAF_SDC_IMS_DOMAIN_INFO_STRU
 结构说明  : IMS域信息
 1.日    期   : 2013年12月13日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2015年01月28日
   作    者   : y00245242
   修改内容   : iteration 9开发，下移IMSA接口到MSCC模块
*****************************************************************************/
typedef struct
{
    TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8   enImsNormalRegSta;
    VOS_UINT8                                  aucReserved[3];
}TAF_SDC_IMS_DOMAIN_INFO_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

/*****************************************************************************
 结构名    : TAF_SDC_SIM_STATUS_STRU
 结构说明  : sim卡状态信息
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;
    VOS_UINT8                           aucReserved[3];
}TAF_SDC_SIM_STATUS_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SIM_MS_IDENTITY_STRU
 结构说明  : ms identity信息
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年04月28日
   作    者   : s00246516
   修改内容   : 双IMSI切换时,MMA概率不触发关机和开机操作
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImsi[TAF_SDC_MAX_IMSI_LEN];

	VOS_UINT8                           aucLastImsi[TAF_SDC_MAX_IMSI_LEN];
    VOS_UINT8                           aucReserved[2];
}TAF_SDC_SIM_MS_IDENTITY_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_USIM_INFO_STRU
 结构说明  : 服务小区信息
 1.日    期   : 2013年3月22日
   作    者   : s46746
   修改内容   : 新建
 2.日    期   : 2013年7月30日
   作    者   : w00176964
   修改内容   : 增加SIM卡类型
 3.日    期   : 2014年4月9日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:增加call模式
*****************************************************************************/
typedef struct
{
    TAF_SDC_SIM_STATUS_STRU             stUsimStatus;                            /* SIM卡状态 */
    TAF_SDC_SIM_MS_IDENTITY_STRU        stMsIdentity;                           /* MS Identity信息 */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-9, begin */
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode;
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-9, end */
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enUsimType;                              /* SIM卡类型 */
    VOS_UINT8                           aucRsv[2];

    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */
}TAF_SDC_USIM_INFO_STRU;


/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
/*****************************************************************************
 结构名    : TAF_SDC_CURC_RPT_CTRL_STRU
 结构说明  : CURC控制主动上报的结构体
 1.日    期   : 2013年3月25日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_STATUS_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8   enStatusRptGeneralControl; /* 控制是否允许所有私有命令的主动上报 */
    VOS_UINT8                                         aucReserved[3];
    VOS_UINT8                                         aucRptCfg[TAF_SDC_RPT_CFG_MAX_SIZE]; /* 64bit主动上报标识 */
}TAF_SDC_CURC_RPT_CTRL_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_UNSOLICITED_RPT_CTRL_STRU
 结构说明  : 单个命令控制主动上报的结构体
 1.日    期   : 2013年3月25日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                         aucRptCfg[TAF_SDC_RPT_CFG_MAX_SIZE]; /* 64bit主动上报标识 */
}TAF_SDC_UNSOLICITED_RPT_CTRL_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_RPT_CTRL_STRU
 结构说明  : 控制主动上报的结构体,包括CURC和单个命令控制主动上报
 1.日    期   : 2013年3月25日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_CURC_RPT_CTRL_STRU              stCurcRptCtrl;                      /* CURC控制主动上报 */
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU       stUnsolicitedRptCtrl;               /* 单个命令控制主动上报 */
}TAF_SDC_RPT_CTRL_STRU;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

/*****************************************************************************
 结构名    : TAF_SDC_USSD_CFG_STRU
 结构说明  : USSD配置信息
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUssdTransMode;
    VOS_UINT8                           ucAlphaTransMode;
    VOS_UINT8                           aucRsv[2];
}TAF_SDC_USSD_CFG_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU
 结构说明  : 控制通过两个Modem的信息交互的增强型的搜索策略
 1.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucUtranSkipWPlmnSearchFlag;
    VOS_UINT8                                   aucReserved[3];
}TAF_SDC_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_PLMN_EXACTLY_COMPARE_INFO_STRU
 结构说明  : en_NV_Item_PLMN_EXACTLY_COMPARE_FLG nv配置内容
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;         /* 精确比较是否开启 */
    VOS_UINT8                           aucRsv[3];
}TAF_SDC_PLMN_EXACTLY_COMPARE_INFO_STRU;

/*****************************************************************************
结构名    : TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU
结构说明  : 非正常服务下是否上报注册状态改变配置信息
1.日    期  : 2015年10月28日
  作    者  : z00359541
  修改内容  : 新生成函数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMergeFlg;                      /* 非正常服务下是否上报注册状态改变 */
    VOS_UINT8                           aucReserved[3];
} TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_MS_SYS_CFG_INFO_STRU
 结构说明  : 系统配置信息
 1.日    期   : 2013年3月22日
   作    者   : s46746
   修改内容   : 新建
 2.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : SS FDN&Call Control项目:增加USSD传输模式信息
 3.日    期   : 2013年08月05日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseI项目
 4.日    期   : 2013年10月15日
   作    者   : y00245242
   修改内容   : VoLTE_PhaseII项目

 5.日    期   : 2013年11月14日
   作    者   : z00161729
   修改内容   : DTS2013111507527:gcf 31.9.2.1不过，网络ussd notify消息应该广播上报，收到网络release complete应该上报cusd:2而不是0
 6.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 7.日    期   : 2015年2月26日
   作    者   : c00318887
   修改内容   : AT&T phaseII 增加ucPlmnExactlyCompareFlg
*****************************************************************************/
typedef struct
{
    TAF_SDC_RPT_CTRL_STRU               stRptCtrl;                              /* 控制主动上报信息 */
    TAF_SDC_USSD_CFG_STRU               stUssdCfg;                              /* USSD配置信息 */
    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, begin */
    VOS_UINT16                          usAppCfgSupportType;                    /*控制应用版本*/
    /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, begin */
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 enUeUsageSetting;                       /* UE's usage setting */
    /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, end */

    VOS_UINT8                                ucRefreshAllFileRestartFlag;
    TAF_SDC_PLMN_EXACTLY_COMPARE_INFO_STRU   stPlmnExactlyCompareInfo;                /* 精确比较PLMN标记 */

    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, end */

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    TAF_SDC_RAT_PRIO_STRU               stPrioRatList;                          /* 接入技术以及优先级 */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    TAF_SDC_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU  stDsdaPlmnSearchEnhancedCfg;

    TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU stNonnormalRegStatusMergeCfg;

}TAF_SDC_MS_SYS_CFG_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_MS_CFG_INFO_STRU
 结构说明  : ms的配置信息
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_MS_CAP_INFO_STRU            stMsCapInfo;                            /* MS的能力信息 */
    TAF_SDC_MS_SYS_CFG_INFO_STRU        stMsSysCfgInfo;                         /* 系统配置信息 */
}TAF_SDC_MS_CFG_INFO_STRU;

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, begin */
/*****************************************************************************
 结构名    : TAF_SDC_NETWORK_CAP_INFO_STRU
 结构说明  : 当前驻留的网络的能力信息
 1.日    期   : 2013年3月28日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8   enNwImsVoCap;
    TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8      enNwEmcBsCap;
    TAF_SDC_LTE_CS_CAPBILITY_ENUM_UINT8   enLteCsCap;
    VOS_UINT8                             aucReserved[1];
}
TAF_SDC_NETWORK_CAP_INFO_STRU;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, end */

/** ****************************************************************************
 * Name        : TAF_SDC_1X_REG_INFO_STRU
 * Description : Register info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegZone;      /**<  Registration zone */
    VOS_UINT8                           ucRegZoneNum;   /**<  Number of registration zones to be retained */

    /* for reg */
    VOS_UINT8                           ucZoneTimer;    /**<  Zone timer length */

    /* for reg */
    VOS_UINT8                           ucMultiSidFlg;  /**<  Multiple SID storage indicator */

    /* for reg */
    VOS_UINT8                           ucMultiNidFlg;  /**<  Multiple NID storage indicator */

    /* for reg */
    VOS_UINT16                          usRegDistance;  /**<  Registration distance */

    /* for reg */
    VOS_UINT8                           ucRegPeriod;    /**<  Registration period */

    /* for reg */
    VOS_UINT8                           ucHomeReg;      /**<  Home registration indicator */

    /* for roam */
    VOS_UINT8                           ucSidRoamReg;   /**<  SID roamer registration indicator */

    /* for roam */
    VOS_UINT8                           ucNidRoamReg;   /**<  NID roamer registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerUpReg;   /**<  Power-up registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerDownReg; /**<  Power-down registration indicator */

    /* for reg */
    VOS_UINT8                           ucParameterReg; /**<  Parameter-change registration indicator */

    /* for reg */
    VOS_UINT8                           aucReserve[1];
}TAF_SDC_1X_REG_INFO_STRU;

/** ****************************************************************************
 * Name        : TAF_SDC_1X_SERVICE_INFO_STRU
 * Description : Service info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxAltSo;            /**<  Max. Num. of alternative service options,for Origination or Page Response Message */
    VOS_UINT8                           ucSDBSupported;        /**<  Short Data Burst supported indicator */
    VOS_UINT8                           ucMoQos;               /**<  permission indicator for QoS in Origination message */
    VOS_UINT8                           ucConcurrentSupported; /**<  concurrent service supported */
    VOS_UINT8                           ucMoPosSupported;      /**<  MS initiated position location supported */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usImsi11_12;           /**<  11th and 12th digits of the IMSI */
    VOS_UINT32                          ulMcc;                 /**<  Mobile country code */
    VOS_UINT16                          usMnc;                 /**<  Mobile network code */
    VOS_UINT8                           aucReserve[2];
}TAF_SDC_1X_SERVICE_INFO_STRU;

/** ****************************************************************************
 * Name        : TAF_SDC_1X_BASE_STATION_INFO_STRU
 * Description : Base station info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usBaseId;        /**<  Base station identification */

    VOS_UINT8                           ucBaseClass;     /**<  Base station class */
    VOS_UINT8                           aucReserve[1];
    /* reg & zone */
    VOS_INT32                           lBaseLatitude;   /**<  Base station latitude */
    VOS_INT32                           lBaseLongitude;  /**<  Base station longitude */

}TAF_SDC_1X_BASE_STATION_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CDMA_DOMAIN_INFO_STRU
 结构说明  : 当前驻留的1X网络的域信息
 1.日    期   : 2014年9月5日
   作    者   : y00213812
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usFreq;
    VOS_INT32                           lSid;             /**<  System identification */
    VOS_INT32                           lNid;             /**<  Network identification */
    VOS_UINT32                          ulIsInEmcCallBack; /* 当前是否处于callback模式*/
    VOS_UINT8                           ucIsEmcCallExistFlg;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           ucRoamingInd;
    VOS_UINT8                           ucPrevInUse;
    VOS_UINT8                           ucPacketZoneId;    /**<  Packet Data service zone identifier */

    VOS_UINT8                           uc1xRfAvailFlg;

    PS_BOOL_ENUM_UINT8                  enRegInfoIncl;
    PS_BOOL_ENUM_UINT8                  enBaseStationInfoIncl;
    PS_BOOL_ENUM_UINT8                  enServiceInfoIncl;
    VOS_UINT8                           aucReserve[1];

    TAF_SDC_1X_REG_INFO_STRU            stRegInfo;
    TAF_SDC_1X_BASE_STATION_INFO_STRU   stBaseStationInfo;
    TAF_SDC_1X_SERVICE_INFO_STRU        stServiceInfo;
}TAF_SDC_1X_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_HRPD_SYS_INFO_STRU
 结构说明  : 当前驻留的HRPD网络的域信息
 1.日    期   : 2015年5月15日
   作    者   : l00301449
   修改内容   : 新建

  2.日    期   : 2015年7月9日
    作    者   : y00322978
    修改内容   : 添加hrpd信息用于可维可测
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucHrpdRfAvailFlg;
    VOS_UINT8                                   ucColorCode;
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT8                                   ucSubNetMask;
    NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM_UINT8   ucSessionStatus;
    VOS_UINT32                                  ulMcc;                   /**<  Mobile country code */
    VOS_UINT32                                  ulSessionSeed;          /*RATI*/
    VOS_UINT8                                   aucCurUATI[NAS_OM_MMA_UATI_OCTET_LENGTH]; /*UATI*/
    VOS_UINT32                                  ulSector24;
}TAF_SDC_HRPD_SYS_INFO_STRU;



/*****************************************************************************
 结构名    : TAF_SDC_NETWORK_INFO_STRU
 结构说明  : 当前驻留的网络信息
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;
    NAS_OM_1X_CALL_STATE_ENUM_UINT8     en1xCallState;
    VOS_UINT8                           aucReserved[3];
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_SDC_3GPP_SYS_INFO_STRU          st3gppSysInfo;                         /* 当前驻留PLMN信息 */
    TAF_SDC_1X_SYS_INFO_STRU            st1xSysInfo;
    TAF_SDC_HRPD_SYS_INFO_STRU          stHrpdSysInfo;
}TAF_SDC_SYS_INFO_STRU;

/* Added by z00234330 for v8r2信号显示优化, 2014-10-17, begin */
/*****************************************************************************
 结构名    : TAF_SDC_SERVICED_PLMN_INFO_STRU
 结构说明  : 当前提供服务的PLMN的相关信息
 1.日    期   : 2014年10月17日
   作    者   : z00234330
   修改内容   : 当前提供服务的PLMN的相关信息
*****************************************************************************/
typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stServicePlmnId;     /*当前注册成功的PLMN ID*/
    TAF_SDC_SYS_MODE_ENUM_UINT8         enServiceSysMode;    /*当前注册成功的接入技术*/
    VOS_UINT8                           ucServiceUtranMode;  /*模式是FDD还是TDD*/
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enServiceSysSubMode; /*当前注册成功的子系统模式*/
    VOS_UINT8                           ucServiceRac;        /*当前注册成功的RAC*/
    VOS_UINT16                          usServiceLac;        /*当前注册成功的LAC*/
    VOS_UINT8                           ucServiceRoamFlg;    /*当前是否漫游*/
    VOS_UINT8                           aucReserve[1];
    VOS_UINT32                          ulServiceCellId;     /*当前注册成功的cellid*/
}TAF_SDC_SERVICED_PLMN_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_3G_CELL_SIGN_INFO_STRU
 结构说明  : 3G信号质量相关信息
 1.日    期   : 2014年10月17日
   作    者   : z00234330
   修改内容   : 小区信号质量
*****************************************************************************/
typedef struct
{
    VOS_INT16                       sRscpValue;  /* 小区信号质量用于3g下^cerssi上报使用*/
    VOS_INT16                       sEcioValue;  /* 小区信噪比用于3g下^cerssi上报使用*/
    /* 用于与UIION其他结构体(TAF_SDC_2G_CELL_SIGN_INFO_STRU,TAF_SDC_4G_CELL_SIGN_INFO_STRU)
         字节对齐，后续如果三个结构体发生改变，此处保留位也要相应修改 */
    VOS_UINT8                       aucReserve[16];
} TAF_SDC_3G_CELL_SIGN_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_2G_CELL_SIGN_INFO_STRU
 结构说明  : 信号质量相关信息
 1.日    期   : 2014年10月17日
   作    者   : z00234330
   修改内容   : 小区信号质量
*****************************************************************************/
typedef struct
{
    VOS_INT16                       sRssiValue;   /* 小区信号质量用于2g下^cerssi上报使用,2g没有rscp的概念用的是rssi */
    /* 用于与UIION其他结构体(TAF_SDC_3G_CELL_SIGN_INFO_STRU,TAF_SDC_4G_CELL_SIGN_INFO_STRU)
        字节对齐，后续如果三个结构体发生改变，此处保留位也要相应修改 */
    VOS_UINT8                       aucReserve1[18];
} TAF_SDC_2G_CELL_SIGN_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_4G_CELL_SIGN_INFO_STRU
 结构说明  : 4G信号质量相关信息
 1.日    期   : 2014年10月17日
   作    者   : z00234330
   修改内容   : 小区信号质量
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRI;                                   /* RI*/
    VOS_UINT8                           aucRes[2];
    VOS_UINT16                          ausCQI[2];                              /* CQI两个码字 */

}TAF_SDC_CQI_INFO_STRU;

typedef struct
{
    VOS_INT16                           sRssi;              /* Rssi*/
    VOS_INT16                           sRsd;               /* 填充字段*/
    VOS_INT16                           sRsrp;              /* 范围：(-141,-44), 99为无效 */
    VOS_INT16                           sRsrq;              /* 范围：(-40, -6) , 99为无效 */
    VOS_INT32                           lSINR;              /* SINR RS_SNR */
    TAF_SDC_CQI_INFO_STRU               stCQI;                                  /*Channle Quality Indicator*/
}TAF_SDC_4G_CELL_SIGN_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_3GPP_RSSI_INFO_STRU
 结构说明  : 小区信号质量
 1.日    期   : 2014年10月17日
   作    者   : z00234330
   修改内容   : 小区信号质量
 2.日    期   : 2015年9月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 修改结构体名
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ucRssiValue;       /*已转换为等级表示的信号强度*/
    VOS_UINT8        ucChannalQual;     /*误码率,只有在有业务的时候才有,若无
                                          效填99*/
    VOS_UINT16       usCellDlFreq;       /*小区频点(下行)*/
    VOS_UINT16       usCellUlFreq;       /*当前频点(上行)*/
    VOS_INT16        sUeRfPower;         /*发射功率,RRMM_UE_RFPOWER_INVALID无效值*/
    VOS_UINT8        aucReserved[3];
    TAF_SDC_SYS_MODE_ENUM_UINT8          enRat;                                 /*rssi上报时的接入技术*/
    /*驻留小区的信号质量*/
    union
    {
        TAF_SDC_2G_CELL_SIGN_INFO_STRU  st2GCellSignInfo;
        TAF_SDC_3G_CELL_SIGN_INFO_STRU  st3GCellSignInfo;
        TAF_SDC_4G_CELL_SIGN_INFO_STRU  st4GCellSignInfo;
    }u;
}TAF_SDC_3GPP_RSSI_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_3GPP2_RSSI_INFO_STRU
 结构说明  : 1X模块信号质量
 1.日    期   : 2015年9月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 增加
*****************************************************************************/
typedef struct
{
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU    st1xSigQualityRptInfo;      /* 当前1x的信号质量 */
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU  stHrpdSigQualityRptInfo;    /* 当前hrpd的信号质量 */
}TAF_SDC_3GPP2_SIG_QUALITY_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SIGNAL_QUALITY_INFO_STRU
 结构说明  : 信号质量信息
 1.日    期   : 2015年01月14日
   作    者   : m00312079
   修改内容   : 新建
 2.日    期   : 2015年10月13日
   作    者   : l00324781
   修改内容   : CDMA Iteration 18 修改
*****************************************************************************/
typedef struct
{
    TAF_SDC_3GPP_RSSI_INFO_STRU                st3GppRssiInfo;     /* 当前3GPP的信号质量 */

    TAF_SDC_3GPP2_SIG_QUALITY_INFO_STRU        st3Gpp2SigQuaInfo;    /* 当前是3GPP2的信号质量,包括hrpd和1x的信号质量，目前只有1x的 */
}TAF_SDC_SIG_QUALITY_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SYSTEM_INFO_STRU
 结构说明  : 3GPP2的系统信息
 1.日    期   : 2015年9月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 增加
*****************************************************************************/
typedef struct
{
    TAF_SDC_1X_SYS_INFO_STRU            st1xSysInfo;        /* 1X模块系统信息 */
}TAF_SDC_3GPP2_SYSTEM_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_APPSYSTEM_INFO_STRU
 结构说明  : 当前提供服务小区的系统信息，包括3GPP和3GPP2
 1.日    期   : 2015年9月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 增加
*****************************************************************************/
typedef struct
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;

    VOS_UINT8                           aucRsv[2];

    TAF_SDC_SERVICED_PLMN_INFO_STRU     stServPlmnInfo;     /* 3GPP的系统的当前提供服务小区的PLMN信息 */

    TAF_SDC_3GPP2_SYSTEM_INFO_STRU      st3Gpp2SysInfo;     /* 3GPP2相关系统的信息,hrpd和1x的，目前只包括1x的 */
}TAF_SDC_APPSYSTEM_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_APPNETWORK_INFO
 结构说明  : 上报给APP用的网络信息
 1.日    期   : 2014年10月17日
   作    者   : z00234330
   修改内容   : 上报给APP用的网络信息
 2.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
 3.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 修改
*****************************************************************************/
typedef struct
{
    TAF_SDC_SIG_QUALITY_INFO_STRU       stAppSigQuaInfo;    /* 当前提供服务小区的信号质量,包括3GPP和3GPP2的信号质量 */
    TAF_SDC_APPSYSTEM_INFO_STRU         stAppSysInfo;        /* 当前提供服务小区的系统信息，包括3GPP和3GPP2 */


    TAF_SDC_CS_DOMAIN_INFO_STRU         stCsDomainInfo;                         /*当前CS域信息*/
    TAF_SDC_PS_DOMAIN_INFO_STRU         stPsDomainInfo;                         /*当前PS域信息*/
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enReportSrvsta;                         /* UE的服务状态 ^srvst上报的服务状态*/
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enServiceDomain;                        /* UE的服务域sysinfo 查询时上报的服务域*/
    VOS_UINT8                           aucReserve[2];

}TAF_SDC_APPNETWORK_INFO;

/* Added by z00234330 for v8r2信号显示优化, 2014-10-17, end */


/*****************************************************************************
 结构名    : TAF_SDC_NETWORK_INFO_STRU
 结构说明  : 当前驻留的网络信息
 1.日    期   : 2013年3月28日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年12月03日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseI:gstMmaValue.stCerssiValue移到SDC中
 3.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
typedef struct
{
    TAF_SDC_SYS_INFO_STRU               stSysInfo;
    TAF_SDC_CS_DOMAIN_INFO_STRU         stCsDomainInfo;                         /* 当前CS域信息 */
    TAF_SDC_PS_DOMAIN_INFO_STRU         stPsDomainInfo;                         /* 当前PS域信息 */
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enReportSrvsta;                         /* UE服务状态^srvst上报的服务状态 */
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enServiceDomain;                        /* UE服务域sysinfo查询时上报的服务域 */
    VOS_UINT8                           aucReserved[2];
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, begin */
    TAF_SDC_NETWORK_CAP_INFO_STRU       stGuNwCapInfo;                          /* GU下网络业务能力信息 */
    TAF_SDC_NETWORK_CAP_INFO_STRU       stLteNwCapInfo;                         /* LTE下网络业务能力信息 */
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, end */

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    TAF_SDC_IMS_DOMAIN_INFO_STRU        stImsDomainInfo;                        /* IMS域的网络信息 */
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    TAF_SDC_SIG_QUALITY_INFO_STRU       stSigQuaInfo;

    VOS_INT32                           lSid;                                   /* 记录最近一次同步或驻留的SID, ID_XSD_MSCC_SID_IND发过来的SID信息 */

}TAF_SDC_NETWORK_INFO_STRU;

/* Added by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-22, end */

/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
/*****************************************************************************
 结构名    : TAF_SDC_ECALL_NUM_STRU
 结构说明  : ecall test/recfg number信息
 1.日    期   : 2014年4月3日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumType;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                           aucCallNumber[TAF_SDC_ECALL_BCD_NUM_MAX_LEN];
}TAF_SDC_ECALL_NUM_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ECALL_INFO_STRU
 结构说明  : 当前手机信息
 1.日    期   : 2014年4月3日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode;
    VOS_UINT8                           aucRsv[3];
    TAF_SDC_ECALL_NUM_STRU              stEcallNum;                             /* SDN文件获取的test number/reconfiguration number */
}TAF_SDC_ECALL_INFO_STRU;
/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */

/*****************************************************************************
 结构名    : TAF_SDC_UCIM_ECC_NUM_STRU
 结构说明  : Uim或CSIM卡文件中的紧急呼叫号码结构

 1.日    期   : 2014年11月18日
   作    者   : w00176964
   修改内容   : 1X项目新增结构

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccNumLen;                            /* 紧急呼号码长度 */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucEccNum[TAF_SDC_MAX_BCD_NUM_LEN];     /* 紧急呼号码 */
} TAF_SDC_UCIM_ECC_NUM_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_UCIM_ECC_NUM_LIST_STRU
 结构说明  : Uim或CSIM卡文件中的紧急呼叫号码列表

 1.日    期   : 2014年11月18日
   作    者   : w00176964
   修改内容   : 1X项目新增结构

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccNumCount;                                  /* 紧急号个数 */
    VOS_UINT8                           aucReseve[3];
    TAF_SDC_UCIM_ECC_NUM_STRU           astUcimEccNumList[TAF_SDC_MAX_UCIM_ECC_NUM];/* 紧急呼列表 */
} TAF_SDC_UCIM_ECC_NUM_LIST_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_CS_CALL_INFO_STRU
 结构说明  : 当前cc业务相关信息
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，增加IMS域呼叫是否存在标识
 3.日    期   : 2013年12月23日
   作    者   : y00245242
   修改内容   : 增加SRVCC缓存处理
 3.日    期   : 2014年4月9日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:增加呼ecall呼叫test/reconfiguration号码
 4.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : CDMA 1x项目迭代5修改
*****************************************************************************/
typedef struct
{
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    VOS_UINT8                           ucCsCallExistFlg;                       /* 当前是否处于呼叫过程中:VOS_TRUE  当前处于呼叫过程中
                                                                                                  VOS_FALSE 当前不处于呼叫过程中  */
    VOS_UINT8                           ucImsCallExistFlg;                      /* 当前是否处于呼叫过程中:VOS_TRUE  当前处于呼叫过程中
                                                                                                  VOS_FALSE 当前不处于呼叫过程中  */
    /* 删除SRVCC标志，移到CALL模块 */
    VOS_UINT8                           ucIsXsmsCallExistFlg;                   /* 当前是否处于呼叫过程中:VOS_TRUE  当前处于呼叫过程中*/

    VOS_UINT8                           ucCsEccExistFlg;                        /* 当前是否处于紧急呼叫过程中:VOS_TRUE  当前处于紧急呼叫过程中*/

    TAF_SDC_MM_EMERGENCY_LIST_STRU      stMmCallEmerNumList;                    /* MM带下来的紧急呼列表 */
    TAF_SDC_CUSTOM_ECC_CTX_STRU         stCustomCallEccNumCtx;                  /* 运营商定制的紧急呼列表 */

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-9, begin */
    TAF_SDC_ECALL_NUM_STRU              stEcallTestNumber;                      /* SDN文件获取的test number */
    TAF_SDC_ECALL_NUM_STRU              stEcallRecfgNumber;                     /* SDN文件获取的reconfiguration number */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-9, end */

    TAF_SDC_UCIM_ECC_NUM_LIST_STRU      st1xCallUcimEccNumList;                     /* 1X下面UIM或CSIM卡中的紧急呼叫号码列表 */

}TAF_SDC_CALL_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SMS_INFO_STRU
 结构说明  : 当前SMS业务相关信息
 1.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新建
 2.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，增加PS域和IMS短信是否存在标识
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsSmsSrvExistFlg;                     /* CS域的短信业务存在标识:VOS_TRUE  当前有CS域的短信业务
                                                                                   VOS_FALSE 当前没有CS域的短信业务  */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
    VOS_UINT8                           ucPsSmsSrvExistFlg;                     /* PS域的短信业务存在标识:VOS_TRUE  当前有PS域的短信业务
                                                                                   VOS_FALSE 当前没有PS域的短信业务  */
    VOS_UINT8                           ucImsSmsSrvExistFlg;                    /* IMS域的短信业务存在标识:VOS_TRUE  当前有IMS域的短信业务
                                                                                   VOS_FALSE 当前没有IMS域的短信业务  */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */
    VOS_UINT8                           aucReserved[1];
}TAF_SDC_SMS_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CS_SS_INFO_STRU
 结构说明  : 当前SS业务相关信息
 1.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新建
 2.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，增加IMS域补充业务是否存在标识
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsSsSrvExistFlg;                      /* CS域的补充业务存在标识:VOS_TRUE  当前有CS域的补充业务
                                                                                   VOS_FALSE 当前没有CS域的补充业务  */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    VOS_UINT8                           ucImsSsSrvExistFlg;                     /* IMS域的补充业务存在标识:VOS_TRUE  当前有IMS域的补充业务
                                                                                   VOS_FALSE 当前没有IMS域的补充业务  */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */
    VOS_UINT8                           aucReserved[2];
}TAF_SDC_SS_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_CS_INFO_STRU
 结构说明  : 当前cs相关信息
 1.日    期   : 2014年3月3日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsServiceConnStatusFlag;              /* cs业务信令连接是否存在标识 */
    VOS_UINT8                           ucReserved[3];                                                                                             VOS_UINT8                           aucReserved[2];
}TAF_SDC_CS_INFO_STRU;


/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
/*****************************************************************************
 结构名    : TAF_SDC_PS_INFO_STRU
 结构说明  : 当前ps相关信息
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPsServiceConnStatusFlag;              /* ps业务信令连接是否存在标识 */
    VOS_UINT8                           aucReserved[3];
}TAF_SDC_PS_INFO_STRU;

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 结构名    : TAF_SDC_EPS_INFO_STRU
 结构说明  : 当前eps相关信息
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEpsServiceConnStatusFlag;              /* eps业务信令连接是否存在标识 */
    VOS_UINT8                           aucReserved[3];
}TAF_SDC_EPS_INFO_STRU;
#endif
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */
/*******************************************************************************
 结构名    :TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_STRU
 结构说明  : union TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION成员stTrigPlmnSearchSrvTyp定义
             bit位置1表示该类型有效
1.日    期 : 2014年6月29日
  作    者 : z00161729
  修改内容 : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usCsMoNormalCall   :1;
    VOS_UINT16                           usCsMoEmgCall      :1;
    VOS_UINT16                           usCsMoSs           :1;
    VOS_UINT16                           usCsMoSms          :1;
    VOS_UINT16                           usPsConversatCall  :1;
    VOS_UINT16                           usPsStreamCall     :1;
    VOS_UINT16                           usPsInteractCall   :1;
    VOS_UINT16                           usPsBackGroundCall :1;
    VOS_UINT16                           usPsSubscribTrafficCall :1;
    VOS_UINT16                           usReserved7         :7;
}TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_STRU;

/*****************************************************************************
 枚举名    : TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION
 结构说明  : no rf触发搜网业务请求类型
1. 日    期: 2014年6月29日
   作    者: z00161729
   修改内容: 新建
*****************************************************************************/
typedef union
{
    VOS_UINT16                                usTrigPlmnSearchSrvType;

    TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_STRU    stTrigPlmnSearchSrvType;
}TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION;


/*****************************************************************************
 结构名    : TAF_SDC_SERVICE_INFO_STRU
 结构说明  : 当前业务相关信息
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新增短信和补充业务的信息
 3.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，SMS增加PS域信息
 4.日    期   : 2014年02月28日
   作    者   : z00161729
   修改内容   : DTS2014022800234:被叫mm收到paging会设置cs业务信令连接存在，
               但查询^usersrvstate时返回无cs业务，syscfgex设置失败回复存在cs业务，不一致
*****************************************************************************/
typedef struct
{
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
    TAF_SDC_CALL_INFO_STRU              stCallInfo;                               /* CC相关信息 */
    TAF_SDC_SMS_INFO_STRU               stSmsInfo;                              /* SMS相关信息 */
    TAF_SDC_SS_INFO_STRU                stSsInfo;                               /* SS相关信息 */
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

    TAF_SDC_CS_INFO_STRU                stCsInfo;                                                                                      VOS_UINT8                           aucReserved[2];

    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
    TAF_SDC_PS_INFO_STRU                stPsInfo;
#if (FEATURE_ON == FEATURE_LTE)
    TAF_SDC_EPS_INFO_STRU               stEpsInfo;
#endif
    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */
    TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION stTrigPlmnSrcSrvType;
    VOS_UINT8                               aucReserved1[2];

}TAF_SDC_SERVICE_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_ERRLOG_REPORT_CTRL_OCTET_STRU
 结构说明  : TAF_SDC_ERRLOG_REPORT_CTRL_OCTET_STRU信息
 1.日    期   : 2014年4月14日
   作    者   : n00269697
   修改内容   : CHR 优化项目
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitOpActiveRptFlag    :1;
    VOS_UINT8                           bitOpRatSwitchRptFlag :1;
    VOS_UINT8                           bitOpSpare            :6;
}TAF_SDC_ERRLOG_REPORT_CTRL_OCTET_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ERRLOG_CTRL_INFO_STRU
 结构说明  : TAF_SDC_ERRLOG_CTRL_INFO_STRU信息
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucErrLogCtrlFlag;                       /* ERRLOG打开标识 */
    TAF_SDC_ERRLOG_REPORT_CTRL_OCTET_STRU                   stErrLogRptCtrl;
    VOS_UINT16                                              usAlmLevel;                             /* 故障告警级别 */
}TAF_SDC_ERRLOG_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ERRLOG_BUFF_INFO_STRU
 结构说明  : TAF_SDC_ERRLOG_BUFF_INFO_STRU信息
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_RING_ID                          pstRingBuffer;                          /* MM层的共享缓存 */
    VOS_UINT32                          ulOverflowCnt;                          /* Ringbuf溢出的次数 */
}TAF_SDC_ERRLOG_BUFF_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ERRLOG_RAT_FREQUENTLY_SWITCH_INFO_STRU
 结构说明  : RAT频繁切换的信息结构
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNvStatisticTime;                      /* NV配置的统计时间 */
    VOS_UINT32                          ulNvSwitchNum;                          /* NV配置的gutl频繁切换的次数 */
    VOS_UINT8                           ucOldRatType;                           /* 最后入队元素的模式类型 */
    VOS_UINT8                           aucReserved[3];
    OM_RING_ID                          pstRingBuffer;                          /* 记录频繁切换记录的循环队列 */
}TAF_SDC_ERRLOG_RAT_FREQUENTLY_SWITCH_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ERRLOG_OOS_INFO_STRU
 结构说明  : 丢网信息结构
 1.日    期   : 2015年08月16日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsOosReportToAppFlag;                 /* CS域是否有上报过APP无服务 */
    VOS_UINT8                           ucPsOosReportToAppFlag;                 /* PS域是否有上报过APP无服务 */
    VOS_UINT8                           ucReportPowerOnBeginFlag;               /* 是否有上报过开机的CHR */
    VOS_UINT8                           ucReportPowerOffBeginFlag;              /* 是否有上报过关机的CHR */
}TAF_SDC_ERRLOG_OOS_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ERRLOG_INFO_STRU
 结构说明  : TAF_SDC_ERRLOG_INFO_STRU信息
 1.日    期   : 2013年08月27日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_ERRLOG_CTRL_INFO_STRU                       stCtrlInfo;
    TAF_SDC_ERRLOG_BUFF_INFO_STRU                       stBuffInfo;
    TAF_SDC_ERRLOG_RAT_FREQUENTLY_SWITCH_INFO_STRU      stRatFrequentlySwitchInfo;

    TAF_SDC_ERRLOG_OOS_INFO_STRU                        stOosInfo;

}TAF_SDC_ERRLOG_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CDMA_MNTN_STRU
 结构说明  : cdma 可维可测
 1.日    期   : 2015年11月10日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEsn;                              /* 32-bit */
    VOS_UINT8                           aucMeId[NAS_OM_MMA_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                           ucReserved;
}TAF_SDC_HARDWARE_INFO_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
/*****************************************************************************
 结构名    : TAF_SDC_PHONE_INFO_STRU
 结构说明  : 当前手机信息
 1.日    期   : 2013年12月25日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2015年02月04日
   作    者   : f00179208
   修改内容   : IMS动态开关配置项目
*****************************************************************************/
typedef struct
{
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhMode;

    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enImsSwitchState;

    VOS_UINT8                           aucRsv[2];

    TAF_SDC_HARDWARE_INFO_STRU          stHardWareInfo;
}TAF_SDC_PHONE_INFO_STRU;
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

/*****************************************************************************
 结构名    : TAF_SDC_REG_REPORT_STATUS_STRU
 结构说明  : 记录当前CS/PS设置的注册状态上报方式
 1.日    期   : 2014年8月18日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_CREG_TYPE_ENUM_UINT8        enCregType;
    TAF_SDC_CGREG_TYPE_ENUM_UINT8       enCgregType;
    TAF_SDC_CEREG_TYPE_ENUM_UINT8       enCeregType;
    VOS_UINT8                           aucRsv;
}TAF_SDC_REG_REPORT_STATUS_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CSIM_INFO_STRU
 结构说明  : 记录CSIM卡信息
 1.日    期   : 2015年2月7日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_SIM_STATUS_STRU             stCsimStatus;                           /* 卡状态 */
    TAF_SDC_SIM_MS_IDENTITY_STRU        stMsIdentity;                           /* MS Identity信息 */
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;                              /* 卡类型 */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucRuimid[TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT];
}TAF_SDC_CSIM_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ICCID_INFO_STRU
 结构说明  : 记录卡ICCID信息
 1.日    期   : 2015年8月26日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucIccId[TAF_SDC_ICC_ID_MAX_NUM + 1];
} TAF_SDC_ICCID_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CARD_INFO_STRU
 结构说明  : 记录卡信息
 1.日    期   : 2015年2月7日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_USIM_INFO_STRU              stUsimInfo;
    TAF_SDC_CSIM_INFO_STRU              stCsimInfo;
    TAF_SDC_ICCID_INFO_STRU             stIccIdInfo;
}TAF_SDC_CARD_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_OPERATOR_NAME_STRU
 结构说明  : 运营商名称结构
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitExt    : 1;
    VOS_UINT8                           bitCoding : 3;    /* 编码格式 */
    VOS_UINT8                           bitAddCi  : 1;
    VOS_UINT8                           bitSpare  : 3;    /* spare bit */
    VOS_UINT8                           ucLength;         /* 运营商名称长度 */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucOperatorName[TAF_SDC_MAX_OPER_NAME_NUM];/* 运营商的名称 */
}TAF_SDC_OPERATOR_NAME_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_OPL_RECORD_INFO_STRU
 结构说明  : OPL文件每条记录的内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stPlmnId;
    VOS_UINT16                          usLacRangeLow;
    VOS_UINT16                          usLacRangeHigh;
    VOS_UINT16                          usPnnIndex;
}TAF_SDC_OPL_RECORD_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_OPL_FILE_INFO_STRU
 结构说明  : 记录OPL文件内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulOplRecordNum;
    VOS_UINT32                          ulOplEfLen;
    TAF_SDC_OPL_RECORD_INFO_STRU        astOplRecordInfo[TAF_SDC_OPL_MAX_RECORD_NUM];
}TAF_SDC_OPL_FILE_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_PNN_RECORD_INFO_STRU
 结构说明  : PNN文件每条记录的内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameShort;/* 运营商的短名称 */
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameLong;  /* 运营商的长名称 */
    VOS_UINT8                           aucPlmnAdditionalInfo[TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN];                                                        /*PLMN Additional Information (coded using one of the UCS2 code options as defined in TS 31.101 [11]).*/
    VOS_UINT8                           ucPlmnAdditionalInfoLen;       /*PLMN Additional Information 长度 */
    VOS_UINT8                           aucReserve[1];
}TAF_SDC_PNN_RECORD_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_PNN_FILE_INFO_STRU
 结构说明  : 记录PNN文件内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPnnRecordNum;
    VOS_UINT32                          ulPnnEfLen;
    TAF_SDC_PNN_RECORD_INFO_STRU        astPnnRecordInfo[TAF_SDC_PNN_MAX_RECORD_NUM];
}TAF_SDC_PNN_FILE_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CPHS_FILE_INFO_STRU
 结构说明  : 记录CPHS文件内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_OPERATOR_NAME_STRU          stCPHSOperName;
}TAF_SDC_CPHS_FILE_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SPN_FILE_INFO_STRU
 结构说明  : 记录SPN文件内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                         ucDispRplmnMode;
    VOS_UINT8                         aucReserve[3];
    TAF_SDC_OPERATOR_NAME_STRU        stSpnOperName;
}TAF_SDC_SPN_FILE_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_SPDI_FILE_INFO_STRU
 结构说明  : 记录SPDI文件内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucServiceProviderPlmnNum;
    VOS_UINT8                           aucReserve[3];
    TAF_SDC_PLMN_ID_STRU                astSeriveProviderPlmn[TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM];
}TAF_SDC_SPDI_FILE_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_MM_INFO_STRU
 结构说明  : 记录mm/gmm/emm information消息内容
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stOperatorPlmnId;
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameShort;         /* 当前驻留网络运营商的短名称 */
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameLong;          /* 当前驻留网络运营商的长名称 */
}TAF_SDC_MM_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CUSTOM_OPER_NAME_STRU
 结构说明  : 记录50024 nv项记录的运营商定制的名称
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stOperatorPlmnId;
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameShort;         /* 当前驻留网络运营商的短名称 */
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameLong;          /* 当前驻留网络运营商的长名称 */
}TAF_SDC_CUSTOM_OPER_NAME_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU
 结构说明  : 记录50024 nv项记录的运营商定制的名称
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_CUSTOM_OPER_NAME_STRU   astCustomOperName[TAF_NVIM_STORED_OPER_NAME_NUM];
}TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU;



/*****************************************************************************
 结构名    : TAF_SDC_OPER_NAME_TYPE_PRIO_STRU
 结构说明  : 运营商名称显示优先级信息
 1.日    期   : 2015年2月11日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucOperNamePrioNum;
    VOS_UINT8                                   aucReserved[3];
    TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8           aucOperNameTypePrio[TAF_SDC_MAX_OPER_NAME_PRIO_NUM];
}TAF_SDC_OPER_NAME_TYPE_PRIO_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_ENHANCED_OPERATOR_NAME_INFO
 结构说明  : 记录运营商名称相关信息
 1.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU     stOperNameTypePrio;   /* cops或^eonsucs2查询从PNN或SPN或CPHS或NITZ获取先后顺序优先级*/
    TAF_SDC_OPL_FILE_INFO_STRU           stUsimOplFileInfo;    /* Usim中的OPL文件0x6FC6信息 */
    TAF_SDC_OPL_FILE_INFO_STRU           stSimOplFileInfo;     /* Sim中的OPL文件0x6FC6信息 */
    TAF_SDC_PNN_FILE_INFO_STRU           stUsimPnnFileInfo;    /* Usim中的PNN文件0x6FC5信息 */
    TAF_SDC_PNN_FILE_INFO_STRU           stSimPnnFileInfo;     /* Sim中的PNN文件0x6FC5信息 */
    TAF_SDC_CPHS_FILE_INFO_STRU          stCphsFileInfo;       /* CPHS文件0x6F14信息 */
    TAF_SDC_SPN_FILE_INFO_STRU           stUsimSpnFileInfo;    /* Usim中的SPN文件0x6f46信息 */
    TAF_SDC_SPN_FILE_INFO_STRU           stSimSpnFileInfo;     /* Sim中的SPN文件0x6f46信息 */
    TAF_SDC_SPDI_FILE_INFO_STRU          stUsimSpdiFileInfo;   /* USIM中SPDI文件0x6FCD信息*/
    TAF_SDC_SPDI_FILE_INFO_STRU          stSimSpdiFileInfo;    /* SIM中SPDI文件0x6FCD信息*/
    TAF_SDC_MM_INFO_STRU                 stMmInfo;             /* 记录MM/GMM/EMM info消息中的信息*/
    TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU   stCustomOperNameInfo; /* 50024 nv中配置的运营商定制名称 */
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8  enCopsFormatType;
    VOS_CHAR                             cWildCard;             /* 通配符,取值a-f,可代表0-9任意数字 */
    VOS_UINT8                            aucReserved[2];
}TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_SDC_CDMA_MNTN_STRU
 结构说明  : cdma 可维可测
 1.日    期   : 2015年11月10日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCdmaStatusReportSuport;           /* 0:不支持上报 other:支持上报*/
    VOS_UINT32                          ulRptPeriod;                        /*可维可测上报周期*/
}TAF_SDC_CDMA_MNTN_STRU;

/*****************************************************************************
 结构名    : TAF_SDC_CTX_STRU
 结构说明  : SDC_CTX信息
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新建
 2.日    期   : 2013年3月22日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核项目把mmc部分全局变量移至sdc
 3.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : SS FDN&Call Control:增加业务相关信息
 4.日    期   : 2014年11月24日
   作    者   : s00217060
   修改内容   : Service_State_Optimize_PhaseI修改
 5.日    期   : 2015年2月9日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
typedef struct
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-22, begin */
    TAF_SDC_CARD_INFO_STRU              stSimInfo;                              /* 卡相关信息 */
    TAF_SDC_MS_CFG_INFO_STRU            stMsCfgInfo;                            /* MS的配置信息 */
    TAF_SDC_NETWORK_INFO_STRU           stNetworkInfo;                          /* 当前驻留的网络信息 */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-22, end */
    TAF_SDC_SERVICE_INFO_STRU           stServiceInfo;                          /* 当前业务相关信息 */

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
    TAF_SDC_PHONE_INFO_STRU             stPhoneInfo;
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

    TAF_SDC_ERRLOG_INFO_STRU            stErrlogInfo;

    TAF_SDC_REG_REPORT_STATUS_STRU      stRegReportStatus;

    TAF_SDC_APPNETWORK_INFO             stAppNetworkInfo;                       /* 上报给APP用的网络信息，不实时更新 */

    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU stEnhancedOperatorNameInfo;

    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8     enCasState;
    VOS_UINT8                                aucRsv[3];

    TAF_SDC_CDMA_MNTN_STRU              stCdmaMntn;
}TAF_SDC_CTX_STRU;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
/*****************************************************************************
结构名    : TAF_SDC_CELL_SIGN_REPORT_CFG_STRU
结构说明  : 信号质量主动上报相关配置信息
1.日    期  : 2013年5月7日
  作    者  : s00217060
  修改内容  : 支持^cerssi新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSignThreshold;                        /* 信号变化门限,当RSSI变化超过该值，接入层需要主动上报信号质量，取值0表示接入层按默认值处理 */
    VOS_UINT8                           ucMinRptTimerInterval;                  /* 间隔上报的时间   */
} TAF_SDC_CELL_SIGN_REPORT_CFG_STRU;

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, begin */
/* call state NV删除，call state的上报由curc统一控制 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, end */

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
TAF_SDC_CTX_STRU*  TAF_SDC_GetSdcCtx( VOS_VOID );

TAF_SDC_MS_CAP_INFO_STRU*  TAF_SDC_GetMsCapInfo( VOS_VOID );

TAF_SDC_PLATFORM_RAT_CAP_STRU*  TAF_SDC_GetPlatformRatCap( VOS_VOID );

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
TAF_SDC_CURC_RPT_CTRL_STRU*  TAF_SDC_GetCurcRptCtrl( VOS_VOID );
TAF_SDC_UNSOLICITED_RPT_CTRL_STRU*  TAF_SDC_GetUnsolicitedRptCtrl( VOS_VOID );
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetGuNwCapInfo
 功能描述  : get GU network capability infomation
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回保存的网络能力参数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetGuNwCapInfo(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_SDC_GetLteNwCapInfo
 功能描述  : get LTE network capability infomation
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回保存的网络能力参数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetLteNwCapInfo(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_SDC_SetGuNwCapInfo
 功能描述  : set GU network capability infomation
 输入参数  : pstNwCapInfo 网络能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetGuNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo);

/*****************************************************************************
 函 数 名  : TAF_SDC_SetLteNwCapInfo
 功能描述  : set LTE network capability infomation
 输入参数  : pstNwCapInfo 网络能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo);
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, end */


VOS_VOID TAF_SDC_InitMsCapInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CAP_INFO_STRU            *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitCtx(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_CTX_STRU                    *pstSdcCtx
);

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetSysMode( VOS_VOID );
VOS_VOID TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode);
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetSysSubMode( VOS_VOID );
VOS_VOID TAF_SDC_SetSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode);
TAF_SDC_3GPP_SYS_INFO_STRU* TAF_SDC_Get3gppSysInfo( VOS_VOID );
TAF_SDC_SYS_INFO_STRU* TAF_SDC_GetSysInfo( VOS_VOID );
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetCsServiceStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus);
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetPsServiceStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus);
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetServiceDomain( VOS_VOID );
VOS_VOID TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain);
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetCsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetCsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus);
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetPsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetPsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus);
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetAppCsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus);
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetAppPsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus);
VOS_UINT8* TAF_SDC_GetSimImsi( VOS_VOID );
VOS_UINT8* TAF_SDC_GetCsimImsi( VOS_VOID );
VOS_VOID TAF_SDC_SetSimImsi( VOS_UINT8 *pstImsi );

VOS_UINT8* TAF_SDC_GetLastSimImsi( VOS_VOID );
VOS_VOID TAF_SDC_SetLastSimImsi( VOS_UINT8 *pstImsi );

TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetSimStatus( VOS_VOID );

/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */

TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetSimType( VOS_VOID );
/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */
VOS_VOID TAF_SDC_SetCurrCampPlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId);
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetCurrCampPlmnId(VOS_VOID);


VOS_UINT16 TAF_SDC_GetCurrCampLac(VOS_VOID);

VOS_UINT8 TAF_SDC_GetCurrCampRac(VOS_VOID);
VOS_UINT32 TAF_SDC_GetCurrCampCellId(VOS_VOID);

TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetServiceStatus(VOS_VOID);

VOS_VOID TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta);


VOS_VOID TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain);
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetAppServiceDomain( VOS_VOID );
VOS_VOID TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta);
TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetAppServiceStatus(VOS_VOID);
VOS_VOID TAF_SDC_SetCurrCampLac(VOS_UINT16 usLac);
VOS_VOID TAF_SDC_SetCurrCampRac(VOS_UINT8 ucRac);
VOS_VOID TAF_SDC_SetCurrCampCellId(VOS_UINT32 ulCellId);
VOS_VOID TAF_SDC_SetCsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstCsAcRetriction);
VOS_VOID TAF_SDC_SetPsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstPsAcRetriction);
TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetCsAcRestriction(VOS_VOID);

TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetPsAcRestriction(VOS_VOID);

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 TAF_SDC_GetCurrLmmAccessType(VOS_VOID);
VOS_VOID TAF_SDC_SetCurrLmmAccessType(TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 enAccessType);


/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
VOS_VOID TAF_SDC_InitCurcRptCtrlInfo(VOS_VOID);
VOS_VOID TAF_SDC_InitUnsolicitedRptCtrlInfo(VOS_VOID);
VOS_VOID TAF_SDC_ReadCellSignReportCfgNV( VOS_VOID );
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
VOS_UINT8   TAF_SDC_GetCsCallExistFlg(VOS_VOID);
VOS_VOID    TAF_SDC_SetCsCallExistFlg(
    VOS_UINT8                           ucInCall
);
VOS_VOID    TAF_SDC_SetImsCallExistFlg(
    VOS_UINT8                           ucImsCallExistFlg
);
VOS_UINT8   TAF_SDC_GetImsCallExistFlg(VOS_VOID);
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

VOS_VOID    TAF_SDC_SetCsEccExistFlg(
    VOS_UINT8                           ucCsEccExistFlg
);
VOS_UINT8 TAF_SDC_GetCsEccExistFlg(VOS_VOID);

/* 删除SRVCC标志，移到CALL模块 */

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
TAF_SDC_CALL_INFO_STRU* TAF_SDC_GetCallInfo(VOS_VOID);
VOS_VOID TAF_SDC_SetMmCallEmerNumList(
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList
);
TAF_SDC_MM_EMERGENCY_LIST_STRU* TAF_SDC_GetMmCallEmerNumList(VOS_VOID);
VOS_VOID TAF_SDC_SetCustomCallEccNumCtx(
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEccNumCtx
);
TAF_SDC_CUSTOM_ECC_CTX_STRU* TAF_SDC_GetCustomCallEccNumCtx(VOS_VOID);
VOS_CHAR** TAF_SDC_GetCallEmerNumsNoUsimTblAddr(VOS_VOID);
VOS_CHAR** TAF_SDC_GetCallEmerNumsWithUsimTblAddr(VOS_VOID);

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_CHAR** TAF_SDC_GetCdmaCallEmcNumsAddr(VOS_VOID);
#endif

VOS_VOID   TAF_SDC_SetUssdTransMode(
    VOS_UINT8                           ucTransMode
);
VOS_UINT8   TAF_SDC_GetUssdTransMode(VOS_VOID);

VOS_VOID TAF_SDC_InitUssdCfgInfo(VOS_VOID);

VOS_VOID TAF_SDC_ReadUssdTransModeNvim(VOS_VOID);
VOS_VOID TAF_SDC_ReadUssdTransTableNvim(VOS_VOID);

VOS_VOID TAF_SDC_InitServiceInfo(
    TAF_SDC_SERVICE_INFO_STRU          *pstServiceInfo
);

VOS_UINT8 TAF_SDC_GetCsServiceConnStatusFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetCsServiceConnStatusFlag(
    VOS_UINT8                           ucCsServiceConnStatusFlag
);


TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION *TAF_SDC_GetTrigPlmnSearchSrvType(VOS_VOID);


/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
VOS_VOID TAF_SDC_InitCallInfo(
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo
);
VOS_VOID TAF_SDC_ReadCustomEccNumListNvim(VOS_VOID);

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-27, begin */
VOS_VOID TAF_SDC_InitAppCfgSupportType(VOS_VOID);

VOS_VOID TAF_SDC_InitGuNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstGuNwCapInfo
);
VOS_VOID TAF_SDC_InitLteNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstLteNwCapInfo
);
VOS_VOID TAF_SDC_InitNetWorkInfo(
    TAF_SDC_NETWORK_INFO_STRU *pstNetworkInfo
);

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-27, end */

/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
VOS_VOID TAF_SDC_InitCsInfo(TAF_SDC_CS_INFO_STRU *pstCsInfo);
VOS_VOID TAF_SDC_InitPsInfo(TAF_SDC_PS_INFO_STRU *pstPsInfo);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_SDC_InitEpsInfo(TAF_SDC_EPS_INFO_STRU *pstEpsInfo);
#endif
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */


/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, begin */
VOS_VOID TAF_SDC_InitUeUsageSetting(VOS_VOID);
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, end */

VOS_UINT8   TAF_SDC_Get7BitToAssicTableType(VOS_VOID);
VOS_VOID    TAF_SDC_Set7BitToAssicTableType(
    VOS_UINT8                           ucType
);

VOS_UINT8*   TAF_SDC_GetCurr7BitToAsciiTableAddr(VOS_VOID);

VOS_VOID TAF_SDC_Get3GppCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
);

VOS_VOID TAF_SDC_GetCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_SDC_Get3Gpp2CurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
);
#endif



VOS_VOID    TAF_SDC_SetSvlteSupportFlag(
    VOS_UINT8                           ucSvlteSupportFlag
);
VOS_UINT8   TAF_SDC_GetSvlteSupportFlag(VOS_VOID);
VOS_VOID    TAF_SDC_SetCsSmsSrvExistFlg(
    VOS_UINT8                           ucCsSmsSrvExistFlg
);
VOS_UINT8   TAF_SDC_GetCsSmsSrvExistFlg(VOS_VOID);
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
VOS_VOID TAF_SDC_SetPsSmsSrvExistFlg(
    VOS_UINT8                           ucPsSmsSrvExistFlg
);
VOS_UINT8 TAF_SDC_GetPsSmsSrvExistFlg(VOS_VOID);
VOS_VOID TAF_SDC_SetImsSmsSrvExistFlg(
    VOS_UINT8                           ucImsSmsSrvExistFlg
);
VOS_UINT8 TAF_SDC_GetImsSmsSrvExistFlg(VOS_VOID);
VOS_VOID    TAF_SDC_SetImsSsSrvExistFlg(
    VOS_UINT8                           ucImsSsSrvExistFlg
);
VOS_UINT8   TAF_SDC_GetImsSsSrvExistFlg(VOS_VOID);
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */
VOS_VOID    TAF_SDC_SetCsSsSrvExistFlg(
    VOS_UINT8                           ucCsSsSrvExistFlg
);
VOS_UINT8   TAF_SDC_GetCsSsSrvExistFlg(VOS_VOID);
VOS_VOID TAF_SDC_InitSvlteSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);


/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, begin */
VOS_VOID TAF_SDC_InitImsRatSupport(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
VOS_VOID TAF_SDC_InitImsCapability(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitVoiceDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitSmsDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitImsConfigPara(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitLteCsServiceCfg(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitRedialCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitImsRoamingCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitImsUssdCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
/* Added by w00167002 for L-C互操作项目, 2014-2-15, begin */
VOS_VOID TAF_SDC_InitLcConfigPara(
    TAF_SDC_LC_CONFIG_PARA_STRU        *pstLcConfigPara
);
/* Added by w00167002 for L-C互操作项目, 2014-2-15, end */

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

VOS_VOID TAF_SDC_SetGsmImsSupportFlag(
    VOS_UINT8                          ucGsmImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetGsmImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetUtranImsSupportFlag(
    VOS_UINT8                          ucUtranImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetUtranImsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetLteImsSupportFlag(
    VOS_UINT8                           ucImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetLteImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetAppCfgSupportType(
    VOS_UINT16                          usAppCfgSupportType
);
VOS_UINT16 TAF_SDC_GetAppCfgSupportType(VOS_VOID);

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, end */

VOS_VOID TAF_SDC_SetCsAttachAllowFlg(VOS_UINT8 ucCsAttachAllowFlg);
VOS_UINT8 TAF_SDC_GetCsAttachAllowFlg(VOS_VOID);


OM_RING_ID TAF_SDC_GetErrLogRingBufAddr(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer);
VOS_UINT8 TAF_SDC_GetErrlogCtrlFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogCtrlFlag(VOS_UINT8 ucFlag);
VOS_UINT16 TAF_SDC_GetErrlogAlmLevel(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel);
VOS_UINT32 TAF_SDC_GetErrlogOverflowCnt(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt);

VOS_UINT8 TAF_SDC_GetErrLogCsOosReportToAppFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_SDC_GetErrLogPsOosReportToAppFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOnBeginFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOffBeginFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_UINT8 ucFlag);

VOS_UINT8 TAF_SDC_GetErrlogActiveRptFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogActiveRptFlag(VOS_UINT8 ucActiveRptFlag);
VOS_UINT8 TAF_SDC_GetErrlogRatSwitchRptFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_UINT8 ucRatSwitchRptFlag);
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticTime(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticTime(
    VOS_UINT32                           ulStatisticTime
);
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticNum(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticNum(
    VOS_UINT32                           ulSwitchNum
);
VOS_VOID TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim(VOS_VOID);
VOS_UINT8 TAF_SDC_GetErrLogOldRatType(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogOldRatType(
    VOS_UINT8                           ucRatType
);
OM_RING_ID TAF_SDC_GetRatSwitchRingBufAddr(VOS_VOID);
VOS_VOID TAF_SDC_SetRatSwitchRingBufAddr(
    OM_RING_ID                          pRingBuffer
);
VOS_VOID TAF_SDC_ReadErrlogCtrlInfoNvim(VOS_VOID);
VOS_VOID TAF_SDC_InitErrLogInfo(
    TAF_SDC_ERRLOG_INFO_STRU           *pstErrLogInfo
);
#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 TAF_SDC_PutRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 TAF_SDC_RatSwitchRingBufRemoveRecord(
    VOS_UINT32                          ulbytes
);
VOS_UINT32 TAF_SDC_GetRecordFromRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 TAF_SDC_GetRatSwitchRingBufferFreeBytes(VOS_VOID);
VOS_VOID TAF_SDC_CleanRatSwitchRingBuf(VOS_VOID);

VOS_VOID TAF_SDC_CreatRatSwitchRingBuf(VOS_VOID);
extern VOS_UINT32 TAF_SDC_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_UINT32 TAF_SDC_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_UINT32 TAF_SDC_GetErrLogRingBufferUseBytes(VOS_VOID);

extern VOS_VOID TAF_SDC_CleanErrLogRingBuf(VOS_VOID);
#endif

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
VOS_VOID TAF_SDC_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                          ucVoiceCallOnImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetVoiceCallOnImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetSmsOnImsSupportFlag(
    VOS_UINT8                          ucSmsOnImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetSmsOnImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                          ucVideoCallOnImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetVideoCallOnImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);
TAF_SDC_VOICE_DOMAIN_ENUM_UINT32 TAF_SDC_GetVoiceDomain(VOS_VOID);
VOS_VOID TAF_SDC_SetSmsDomain(
    TAF_SDC_SMS_DOMAIN_ENUM_UINT8      enSmsDomain
);
TAF_SDC_SMS_DOMAIN_ENUM_UINT8 TAF_SDC_GetSmsDomain(VOS_VOID);
VOS_VOID TAF_SDC_SetLteEmsSupportFlag(
    VOS_UINT8                           ucLteEmsSupportFlag
);
VOS_UINT8 TAF_SDC_GetLteEmsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetLteCsSeviceCap(
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCap
);
TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8 TAF_SDC_GetLteCsSeviceCap(VOS_VOID);
TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 TAF_SDC_GetUeUsageSetting(VOS_VOID);
VOS_VOID TAF_SDC_SetUeUsageSetting(
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8   enUeUsageSetting
);

VOS_UINT8 TAF_SDC_GetRoamFlag(VOS_VOID);
VOS_VOID  TAF_SDC_SetRoamFlag(VOS_UINT8 ucRoamFlag);

VOS_UINT8 TAF_SDC_GetCampOnFlag( VOS_VOID );
VOS_VOID  TAF_SDC_SetCampOnFlag(VOS_UINT8 ucCampOnFlg);



VOS_VOID TAF_SDC_Set3GppRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
);

VOS_UINT8 TAF_SDC_Get3GppRfAvailFlag(VOS_VOID);

VOS_VOID TAF_SDC_Set1xRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
);

VOS_UINT8 TAF_SDC_Get1xRfAvailFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetHrpdRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
);

VOS_UINT8 TAF_SDC_GetHrpdRfAvailFlag(VOS_VOID);




TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetCampSysMode( VOS_VOID );

VOS_UINT8 TAF_SDC_GetSimCsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetSimCsRegStatus(
    VOS_UINT8       ucSimCsRegStatus
);


VOS_UINT8 TAF_SDC_GetSimPsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetSimPsRegStatus(
    VOS_UINT8       ucSimPsRegStatus
);

TAF_SDC_RAT_PRIO_STRU* TAF_SDC_GetMsPrioRatList( VOS_VOID );
VOS_VOID TAF_SDC_SetMsPrioRatList(
    TAF_SDC_RAT_PRIO_STRU              *pstPrioRatList
);

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
VOS_UINT8 TAF_SDC_GetCallRedailFromImsToCsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetCallRedailFromImsToCsSupportFlag(VOS_UINT8 ucCallRedialFromImsToCs);

VOS_UINT8 TAF_SDC_GetSmsRedailFromImsToCsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetSmsRedailFromImsToCsSupportFlag(VOS_UINT8 ucSmsRedialFromImsToCs);

VOS_UINT8 TAF_SDC_GetRoamingSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetRoamingSupportFlag(VOS_UINT8 ucRoamingSupport);
/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
VOS_VOID    TAF_SDC_SetImsNormalRegStatus(
    TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8    enRegStatus
);

TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8   TAF_SDC_GetImsNormalRegStatus(VOS_VOID);


VOS_VOID  TAF_SDC_SetCurPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
);

TAF_SDC_PHONE_MODE_ENUM_UINT8  TAF_SDC_GetCurPhoneMode(VOS_VOID);

TAF_SDC_CREG_TYPE_ENUM_UINT8  TAF_SDC_GetCregType(VOS_VOID);

TAF_SDC_CGREG_TYPE_ENUM_UINT8  TAF_SDC_GetCgregType(VOS_VOID);

TAF_SDC_CEREG_TYPE_ENUM_UINT8  TAF_SDC_GetCeregType(VOS_VOID);

VOS_VOID  TAF_SDC_SetCregType(TAF_SDC_CREG_TYPE_ENUM_UINT8 enCregType);

VOS_VOID  TAF_SDC_SetCgregType(TAF_SDC_CGREG_TYPE_ENUM_UINT8 enCgregType);

VOS_VOID  TAF_SDC_SetCeregType(TAF_SDC_CEREG_TYPE_ENUM_UINT8 enCeregType);

/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallTestNumber(VOS_VOID);
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallRecfgNumber(VOS_VOID);
TAF_SDC_CALL_MODE_ENUM_UINT8            TAF_SDC_GetCurCallMode(VOS_VOID);
VOS_VOID  TAF_SDC_SetCurCallMode(
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode
);
#endif
/* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */

VOS_VOID TAF_SDC_InitPhoneInfo(
    TAF_SDC_PHONE_INFO_STRU            *pstPhInfo
);

VOS_VOID TAF_SDC_InitRegReportStatus(
    TAF_SDC_REG_REPORT_STATUS_STRU     *pstRegReportStatus
);


VOS_VOID TAF_SDC_InitDsdaPlmnSearchEnhancedCfg(VOS_VOID);

VOS_UINT8 TAF_SDC_GetPsAttachAllowFlg(VOS_VOID);
VOS_VOID TAF_SDC_SetPsAttachAllowFlg(VOS_UINT8 ucPsAttachAllowFlg);


VOS_VOID  TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8  ucUtranSkipWPlmnSearchFlag);
VOS_UINT8  TAF_SDC_GetUtranSkipWPlmnSearchFlag(VOS_VOID);


VOS_UINT8 TAF_SDC_GetUssdOnImsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetUssdOnImsSupportFlag(VOS_UINT8 ucUssdOnImsSupportFlag);
/* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */
VOS_VOID TAF_SDC_SetLCEnableFlg(
    VOS_UINT8                           ucLCEnableFlg
);

VOS_UINT8 TAF_SDC_GetLCEnableFlg(VOS_VOID);

VOS_UINT8 TAF_SDC_GetLCWorkCfg(VOS_VOID);
VOS_VOID   TAF_SDC_SetLCWorkCfg(
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8     enLCWorkCfg
);
/* Added by s00261364 for L-C互操作项目, 2014-1-27, end */

/* Added by m00217266 for L-C互操作项目, 2014-2-12, begin */
VOS_UINT8 TAF_SDC_GetLCRatCombined(VOS_VOID);
/* Added by m00217266 for L-C互操作项目, 2014-2-12, end */

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
TAF_SDC_LC_CONFIG_PARA_STRU* TAF_SDC_GetLcConfigPara(VOS_VOID);
/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

VOS_VOID TAF_SDC_SaveCsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
);

VOS_VOID TAF_SDC_SaveUsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
);

VOS_VOID TAF_SDC_SaveUsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enUsimStatus
);

VOS_VOID TAF_SDC_SaveCsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCsimStatus
);

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-26, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_SDC_InitECallNumber(
    TAF_SDC_ECALL_NUM_STRU             *pstECallNumber
);
#endif

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-26, end */

/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
VOS_VOID TAF_SDC_SetPsServiceConnStatusFlag(
    VOS_UINT8                           ucPsServiceConnStatusFlag
);
VOS_UINT8 TAF_SDC_GetPsServiceConnStatusFlag(VOS_VOID);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_SDC_SetEpsServiceConnStatusFlag(
    VOS_UINT8                           ucEpsServiceConnStatusFlag
);
VOS_UINT8 TAF_SDC_GetEpsServiceConnStatusFlag(VOS_VOID);
#endif
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */
#if (FEATURE_ON == FEATURE_BASTET)
VOS_UINT8   TAF_SDC_GetBastetSupportFlag(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_SDC_Set1xCallUcimEmccNumList(
    TAF_SDC_UCIM_ECC_NUM_LIST_STRU     *pstUcimEccNumList
);

TAF_SDC_UCIM_ECC_NUM_LIST_STRU* TAF_SDC_Get1xCallUcimEmccNumList(VOS_VOID);

VOS_INT32 TAF_SDC_Get1xSid(VOS_VOID);

VOS_INT32 TAF_SDC_Get1xNid(VOS_VOID);

VOS_UINT8 TAF_SDC_Get1xRoamingFlag(VOS_VOID);

VOS_VOID TAF_SDC_Set1xSysInfo(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU          *pSysInfo
);

TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_Get1xSysInfo(VOS_VOID);
TAF_SDC_HRPD_SYS_INFO_STRU* TAF_SDC_GethrpdSysInfo(VOS_VOID);


TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_Get1xSigQualityInfo(VOS_VOID);
VOS_VOID TAF_SDC_Init1xSigQualityRptValue(VOS_VOID);

TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU* TAF_SDC_GetHrpdSigQualityInfo(VOS_VOID);
VOS_VOID TAF_SDC_InitHrpdSigQualityRptValue(VOS_VOID);


VOS_UINT8 TAF_SDC_Get1xPrevInUse(VOS_VOID);

VOS_UINT16 TAF_SDC_Get1xChan(VOS_VOID);
VOS_VOID TAF_SDC_SetXCaLLState(
    NAS_OM_1X_CALL_STATE_ENUM_UINT8        enXCallState
);
NAS_OM_1X_CALL_STATE_ENUM_UINT8 TAF_SDC_GetXCallState(
    VOS_VOID
);
VOS_VOID TAF_SDC_SetCdmaStatusReportPeriod(
    VOS_UINT32                          ulRptPeriod
);
VOS_UINT32  TAF_SDC_GetCdmaStatusReportPeriod(
    VOS_VOID
);
VOS_VOID TAF_SDC_Init1xSysInfo(
    TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo
);
VOS_VOID TAF_SDC_InitHrpdSysInfo(
    TAF_SDC_HRPD_SYS_INFO_STRU         *pstHrpdSysInfo
);

#endif

VOS_VOID TAF_SDC_InitAppSysMode(VOS_VOID);
VOS_VOID TAF_SDC_InitAppSysSubMode(VOS_VOID);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_SDC_InitAppNetwork_Info(TAF_SDC_APPNETWORK_INFO *pstAppNetworkInfo);
VOS_VOID TAF_SDC_InitNetworkRssiValue( TAF_SDC_SIG_QUALITY_INFO_STRU    *pstSigQuaInfo);
VOS_VOID TAF_SDC_InitAppNetworkPlmnInfo(TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstServPlmnInfo);
#endif

TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetUsimOplFileInfo(VOS_VOID);
VOS_VOID TAF_SDC_SetCopsFormatType(
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8                     enCopsFormatType
);
TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 TAF_SDC_GetCopsFormatType(VOS_VOID);

TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetSimOplFileInfo(VOS_VOID);
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetUsimPnnFileInfo(VOS_VOID);
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetSimPnnFileInfo(VOS_VOID);
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetUsimSpnFileInfo(VOS_VOID);
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetSimSpnFileInfo(VOS_VOID);
TAF_SDC_CPHS_FILE_INFO_STRU* TAF_SDC_GetChpsFileInfo(VOS_VOID);
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetUsimSpdiFileInfo(VOS_VOID);
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSimSpdiFileInfo(VOS_VOID);
TAF_SDC_MM_INFO_STRU* TAF_SDC_GetMmInfo(VOS_VOID);
TAF_SDC_OPER_NAME_TYPE_PRIO_STRU* TAF_SDC_GetOperNamePrio(VOS_VOID);
VOS_VOID TAF_SDC_InitEonsRelatedSimFileInfo(VOS_VOID);

VOS_VOID TAF_SDC_InitEnhancedOperatorNameInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8                        enInitType,
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo
);
VOS_VOID TAF_SDC_ReadEnhancedOperNameServiceCfgNvim( VOS_VOID );

VOS_VOID TAF_SDC_ReadCustomOperNameInfoNvim(VOS_VOID);

TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU *TAF_SDC_GetEnhancedOperatorNameInfo(VOS_VOID);
TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU* TAF_SDC_GetCustomOperNameInfo(VOS_VOID);

VOS_UINT8 TAF_SDC_GetPlmnExactlyCompareFlg(VOS_VOID);
VOS_VOID  TAF_SDC_SetPlmnExactlyCompareFlg(VOS_UINT8  ucPlmnExactlyComparaFlag);
VOS_VOID  TAF_SDC_SetPlmnCompareWildCard(
    VOS_CHAR                            cWildCard
);
VOS_CHAR  TAF_SDC_GetPlmnCompareWildCard(VOS_VOID);
VOS_VOID TAF_SDC_InitPlmnExactlyCompareFlg(VOS_VOID);
VOS_VOID TAF_SDC_InitRefreshAllFileRestartFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetRefreshAllFileRestartFlag(
    VOS_UINT8                           ucRefreshAllFileRestartFlag
);
VOS_UINT8 TAF_SDC_GetRefreshAllFileRestartFlag(VOS_VOID);


TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetCurrNetworkInfo(VOS_VOID);
VOS_VOID TAF_SDC_SetAppRssiValue(VOS_UINT8 ucRssiValue);
VOS_UINT8 TAF_SDC_GetAppRssiValue(VOS_VOID);
VOS_UINT16 TAF_SDC_GetAppCellUlFreq(VOS_VOID);
VOS_UINT16 TAF_SDC_GetAppCellDlFreq(VOS_VOID);
VOS_UINT32 TAF_SDC_GetAppLteArfcn(VOS_VOID);
VOS_VOID TAF_SDC_SetAppLteArfcn(VOS_UINT32 ulLteArfcn);
VOS_VOID TAF_SDC_SetAppServicePlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId);
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetAppServicePlmnId(VOS_VOID);
VOS_VOID TAF_SDC_SetAppSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode);
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetAppSysMode( VOS_VOID );
VOS_VOID TAF_SDC_SetAppSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode);
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetAppSysSubMode( VOS_VOID );
VOS_VOID TAF_SDC_SetAppCampLac(VOS_UINT16 usLac);
VOS_UINT16 TAF_SDC_GetAppCampLac(VOS_VOID);
VOS_VOID TAF_SDC_SetAppCampRac(VOS_UINT8 ucRac);
VOS_UINT8 TAF_SDC_GetAppCampRac(VOS_VOID);
VOS_VOID TAF_SDC_SetAppCampCellId(VOS_UINT32 ulServiceCellId);
VOS_UINT32 TAF_SDC_GetAppCampCellId(VOS_VOID);
VOS_VOID TAF_SDC_SetAppUtranMode(VOS_UINT8 ucServiceUtranMode);
VOS_UINT8 TAF_SDC_GetAppUtranMode(VOS_VOID);
VOS_VOID TAF_SDC_SetAppRoamFlg(VOS_UINT8 ucServiceRoamFlg);
VOS_UINT8 TAF_SDC_GetAppRoamFlg(VOS_VOID);
TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetworkInfo(VOS_VOID);

VOS_VOID  TAF_SDC_SetCurImsSwitchState(
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8       enState
);
TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8  TAF_SDC_GetCurImsSwitchState(VOS_VOID);

TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsServiceStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetAppCsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus);
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsServiceStatus( VOS_VOID );

VOS_VOID TAF_SDC_SetAppPsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus);

VOS_VOID TAF_SDC_SetUsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8 enSimStatus
);

VOS_VOID TAF_SDC_SetCsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
);

VOS_VOID TAF_SDC_SetIccIdInfo(
    VOS_UINT8                   ucLen,
    VOS_UINT8                  *pucIccId
);

TAF_SDC_ICCID_INFO_STRU *TAF_SDC_GetIccIdInfo( VOS_VOID );

TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetUsimType(
    VOS_VOID
);

TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetCsimType(
    VOS_VOID
);

TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetUsimStatus(
    VOS_VOID
);

TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetCsimStatus(
    VOS_VOID
);

VOS_VOID TAF_SDC_SetCsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType
);

VOS_VOID TAF_SDC_SetUsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType
);

VOS_VOID TAF_SDC_InitSimInfo(TAF_SDC_USIM_INFO_STRU *pstSimInfo);

VOS_VOID TAF_SDC_InitCsimInfo(
    TAF_SDC_CSIM_INFO_STRU             *pstCsimInfo
);

TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU *
TAF_SDC_GetImsToCsRedialCauseConfig(VOS_VOID);





VOS_VOID    TAF_SDC_SetXsmsCallExistFlg(
    VOS_UINT8                           ucIsXsmsCallExistFlg
);

VOS_UINT8 TAF_SDC_GetXsmsCallExistFlg(
    VOS_VOID
);

VOS_UINT16 TAF_SDC_Get1xBaseId(VOS_VOID);

VOS_VOID TAF_SDC_SetCdmaCurUeState(
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8    enCasState
);

VOS_UINT8 TAF_SDC_GetCdmaCurUeState(
    VOS_VOID
);

TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU* TAF_SDC_GetNonnormalRegStatusMergeCfg(VOS_VOID);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_GetApp1xSigQualityInfo(VOS_VOID);

TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_GetApp1xSysInfo(VOS_VOID);

VOS_UINT8 TAF_SDC_GetApp1xRoamingFlag(VOS_VOID);

#endif

TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetNetWorkInfoAddr(VOS_VOID);
TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetWorkInfoAddr(VOS_VOID);

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

#endif /* end of TafSdcCtx.h */
