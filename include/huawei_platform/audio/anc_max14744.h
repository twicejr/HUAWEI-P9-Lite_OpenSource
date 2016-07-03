/*
 * anc_max14744.h -- anc headset driver
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef ANC_MAX14744
#define ANC_MAX14744

#include "huawei_platform/audio/anc_hs_interface.h"

#define ANC_HS_ENABLE_CHARGE 0
#define ANC_HS_DISABLE_CHARGE 1

#define ANC_MAX14744_R000_DEVICE_ID                                       0x00
#define ANC_MAX14744_R001_ADC_CONVERSION                            0x01
#define ANC_MAX14744_R002_ADC_STATUS                                    0x02
#define ANC_MAX14744_R003_STATUS                                            0x03
#define ANC_MAX14744_R004_MSIC1                                               0x04
#define ANC_MAX14744_R005_MSIC2                                               0x05
#define ANC_MAX14744_R006_INTERRUPT                                       0x06
#define ANC_MAX14744_R007_MASK                                                0x07
#define ANC_MAX14744_R008_PINS_CONTROL1                               0x08
#define ANC_MAX14744_R009_PINS_CONTROL2                               0x09
#define ANC_MAX14744_R00A_ADC_CONTROL                                  0x0a
#define ANC_MAX14744_R00B_ACC_CONTROL1                                0x0b
#define ANC_MAX14744_R00C_ACC_CONTROL2                                0x0c
#define ANC_MAX14744_R00F_COMMAND                                         0x0f
#define ANC_MAX14744_R010_TX_RX                                               0x10
#define ANC_MAX14744_R011_INT                                                   0x11
#define ANC_MAX14744_R012_INT_ENA                                           0x12
#define ANC_MAX14744_R013_CK_DIV                                             0x13
#define ANC_MAX14744_R014_CONTROL                                          0x14

#define ANC_MAX14744_JACK_DETECT_BIT                                     0x10
#define ANC_MAX14744_PLUG_IRQ_BIT                                           0x10
#define ANC_MAX14744_BUTTON_PRESS_IRQ_BIT                           0x01
#define ANC_MAX14744_BUTTON_PRESS_IRQ_MASK_BIT                0x01
#define ANC_MAX14744_BUTTON_PRESS_BIT                                   0x02
#define ANC_MAX14744_EOC_IRQ_BIT                                    0x20

#define ANC_MAX14744_EOC_BIT                                             0x01
#define ANC_MAX14744_IDETLVL_BIT                                         0x40

#define ANC_MAX14744_MODE1_MASK                                             0x0C
#define ANC_MAX14744_MODE0_MASK                                             0x03
#define ANC_MAX14744_BYPASS_MASK                                            0x02
#define ANC_MAX14744_MANUL_MIC_SW_MASK                              0x40
#define ANC_MAX14744_FORCE_MIC_SW_MASK                               0x10
#define ANC_MAX14744_MANUL_CNTL_MASK                              0x80
#define ANC_MAX14744_FORCE_CNTL_MASK                               0x20

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

#define  MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC  262148

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

#ifdef CONFIG_ANC_MAX14744
int anc_max14744_dev_register(struct anc_hs_dev *dev, void * codec_data);
bool anc_max14744_check_headset_pluged_in(void);
void anc_max14744_start_charge(void);
void anc_max14744_charge_detect(int saradc_value, int headset_type);
void anc_max14744_stop_charge(void);
void anc_max14744_force_charge(int disable);
bool check_anc_max14744_support(void);
bool anc_max14744_plug_enable(void);
void anc_max14744_invert_headset_control(int connect);
void anc_max14744_refresh_headset_type(int headset_type);
#else
int anc_max14744_dev_register(struct anc_hs_dev *dev, void * codec_data)
{
    return 0;
}
bool anc_max14744_check_headset_pluged_in(void)
{
    return false;
}
static inline void anc_max14744_start_charge(void)
{
    return;
}
static inline void anc_max14744_charge_detect(int saradc_value, int headset_type)
{
    return;
}
static inline void anc_max14744_stop_charge(void)
{
    return;
}
static inline void anc_max14744_force_charge(int disable)
{
    return;
}
static inline bool check_anc_max14744_support(void)
{
    return false;
}
static inline bool anc_max14744_plug_enable(void)
{
    return false;
}
void anc_max14744_invert_headset_control(int connect)
{
    return;
}
void anc_max14744_refresh_headset_type(int headset_type)
{
    return;
}
#endif

#endif //ANC_HS_H
