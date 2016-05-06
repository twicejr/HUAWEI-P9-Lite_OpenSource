#ifndef _LLT_WIFI_H
#define _LLT_WIFI_H


#include <typedefs.h>


#ifdef CONFIG_LLT_TEST

struct UT_TEST_WL
{
	int (*wait_for_cfg80211_resume)(void);
	uint8 (*center_chan_to_edge)(uint );
	uint8 (*channel_low_edge)(uint , uint );
	int (*channel_to_sb)(uint , uint , uint );
	int (*channel_80mhz_to_id)(uint );
	uint8 (*channel_to_ctl_chan)(uint , uint , uint );
    uint8 (*wf_chspec_get80Mhz_ch)(uint8 );
};
extern struct UT_TEST_WL UT_hw_wifi;
extern struct UT_TEST_WL  UT_bcmwifi;

#endif

#endif /*_K3V2_WIFI_POWER_H*/
