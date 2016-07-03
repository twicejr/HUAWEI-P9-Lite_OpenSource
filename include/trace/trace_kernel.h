

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