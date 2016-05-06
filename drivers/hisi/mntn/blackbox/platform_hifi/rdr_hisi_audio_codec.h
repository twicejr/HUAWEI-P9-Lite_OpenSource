/*
 * audio codec rdr.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __RDR_HISI_CODEC_H__
#define __RDR_HISI_CODEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

int  rdr_audio_codec_init(void);
void rdr_audio_codec_exit(void);

void rdr_audio_codec_dump(u32 modid, char *pathname, pfn_cb_dump_done pfb);
void rdr_audio_codec_reset(u32 modid, u32 etype, u64 coreid);
void rdr_codec_hifi_watchdog_process(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

