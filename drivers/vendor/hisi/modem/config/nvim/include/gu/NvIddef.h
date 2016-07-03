

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
