/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Version.h
  版 本 号   : 初稿
  作    者   : 戴明扬
  生成日期   : 2010年2月12日
  最近修改   : 初稿
  功能描述   : 此文件中，只定义产品ID、硬件版本号、软件版本号，供其他组件引用
  函数列表   :
  修改历史   :
  1.日    期   : 2010年2月12日
    作    者   : 戴明扬
    修改内容   : 创建文件

******************************************************************************/

#ifndef __VERSION_H__
#define __VERSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#define PRODUCT_ID                      "BALONGSPC2H"
#define HARD_VERSION                    "BALONGSPC2H"
#define PRODUCT_VERSION                 "V3R1C1B020"


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

#endif /* end of Version.h */
