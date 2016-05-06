/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : trace_kernel.h
  版 本 号   : 初稿
  作    者   : 陈易超
  生成日期   : 2013年4月28日
  最近修改   :
  功能描述   : APIs for kernel function calling. To add log to trace_marker
               which will be dumped by systrace.
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月28日
    作    者   : 陈易超
    修改内容   : 创建文件

******************************************************************************/

#ifndef _TRACE_KERNEL_H
#define _TRACE_KERNEL_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
enum  {
    TP = 0,
    REC,
    CAM,
    STF,
    NUP,
    VDEC,
    VENC,
    VPP,
    APLY,
    AREC,
    APCM,
    ADSP,
    AASP,
    GPU,
    SF,
    MHL,
    MODULE_ID_MAX,
};
/*****************************************************************************
  3 函数实现
*****************************************************************************/
void trace_dot(unsigned int id, const char* point, int value);
void trace_begin(int tag, const char* name);
void trace_end(int tag);
void trace_counter(int tag, const char* name, int value);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif