/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : WrrcCodecInterface.h
  版 本 号   : V1.00
  作    者   : 贾长青
  生成日期   : 2015年8月10日
  最近修改   :
  功能描述   : WrrcCodecInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月10日
    作    者   : 贾长青
    修改内容   : 创建文件
******************************************************************************/

#ifndef __WRRCCODECINTERFACE_H__
#define __WRRCCODECINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CODEC_WRRC_MSG_TYPE_ENUM
 结构说明  : 原语的ulMsgName
*****************************************************************************/
enum CODEC_WRRC_MSG_TYPE_ENUM
{
    ID_CODEC_WRR_NOISE_STATUS_IND           = 0x0000,   /* _H2ASN_MsgChoice CODEC_WRR_NOISE_STATUS_IND_STRU */
    ID_WRR_CODEC_SILENCE_STATUS_IND         = 0x0001,   /* _H2ASN_MsgChoice WRR_CODEC_SILENCE_STATUS_IND_STRU */
    ID_CODEC_WRR_MSG_TYPE_BUTT              = 0xFFFF
};
typedef VOS_UINT16 CODEC_WRRC_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : CODEC_WRR_NOISE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 流水声状态指示
*****************************************************************************/
enum CODEC_WRR_NOISE_STATUS_ENUM
{
    CODEC_WRR_NO_NOISE    = 0x00,
    CODEC_WRR_NOISE       = 0x01,
    CODEC_WRR_NOISE_BUTT
};

typedef VOS_UINT8 CODEC_WRR_NOISE_STATUS_ENUM_UINT8;

/*******************************************************************************
 结构名    : CODEC_WRR_NOISE_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 CODEC_WRR_NOISE_STATUS_IND 的结构
             该消息用于向协议栈指示流水声发生或消失
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                      usMsgName;                  /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                      usReserve1;                 /* 保留 */
    CODEC_WRR_NOISE_STATUS_ENUM_UINT8               enNoiseStatus;              /* 是否存在流水声 */
    VOS_UINT8                                       aucReserve[3];              /* 保留位 */
}CODEC_WRR_NOISE_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : WRR_CODEC_SILENCE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 静默音枚举值
*****************************************************************************/
enum WRR_CODEC_SILENCE_STATUS_ENUM
{
    CODEC_WRR_SILENCE_START = 0x00,
    CODEC_WRR_SILENCE_END   = 0X01,
    CODEC_WRR_SILENCE_BUTT
};
typedef VOS_UINT8 WRR_CODEC_SILENCE_STATUS_ENUM_UINT8;

/*******************************************************************************
 结构名    : WRR_CODEC_SILENCE_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 WRR_CODEC_SILENCE_STATUS_IND 的结构
             该消息用于WRR指示CODEC启动静默音或关闭静默音
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                      usMsgName;                  /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                      usReserve1;                 /* 保留 */
    WRR_CODEC_SILENCE_STATUS_ENUM_UINT8             enSilenceStatus;            /* 关闭、启动静默音指示 */
    VOS_UINT8                                       aucReserve[3];              /* 保留位 */
}WRR_CODEC_SILENCE_STATUS_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

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

#endif /* end of WrrcCodecInterface.h */



