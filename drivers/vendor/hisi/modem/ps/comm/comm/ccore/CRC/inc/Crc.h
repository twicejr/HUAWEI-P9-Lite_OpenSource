/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Crc.h
  版 本 号   : 初稿
  作    者   : h00163499
  生成日期   : 2013年9月10日
  最近修改   :
  功能描述   : Crc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年9月10日
    作    者   : h00163499
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CRC_H__
#define __CRC_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*polynomial:g(x) = x^30 + x^29 + x^21 + x^20 + x^15 + x^13 + x^12 + x^11 + x^8 + x^7 + x^6 + x^2 + x^1 + 1*/
#define     CRC_30_POLYNOMIAL           (0x6030B9C7)

/*polynomial:g(x) = x^16 + x^12 + x^5 + 1*/
#define     CRC_16_POLYNOMIAL            (0x1021)

/*polynomial:g(x) = x^8 + x^7 + x^4 + x^3 + x + 1*/
#define     CRC_8_POLYNOMIAL            (0x9B)


#define     CRC_FCS_BIT_OPR_8           (0xFF)

#define     CRC_30_BIT_SEED             (0x3FFFFFFF)
#define     CRC_16_BIT_SEED             (0xFFFF)
#define     CRC_8_BIT_SEED              (0xFF)
#define     FCS_32_BIT_SEED             (0xFFFFFFFF)
#define     FCS_16_BIT_SEED             (0xFFFF)


#define     GET_16_BIT_HIGH_8_BIT(usCRC16)          ((VOS_UINT16)((usCRC16) >> (16 - 8)))
#define     GET_30_BIT_HIGH_8_BIT(ulCRC30)          ((VOS_UINT32)((ulCRC30) >> (30 - 8)))
#define     UC_LEFT_SHIFT_22_BIT(ucData)            (((VOS_UINT32)(*(ucData))) << 22)
#define     UC_LEFT_SHIFT_8_BIT(ucData)             (((VOS_UINT16)(*(ucData))) << 8)
#define     UL_CRC_LEFT_SHIFT_8_BIT(ulCRC30)        ((ulCRC30) << 8)
#define     US_CRC_LEFT_SHIFT_8_BIT(usCRC16)        ((usCRC16) << 8)
#define     UL_CRC_RIGHT_SHIFT_8_BIT(ulCRC30)       ((ulCRC30) >> 8)
#define     US_CRC_RIGHT_SHIFT_8_BIT(usCRC16)       ((usCRC16 )>> 8)
#define     UL_FCS_RIGHT_SHIFT_8_BIT(ulFCS32)       ((ulFCS32) >> 8)
#define     US_FCS_RIGHT_SHIFT_8_BIT(usFCS16)       ((usFCS16) >> 8)

#define     GET_16_BIT_HIGHEST_BIT(ucData)          ((ucData) & 0x8000)
#define     GET_30_BIT_HIGHEST_BIT(ucData)          ((ucData) & 0x20000000)



/* Seed value for 32 bit CRC */
#define FCS_32_SEED             0x00000000UL
/* Mask for 32 bit CRC polynomial:
x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x^1+1
Note: the x^32 tap can be left off from the polynomial as it is implicit.
 */
#define FCS_32_POLYNOMIAL       0x04c11db7UL
/* Most significant bit mask for CRC.*/
#define FCS_32_MSB_MASK         0x80000000UL

/* The CRC table size is based on how many bits at a time we are going
** to process through the table.  Given that we are processing the data
** 8 bits at a time, this gives us 2^8 (256) entries.
*/
#define FCS_TAB_SIZE    256             /* 2^CRC_TAB_BITS      */






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

extern VOS_UINT32 CRC_CalculateCRC30(const VOS_UINT8 *pucDataBuf, VOS_UINT16 usLengthBits);

extern VOS_UINT16 CRC_CalculateCRC16(const VOS_UINT8 *pucDataBuf, VOS_UINT32 ulLengthBits);

extern VOS_UINT8 CRC_CalculateCRC8(const VOS_UINT8 *pucDataBuf, VOS_UINT16 usLengthBits);

extern VOS_UINT32 FCS_CalculateFCS32(const VOS_UINT8 *pucDataBuf, VOS_UINT16 ulBitLength, VOS_UINT32 ulSeed);

extern VOS_UINT16 FCS_CalculateFCS16(const VOS_UINT8 *pucDataBuf, VOS_UINT16 usLength);

extern VOS_UINT8 FCS_CalculateFCS8(VOS_UINT8 usSN);

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

#endif /* end of Crc.h */

