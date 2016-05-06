/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasAirMsgHdr.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2008年2月19日
  最近修改   : 2008年2月19日
  功能描述   : 定义NAS空口消息的公共头部
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月19日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NASAIRMSGHDR_H__
#define __NASAIRMSGHDR_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/* PD定义 (24.007 11.2.3.1.1) */
#define  NAS_PD_GCC                     0x00
#define  NAS_PD_BCC                     0x01
#define  NAS_PD_CC                      0x03
#define  NAS_PD_GTTP                    0x04
#define  NAS_PD_MM                      0x05
#define  NAS_PD_RR                      0x06
#define  NAS_PD_GMM                     0x08
#define  NAS_PD_SMS                     0x09
#define  NAS_PD_SM                      0x0A
#define  NAS_PD_SS                      0x0B
#define  NAS_PD_LS                      0x0C

/* TI flag 定义 (24.007 11.2.3.1.3) */
#define  NAS_TI_FLAG_FROM_ORIGINATOR    1
#define  NAS_TI_FLAG_TO_ORIGINATOR      0

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*
   NAS空口消息头，
   所有要使用统一编解码方式进行编解码的NAS消息结构都必须包含该头部
*/
typedef struct
{
   VOS_UINT8                            bit4PD              :4;
   VOS_UINT8                            bit4TI              :4;
   VOS_UINT8                            ucMsgType;
}NAS_AIR_MSG_HDR_STRU;


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

#endif /* __NASAIRMSGHDR_H__ */

