/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SysNvId.h
  版 本 号   :
  作    者   : 胡骏 59254
  生成日期   : 2009年5月14日
  最近修改   :
  功能描述   : 定义了系统NV项ID枚举定义
  函数列表   :
  修改历史   :
  1.日    期   : 2009年5月14日
    作    者   : 胡骏 59254
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NVIDDEF_H__
#define __NVIDDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/****************************************************************************
  1 宏定义
*****************************************************************************/
/* 模块NVID的范围定义*/
#define     GU_SYS_NV_ID_MIN            0
#define     GU_SYS_NV_ID_MAX            4095

#define     GU_RF_BASE_NV_ID_MIN        4097
#define     GU_RF_BASE_NV_ID_MAX        8192

#define     GU_PS_NV_ID_MIN             8193
#define     GU_PS_NV_ID_MAX             12287

#define     GU_CODEC_NV_ID_MIN          12288
#define     GU_CODEC_NV_ID_MAX          12543

#define     GU_RF_EXTEND_NV_ID_MIN      20480
#define     GU_RF_EXTEND_NV_ID_MAX      20991

#define     GU_CUSTOM_BASE_NV_ID_MIN    32768


#define     GU_CUSTOM_EXTEND_NV_ID_MIN  50000
#define     GU_CUSTOM_EXTEND_NV_ID_MAX  50500

#define     LTE_MODEM_NV_ID_MIN         53248
#define     LTE_MODEM_NV_ID_MAX         58624

#define     LTE_CUSTOM_NV_ID_MIN        58625
#define     LTE_CUSTOM_NV_ID_MAX        62976



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __NVIDDEF_H__ */
