/*
 * anc_hs.h -- anc headset driver
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef ANC_HS_H
#define ANC_HS_H

#include "huawei_platform/audio/anc_hs_interface.h"

#define ANC_HS_ENABLE_CHARGE 0
#define ANC_HS_DISABLE_CHARGE 1

#define ANC_HS_ENABLE_5VOLTATE 1
#define ANC_HS_DISABLE_5VOLTATE 0

/*IO controls for user*/
#define IOCTL_ANC_HS_CHARGE_ENABLE_CMD          _IO('A', 0x01)
#define IOCTL_ANC_HS_CHARGE_DISABLE_CMD         _IO('A', 0x02)
#define IOCTL_ANC_HS_GET_CHARGE_STATUS_CMD               _IOR('A', 0xFF, __u32)
#define IOCTL_ANC_HS_GET_HEADSET_CMD            _IOR('A', 0xFE, __u32)

struct MLIBSetParaInfo {
    short   msgID;
    short   reserve;
    int     uwPathID;
    int     uwModuleID;
    int     uwSize;
    char    aucData[];
};
#define MLIB_PARA_LENGTH_MAX 200

#define ERROR_RET 1
#define OK_RET  0

enum AUDIO_MSG_ENUM {
    ID_AP_AUDIO_ENHANCE_SET_DEVICE_IND  = 0xDD91,
    ID_AP_AUDIO_MLIB_SET_PARA_IND       = 0xDD92,
};
enum MLIB_PATH_ENUM {
    MLIB_PATH_CS_VOICE_CALL_MICIN = 0,
    MLIB_PATH_CS_VOICE_CALL_SPKOUT,
    MLIB_PATH_VOIP_CALL_MICIN,
    MLIB_PATH_VOIP_CALL_SPKOUT,
    MLIB_PATH_AUDIO_PLAY,
    MLIB_PATH_AUDIO_RECORD,
    MLIB_PATH_SIRI_MICIN,
    MLIB_PATH_SIRI_SPKOUT,
    MLIB_PATH_BUTT,
};
enum MLIB_MODULE_ENUM {
    MLIB_MODULE_DEFAULT = 0,
    MLIB_MODULE_BALONG_PP,
    MLIB_MODULE_FORTE_VOICE,
    MLIB_MODULE_MBDRC,
    MLIB_MODULE_KARAOKE,
    MLIB_MODULE_MCPS_TEST,
    MLIB_MODULE_WNR_VOICE,
    MLIB_MODULE_3A_VOICE,
    MLIB_MODULE_BUTT,
};
enum MLIB_VOICE_PARA_ENUM
{
    MLIB_PARA_INVALID = 0,
    MLIB_BWE_PARA_ENABLE,
    MLIB_LVM_PARA_ENABLE,
    MLIB_BT_PARA_NREC,
    MLIB_RESET_PARA_ENABLE,
    MLIB_PRINT_MCPS_ENABLE,
    MLIB_VOICE_ALGO_BYPASS,
    MLIB_WNR_PARA_ENABLE,
    MLIB_DHF_PARA_ENABLE,
    MLIB_ANC_HS_PARA_ENABLE,
};
struct MlibParameterVoice
{
    int32_t key;
    int32_t  value;
};
#ifdef CONFIG_ANC_HS
int anc_hs_dev_register(struct anc_hs_dev *dev, void *codec_data);
void anc_hs_start_charge(void);
void anc_hs_charge_detect(int saradc_value, int headset_type);
void anc_hs_stop_charge(void);
void anc_hs_force_charge(int disable);
bool check_anc_hs_support(void);
void anc_hs_5v_control(int enable);
#else
static inline int anc_hs_dev_register(struct anc_hs_dev *dev, void *codec_data)
{
    return 0;
}
static inline void anc_hs_start_charge(void)
{
    return;
}
static inline void anc_hs_charge_detect(int saradc_value, int headset_type)
{
    return;
}
static inline void anc_hs_stop_charge(void)
{
    return;
}
static inline void anc_hs_force_charge(int disable)
{
    return;
}
static inline bool check_anc_hs_support(void)
{
    return false;
}
static inline void anc_hs_5v_control(int enable)
{
    return;
}
#endif

#endif //ANC_HS_H
