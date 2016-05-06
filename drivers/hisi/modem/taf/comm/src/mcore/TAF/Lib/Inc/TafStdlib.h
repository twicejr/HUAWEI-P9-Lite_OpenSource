
#ifndef _TAF_STD_LIB_H_
#define _TAF_STD_LIB_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "MnMsgApi.h"
#include  "MnErrorCode.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#define TAF_STD_7BIT_MASK                                    (0x7f)
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
#define TAF_STD_MAX_GSM7BITDEFALPHA_NUM                     (128)
#define TAF_STD_NOSTANDARD_ASCII_CODE                       (0xff)
#define TAF_STD_GSM_7BIT_EXTENSION_FLAG                     (0xfe)
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/* This is the number of days in a leap year set.
   A leap year set includes 1 leap year, and 3 normal years. */
#define TAF_STD_TIME_ZONE_QUAD_YEAR                         (366+(3*365))

/* 5 days (duration between Jan 1 and Jan 6), expressed as seconds. */

#define TAF_STD_TIME_ZONE_OFFSET_S                          (432000UL)

/* This is the year upon which all time values used by the Clock Services
** are based.  NOTE:  The user base day (GPS) is Jan 6 1980, but the internal
** base date is Jan 1 1980 to simplify calculations */

#define TAF_STD_TIME_ZONE_BASE_YEAR                          (1980)

#define TAF_STD_TIME_ZONE_MAX_YEAR                           (2100)

#define TAF_STD_SECONDS_PER_MINUTE                           (60)               /* 60s */

#define TAF_STD_MINUTES_PER_HOUR                             (60)               /* 60m */

#define TAF_STD_HOURS_PER_DAY                                (24)               /* 24HOUR */

#define TAF_STD_NORMAL_MONTH_TAB_COUNT                       (13)

#define TAF_STD_DAYS_ELAPSED_OF_A_LEAP_YEAR_SET_TAB_COUNT    (5)



#define TAF_STD_INVALID_MCC                                 (0xFFFFFFFF)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/



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
 结构名    : TAF_STD_TIME_ZONE_TYPE_STRU
 结构说明  : TimeZone类型的时间结构

 修改记录  :
 1.日    期   : 2014年12月28日s
   作    者   : x00314862
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
  /* Year [1980..2100) */
    VOS_UINT16                          usYear;

  /* Month of year [1..12] */
    VOS_UINT16                          usMonth;

  /* Day of month [1..31] */
    VOS_UINT16                          usDay;

  /* Hour of day [0..23] */
    VOS_UINT16                          usHour;

  /* Minute of hour [0..59] */
    VOS_UINT16                          usMinute;

  /* Second of minute [0..59] */
    VOS_UINT16                          usSecond;


}TAF_STD_TIME_ZONE_TYPE_STRU;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 TAF_STD_Itoa(
    VOS_UINT32                          ulDigit,
    VOS_CHAR                           *pcDigitStr,
    VOS_UINT32                         *pulDigitStrLength
);

VOS_UINT32 TAF_STD_AsciiNum2HexString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                         *pusSrcLen
);

VOS_UINT16 TAF_STD_HexAlpha2AsciiString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    VOS_UINT8                          *pucDst
);

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*将7bit编码方式的字符转换为8bit字符*/
VOS_UINT32  TAF_STD_UnPack7Bit(
    const VOS_UINT8                    *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                          *pucUnPackedChar
);

/*将字符转换为7bit编码方式*/
VOS_UINT32  TAF_STD_Pack7Bit(
    const VOS_UINT8                    *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                          *pucPackedChar,
    VOS_UINT32                         *pulLen
);

/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
VOS_UINT32  TAF_STD_ConvertBcdNumberToAscii(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                           *pcAsciiNumber
);
VOS_UINT32  TAF_STD_ConvertBcdCodeToAscii(
    VOS_UINT8                           ucBcdCode,
    VOS_CHAR                           *pcAsciiCode
);
VOS_UINT32  TAF_STD_ConvertAsciiNumberToBcd(
    const VOS_CHAR                     *pcAsciiNumber,
    VOS_UINT8                          *pucBcdNumber,
    VOS_UINT8                          *pucBcdLen
);
VOS_UINT32 TAF_STD_ConvertAsciiAddrToBcd(
    MN_MSG_ASCII_ADDR_STRU             *pstAsciiAddr,
    MN_MSG_BCD_ADDR_STRU               *pstBcdAddr
);
VOS_UINT32  TAF_STD_ConvertAsciiCodeToBcd(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                          *pucBcdCode
);
VOS_UINT8 TAF_STD_ConvertDeciDigitToBcd(
    VOS_UINT8                           ucDeciDigit,
    VOS_BOOL                            bReverseOrder
);
VOS_UINT32 TAF_STD_ConvertBcdToDeciDigit(
    VOS_UINT8                           ucBcdDigit,
    VOS_BOOL                            bReverseOrder,
    VOS_UINT8                          *pucDigit
);
VOS_UINT32  TAF_STD_ConvertAsciiToDefAlpha(
    const VOS_UINT8                    *pucAsciiChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucDefAlpha
);
VOS_VOID  TAF_STD_ConvertDefAlphaToAscii(
    const VOS_UINT8                    *pucDefAlpha,
    VOS_UINT32                          ulDefAlphaLen,
    VOS_UINT8                          *pucAsciiChar,
    VOS_UINT32                         *pulAsciiCharLen
);

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

VOS_UINT32  TAF_STD_ConvertBcdCodeToDtmf(
    VOS_UINT8                           ucBcdCode,
    VOS_UINT8                          *pucDtmfCode
);

VOS_UINT32  TAF_STD_ConvertBcdNumberToDtmf(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_UINT8                          *pucDtmfNumber
);

extern VOS_UINT32 TAF_STD_ConvertTimeFromSecsToTimeZone
(
    VOS_UINT32                          ulHighSystemTime,
    VOS_UINT32                          ulLowSystemTime,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstUniversalTimeandLocalTimeZone
);

extern VOS_VOID TAF_STD_ConvertSystemTimeToHighLow(
    VOS_UINT8                          *pucSysTimeByte,
    VOS_UINT32                         *pulHighSystemTime,
    VOS_UINT32                         *pulLowSystemTime
);

extern VOS_UINT32 TAF_STD_64Add32
(
    VOS_UINT32                          ulHighAddend,
    VOS_UINT32                          ulLowAddend,
    VOS_UINT32                          ulAddFactor,
    VOS_UINT32                         *pulHighRslt,
    VOS_UINT32                         *pulLowRslt
);

extern VOS_UINT32 TAF_STD_64Sub32
(
    VOS_UINT32                          ulHighMinuend,
    VOS_UINT32                          ulLowMinuend,
    VOS_UINT32                          ulSubFactor,
    VOS_UINT32                         *pulHighRslt,
    VOS_UINT32                         *pulLowRslt
);


VOS_UINT32 TAF_STD_IsValidEmerCategory(
    VOS_UINT8                           ucEmerCategory
);

VOS_UINT16 TAF_STD_TransformBcdMccToDeciDigit(
    VOS_UINT32                          ulBcdMcc
);

VOS_UINT8 TAF_STD_TransformBcdImsi1112ToDeciDigit(
    VOS_UINT16                          usBcdImsi1112
);

VOS_UINT16 TAF_STD_TransformBcdMncToDeciDigit(
    VOS_UINT16                          usBcdMnc
);

VOS_UINT32 TAF_STD_TransformDeciDigitToBcdMcc(
    VOS_UINT32                          ulDeciDigitMcc
);
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

#endif /* end of TafSpmCtx.h */


