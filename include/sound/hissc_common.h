#ifndef __HISSC_COMMON_H_
#define __HISSC_COMMON_H_


enum hissc_mute {
    UNMUTE_PGA = 0,
    MUTE_PGA = 1,
};

extern void audio_codec_mute_pga(enum hissc_mute mute);

#endif

