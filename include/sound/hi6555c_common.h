#ifndef __HI6555C_COMMON_H_
#define __HI6555C_COMMON_H_


enum hi6555c_mute {
    UNMUTE_PGA = 0,
    MUTE_PGA = 1,
};

extern void audio_codec_mute_pga(enum hi6555c_mute mute);

#endif

