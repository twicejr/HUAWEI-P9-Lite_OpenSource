/*
 * audio rdr adpter.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __RDR_HISI_AUDIO_ADAPTER_H__
#define __RDR_HISI_AUDIO_ADAPTER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/hisi/rdr_pub.h>


#define RDR_FNAME_LEN					128
/* rdr为HIFI分配的ID范围为0x84000000~0x84ffffff，定义在rdr_pub.h中 */
#define HIFI_MODID_START        HISI_BB_MOD_HIFI_START

#define SOC_AUDIO_MODID_START   HIFI_MODID_START
#define SOC_AUDIO_MODID_END     0x8400000f

#define CODEC_AUDIO_MODID_START 0x84000010
#define CODEC_AUDIO_MODID_END   0x8400001F

#define HIFI_MODID_END          HISI_BB_MOD_HIFI_END

#define RDR_MODEM_CP_MOD_ID             0x82000001
#define RDR_MODEM_CP_RESET_3RD_MOD_ID   0x82000008

int rdr_audio_write_file(char *name, char *data, u32 size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

