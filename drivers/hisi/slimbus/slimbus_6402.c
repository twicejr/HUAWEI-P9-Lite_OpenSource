/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/delay.h>

#include "csmi.h"
#include "slimbus_drv.h"
#include "slimbus.h"
#include <hisi/hilog.h>
#include <dsm/dsm_pub.h>

/*lint -e750*/
#define LOG_TAG "Slimbus_6402"

extern slimbus_channel_property_t audio_playback[SLIMBUS_AUDIO_PLAYBACK_CHANNELS];
extern slimbus_channel_property_t audio_capture[SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS];
extern slimbus_channel_property_t voice_down[SLIMBUS_VOICE_DOWN_CHANNELS];
extern slimbus_channel_property_t voice_up[SLIMBUS_VOICE_UP_CHANNELS];
extern slimbus_channel_property_t img_download[SLIMBUS_IMAGE_DOWNLOAD_CHANNELS];
extern slimbus_channel_property_t ec_ref[SLIMBUS_ECREF_CHANNELS];
extern slimbus_channel_property_t sound_trigger[SLIMBUS_SOUND_TRIGGER_CHANNELS];


/* slimbus soc side port definition */
typedef enum
{
	AUDIO_PLAY_SOC_LEFT_PORT			= 0,
	AUDIO_PLAY_SOC_RIGHT_PORT			= 1,
	AUDIO_CAPTURE_SOC_LEFT_PORT 			= 2,
	AUDIO_CAPTURE_SOC_RIGHT_PORT			= 3,
	BT_CAPTURE_SOC_LEFT_PORT			= 6,
	BT_CAPTURE_SOC_RIGHT_PORT			= 7,
	VOICE_DOWN_SOC_LEFT_PORT			= 8,
	VOICE_DOWN_SOC_RIGHT_PORT			= 9,
	VOICE_UP_SOC_MIC1_PORT				= 10,
	VOICE_UP_SOC_MIC2_PORT				= 11,

	IMAGE_DOWNLOAD_SOC_PORT 			= 12,
	VOICE_SOC_ECREF_PORT				= 14,
	AUDIO_SOC_ECREF_PORT				= 15,
} slimbus_soc_port_t;

/* slimbus device side port definition */
typedef enum
{
	AUDIO_PLAY_6402_LEFT_PORT			= 0,
	AUDIO_PLAY_6402_RIGHT_PORT			= 1,
	AUDIO_CAPTURE_6402_LEFT_PORT			= 2,
	AUDIO_CAPTURE_6402_RIGHT_PORT			= 3,
	BT_CAPTURE_6402_LEFT_PORT			= 6,
	BT_CAPTURE_6402_RIGHT_PORT			= 7,
	VOICE_DOWN_6402_LEFT_PORT			= 8,
	VOICE_DOWN_6402_RIGHT_PORT			= 9,
	VOICE_UP_6402_MIC1_PORT 			= 10,
	VOICE_UP_6402_MIC2_PORT 			= 11,

	IMAGE_DOWNLOAD_6402_PORT			= 12,
	VOICE_6402_ECREF_PORT				= 14,
	AUDIO_6402_ECREF_PORT				= 15,
} slimbus_6402_port_t;

/* channel numbers */
static uint8_t chnum_table[SLIMBUS_TRACK_MAX] = {
			SLIMBUS_AUDIO_PLAYBACK_CHANNELS,
			SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS,
			SLIMBUS_VOICE_DOWN_CHANNELS,
			SLIMBUS_VOICE_UP_CHANNELS,
			SLIMBUS_IMAGE_DOWNLOAD_CHANNELS,
			SLIMBUS_ECREF_CHANNELS,
			SLIMBUS_SOUND_TRIGGER_CHANNELS,
			SLIMBUS_DEBUG_CHANNELS,
			/* super play */
			/* super cap */
};

/* segment length */
static uint16_t sl_table[SLIMBUS_RF_MAX][SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] = {
			/* 24.576M */
			{
				{6, 6},						/* audio playback */
				{6, 6, 6, 6},					/* audio capture */
				{6, 6},						/* voice down */
				{6, 6, 6, 6},					/* voice up */
				{5},						/* image download */
				{4, 4},						/* EC_REF */
				{4},						/* sound trigger */
				{6, 6},
			},
			/* 6.144M */
			{
				{6, 6},						/* audio playback */
				{4, 4},						/* audio capture */
				{4, 4},						/* voice down */
				{4, 4, 4, 4},					/* voice up */
				{5},						/* image download */
				{0, 0},						/* EC_REF */
			},
};

/* presence rate */
static slimbus_presence_rate_t pr_table[SLIMBUS_RF_MAX][SLIMBUS_TRACK_MAX] = {
			{
				SLIMBUS_PR_48K, SLIMBUS_PR_48K,
				SLIMBUS_PR_8K, SLIMBUS_PR_8K,
				SLIMBUS_PR_768K, SLIMBUS_PR_48K, SLIMBUS_PR_192K
			},
			{
				SLIMBUS_PR_48K, SLIMBUS_PR_48K,
				SLIMBUS_PR_8K, SLIMBUS_PR_8K,
				SLIMBUS_PR_192K, SLIMBUS_PR_48K
			},
};


/* channel index */
static uint32_t cn_table[SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] = {
			{AUDIO_PLAY_CHANNEL_LEFT, AUDIO_PLAY_CHANNEL_RIGHT},
			{AUDIO_CAPTURE_CHANNEL_LEFT, AUDIO_CAPTURE_CHANNEL_RIGHT, VOICE_UP_CHANNEL_MIC1, VOICE_UP_CHANNEL_MIC2},
			{VOICE_DOWN_CHANNEL_LEFT, VOICE_DOWN_CHANNEL_RIGHT},
			{VOICE_UP_CHANNEL_MIC1, VOICE_UP_CHANNEL_MIC2, AUDIO_CAPTURE_CHANNEL_LEFT, AUDIO_CAPTURE_CHANNEL_RIGHT},
			{IMAGE_DOWNLOAD},
			{VOICE_ECREF, AUDIO_ECREF},
			{SOUND_TRIGGER_CHANNEL_LEFT, SOUND_TRIGGER_CHANNEL_RIGHT},
};

/* source port number */
static uint8_t source_pn_table[SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] = {
			{AUDIO_PLAY_SOC_LEFT_PORT, AUDIO_PLAY_SOC_RIGHT_PORT},
			{AUDIO_CAPTURE_6402_LEFT_PORT, AUDIO_CAPTURE_6402_RIGHT_PORT, VOICE_UP_6402_MIC1_PORT, VOICE_UP_6402_MIC2_PORT},
			{VOICE_DOWN_SOC_LEFT_PORT, VOICE_DOWN_SOC_RIGHT_PORT},
			{VOICE_UP_6402_MIC1_PORT, VOICE_UP_6402_MIC2_PORT, AUDIO_CAPTURE_6402_LEFT_PORT, AUDIO_CAPTURE_6402_RIGHT_PORT},
			{IMAGE_DOWNLOAD_SOC_PORT},
			{VOICE_6402_ECREF_PORT, AUDIO_6402_ECREF_PORT},
			{BT_CAPTURE_6402_LEFT_PORT, BT_CAPTURE_6402_RIGHT_PORT},
};

/* sink port number */
static uint8_t sink_pn_table[SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] = {
			{AUDIO_PLAY_6402_LEFT_PORT, AUDIO_PLAY_6402_RIGHT_PORT},
			{AUDIO_CAPTURE_SOC_LEFT_PORT, AUDIO_CAPTURE_SOC_RIGHT_PORT, VOICE_UP_SOC_MIC1_PORT, VOICE_UP_SOC_MIC2_PORT},
			{VOICE_DOWN_6402_LEFT_PORT, VOICE_DOWN_6402_RIGHT_PORT},
			{VOICE_UP_SOC_MIC1_PORT, VOICE_UP_SOC_MIC2_PORT, AUDIO_CAPTURE_SOC_LEFT_PORT, AUDIO_CAPTURE_SOC_RIGHT_PORT},
			{IMAGE_DOWNLOAD_6402_PORT},
			{VOICE_SOC_ECREF_PORT, AUDIO_SOC_ECREF_PORT},
			{BT_CAPTURE_SOC_LEFT_PORT, BT_CAPTURE_SOC_RIGHT_PORT},
};

/* segment distribution */
static uint16_t sd_table[SLIMBUS_RF_MAX][SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] = {
			/* 24.576M */
			{
				{0xC94, 0xCB4}, 				/* audio playback */
				{0xCD4, 0xCF4, 0xC9A, 0xCBA},			/* audio capture */
				{0x15A, 0x17A}, 				/* voice down 8k */
				{0x1DA, 0x1FA, 0x55A, 0x57A},			/* voice up 8k */
				{0xC0B},					/* image download */
				{0xC90, 0xCB0}, 				/* EC_REF */
				{0xC28/*, 0xC2C*/}, 				/* sound trigger */
			},
			/* 6.144M */
			{
				{0xc24, 0xc2a}, 				/* audio playback */
				{0xc30, 0xc34}, 				/* audio capture */
				{0x58, 0x5c},					/* voice down 8k */
				{0x78, 0x7c, 0x458, 0x45C}, 			/* voice up 8k */
				{0xC0B},					/* image download */
				{0},						/* voice EC_REF */
			},
};

static uint16_t sd_voice_down_16k[SLIMBUS_RF_MAX][SLIMBUS_CHANNELS_MAX] = {
			{0xDA,	0xFA},						/* 24.576M voice down 16k*/
			{0x38,	0x3C},						/* 6.144M voice down 16k*/
};

static uint16_t sd_voice_up_16k[SLIMBUS_RF_MAX][SLIMBUS_CHANNELS_MAX] = {
			{0x4DA, 0x4FA, 0x8DA, 0x8FA},				/* 24.576M voice up 16k*/
			{0x438, 0x43c, 0x838, 0x83c},				/* 6.144M voice up 16k*/
};

static uint16_t sd_soundtrigger_48k[SLIMBUS_CHANNELS_MAX] = {0xC88/*, 0xC8C*/};

static uint16_t sd_soundtrigger_16k[SLIMBUS_CHANNELS_MAX] = {0x88};




void slimbus_hi6402_param_init(slimbus_device_info_t *dev)
{
	slimbus_channel_property_t	*pchprop = NULL;
	slimbus_transport_protocol_t	tp = SLIMBUS_TP_ISOCHRONOUS;
	slimbus_rf_type_t	rf = dev->rf;
	int 	track_type = 0;
	uint8_t source_la	= SOC_LA_GENERIC_DEVICE;
	uint8_t sink_la		= HI6402_LA_GENERIC_DEVICE;
	int 	ch		= 0;
	int 	i		= 0;


	for (track_type = SLIMBUS_TRACK_AUDIO_PLAY; track_type < SLIMBUS_TRACK_MAX; track_type++) {
		source_la = SOC_LA_GENERIC_DEVICE;
		sink_la   = HI6402_LA_GENERIC_DEVICE;
		tp	= SLIMBUS_TP_ISOCHRONOUS;

		switch (track_type) {
		case SLIMBUS_TRACK_AUDIO_PLAY:
			pchprop = audio_playback;
			break;
		case SLIMBUS_TRACK_AUDIO_CAPTURE:
			pchprop = audio_capture;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		case SLIMBUS_TRACK_VOICE_DOWN:
			pchprop = voice_down;
			break;
		case SLIMBUS_TRACK_VOICE_UP:
			pchprop = voice_up;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		case SLIMBUS_TRACK_IMAGE_LOAD:
			pchprop = img_download;
			tp		= SLIMBUS_TP_PUSHED;
			break;
		case SLIMBUS_TRACK_ECREF:
			pchprop = ec_ref;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		case SLIMBUS_TRACK_SOUND_TRIGGER:
			pchprop = sound_trigger;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		default:
			pr_err("[%s:%d] track type is invalid: %d\n", __FUNCTION__, __LINE__, track_type);
			return;
		}

		for (ch = 0; ch < chnum_table[track_type]; ch++) {
			memset(pchprop, 0, sizeof(slimbus_channel_property_t));

			pchprop->cn 	   = cn_table[track_type][ch];
			pchprop->source.la = source_la;
			pchprop->source.pn = source_pn_table[track_type][ch];
			pchprop->sink_num  = 1;
			for (i = 0; i < pchprop->sink_num; i++) {
				pchprop->sinks[i].la  = sink_la;
				pchprop->sinks[i].pn  = sink_pn_table[track_type][ch];
			}
			pchprop->tp 	   = tp;
			pchprop->sd 	   = sd_table[rf][track_type][ch];
			pchprop->sl 	   = sl_table[rf][track_type][ch];
			pchprop->fl 	   = 0;
			pchprop->pr 	   = pr_table[rf][track_type];
			pchprop->af 	   = SLIMBUS_AF_NOT_APPLICABLE;
			pchprop->dt 	   = SLIMBUS_DF_NOT_INDICATED;
			pchprop->cl 	   = 0;
			if (SLIMBUS_TP_PUSHED == tp) {
				pchprop->dl    = pchprop->sl - 1;
			} else {
				pchprop->dl    = pchprop->sl;
			}
			pchprop->active    = 0;

			pchprop++;
		}
	}

	return;
}
EXPORT_SYMBOL(slimbus_hi6402_param_init);


int slimbus_hi6402_param_set(
				slimbus_device_info_t *dev,
				slimbus_track_type_t   track_type,
				slimbus_track_param_t *params)
{
	slimbus_channel_property_t	*pchprop = NULL;
	slimbus_track_type_t		track;
	slimbus_rf_type_t		rf	  = dev->rf;
	int 	ch = 0;

	pr_info("[%s:%d] track type:%d, rate:%d, chnum:%d\n", __FUNCTION__, __LINE__, track_type, params->rate, params->channels);

	if ((SLIMBUS_TRACK_VOICE_DOWN == track_type) || (SLIMBUS_TRACK_VOICE_UP == track_type)) {
		track = SLIMBUS_TRACK_VOICE_DOWN;
		pchprop = &voice_down[0];

		for (ch=0; ch < chnum_table[track]; ch++) {
			if (params->rate == 8000) {
				pchprop->sd 	   = sd_table[rf][track][ch];
				pchprop->pr 	   = pr_table[rf][track];
			} else if (params->rate == 16000) {
				pchprop->sd 	   = sd_voice_down_16k[rf][ch];
				pchprop->pr 	   = SLIMBUS_PR_16K;
			} else {
				pr_err("[%s:%d] sample rate is invalid: %d\n", __FUNCTION__, __LINE__, params->rate);
			}

			pchprop++;
		}

		track = SLIMBUS_TRACK_VOICE_UP;
		pchprop = &voice_up[0];
		if (SLIMBUS_TRACK_VOICE_UP == track_type) {
			dev->voice_up_chnum = params->channels;
		}

		for (ch=0; ch < chnum_table[track]; ch++) {
			if (params->rate == 8000) {
				pchprop->sd 	   = sd_table[rf][track][ch];
				pchprop->pr 	   = pr_table[rf][track];
			} else if (params->rate == 16000) {
				pchprop->sd 	   = sd_voice_up_16k[rf][ch];
				pchprop->pr 	   = SLIMBUS_PR_16K;
			} else {
				pr_err("[%s:%d] sample rate is invalid: %d\n", __FUNCTION__, __LINE__, params->rate);
			}

			pchprop++;
		}
	} else if (SLIMBUS_TRACK_AUDIO_CAPTURE == track_type) {
		dev->audio_up_chnum = params->channels;
	} else if (SLIMBUS_TRACK_SOUND_TRIGGER == track_type) {
		track = SLIMBUS_TRACK_SOUND_TRIGGER;
		pchprop = &sound_trigger[0];
		for (ch=0; ch < chnum_table[track]; ch++) {
			if (params->rate == 192000) {
				pchprop->sd 	   = sd_table[rf][track][ch];
				pchprop->pr 	   = pr_table[rf][track];
			} else if (params->rate == 48000) {
				pchprop->sd 	   = sd_soundtrigger_48k[ch];
				pchprop->pr 	   = SLIMBUS_PR_48K;
			} else if (params->rate == 16000) {
				pchprop->sd 	   = sd_soundtrigger_16k[ch];
				pchprop->pr 	   = SLIMBUS_PR_16K;
			}
			pchprop++;
		}
	} else {
		pr_err("[%s:%d] track type is invalid: %d\n", __FUNCTION__, __LINE__, track_type);
	}

	return 0;
}



/*
 * create hi6402 slimbus device
 * @device, pointer to created instance
 *
 * return 0, if success
 */
int create_hi6402_slimbus_device(slimbus_device_info_t **device)
{
	struct slimbus_device_info *dev_info = NULL;

	dev_info = kzalloc(sizeof(struct slimbus_device_info), GFP_KERNEL);
	if (!dev_info) {
		pr_info("[%s:%d] malloc slimbus failed!\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	dev_info->generic_la		= HI6402_LA_GENERIC_DEVICE;
	dev_info->voice_up_chnum	= SLIMBUS_VOICE_UP_2CH;;
	dev_info->audio_up_chnum	= SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS;//default is 4mic
	dev_info->page_sel_addr		= 1;

	mutex_init(&dev_info->mutex);

	*device = dev_info;

	return 0;
}
EXPORT_SYMBOL(create_hi6402_slimbus_device);

int release_hi6402_slimbus_device(slimbus_device_info_t *device)
{
	if (device != NULL) {
		mutex_destroy(&(device->mutex));
		kfree(device);
		device = NULL;
	}
	return 0;
}
EXPORT_SYMBOL(release_hi6402_slimbus_device);

