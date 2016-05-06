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

#ifndef __SLIMBUS_TYPES_H__
#define __SLIMBUS_TYPES_H__

#include <linux/types.h>

/* max channel number supported */
#define SLIMBUS_MAX_CHANNELS	(16)

#define SLIMBUS_AUDIO_PLAYBACK_CHANNELS                 (2)
#define SLIMBUS_AUDIO_CAPTURE_CHANNELS                  (2)
#define SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS        (4)
#define SLIMBUS_VOICE_DOWN_CHANNELS                     (2)
#define SLIMBUS_VOICE_UP_CHANNELS                       (4)
#define SLIMBUS_VOICE_UP_2CH                            (2)
#define SLIMBUS_IMAGE_DOWNLOAD_CHANNELS                 (1)
#define SLIMBUS_ECREF_CHANNELS                          (2)
#define SLIMBUS_SOUND_TRIGGER_CHANNELS                  (1)
#define SLIMBUS_VOICE_UP_SOUNDTRIGGER                   (1)
#define SLIMBUS_DEBUG_CHANNELS                          (2)

#define SLIMBUS_CHANNELS_MAX                            (4)


/* user value / information elements slice sizes */
typedef enum
{
	SLIMBUS_SS_1_BYTE					= 0,				/* slice size is 1 byte. */
	SLIMBUS_SS_2_BYTES					= 1,				/* slice size is 2 bytes. */
	SLIMBUS_SS_3_BYTES					= 2,				/* slice size is 3 bytes. */
	SLIMBUS_SS_4_BYTES					= 3,				/* slice size is 4 bytes. */
	SLIMBUS_SS_6_BYTES					= 4,				/* slice size is 6 bytes. */
	SLIMBUS_SS_8_BYTES					= 5,				/* slice size is 8 bytes. */
	SLIMBUS_SS_12_BYTES 				= 6,				/* slice size is 12 bytes. */
	SLIMBUS_SS_16_BYTES 				= 7,				/* slice size is 16 bytes. */
	SLIMBUS_SS_SLICE_BUT				= 8,

} slimbus_slice_size_t;

/* transport protocols */
typedef enum
{
	SLIMBUS_TP_ISOCHRONOUS				= 0,				/* isochronous protocol (multicast). */
	SLIMBUS_TP_PUSHED					= 1,				/* pushed protocol (multicast). */
	SLIMBUS_TP_PULLED					= 2,				/* pulled protocol (unicast). */
	SLIMBUS_TP_LOCKED					= 3,				/* locked protocol (multicast). */
	SLIMBUS_TP_ASYNC_SIMPLEX			= 4,				/* asynchronous protocol - simplex (unicast). */
	SLIMBUS_TP_ASYNC_HALF_DUPLEX		= 5,				/* asynchronous protocol - half-duplex (unicast). */
	SLIMBUS_TP_EXT_ASYNC_SIMPLEX		= 6,				/* extended asynchronous protocol - simplex (unicast). */
	SLIMBUS_TP_EXT_ASYNC_HALF_DUPLEX	= 7,				/* extended asynchronous protocol - half-duplex (unicast). */
	SLIMBUS_TP_USER_DEFINED_1			= 14,				/* user defined 1. */
	SLIMBUS_TP_USER_DEFINED_2			= 15,				/* user defined 2. */

} slimbus_transport_protocol_t;

/* presence rates */
typedef enum
{
	SLIMBUS_PR_12K						= 1,
	SLIMBUS_PR_24K						= 2,
	SLIMBUS_PR_48K						= 3,
	SLIMBUS_PR_96K						= 4,
	SLIMBUS_PR_192K 					= 5,
	SLIMBUS_PR_384K 					= 6,
	SLIMBUS_PR_768K 					= 7,
	SLIMBUS_PR_11025					= 9,
	SLIMBUS_PR_22050					= 10,
	SLIMBUS_PR_44100					= 11,
	SLIMBUS_PR_88200					= 12,
	SLIMBUS_PR_176400					= 13,
	SLIMBUS_PR_352800					= 14,
	SLIMBUS_PR_705600					= 15,
	SLIMBUS_PR_4K						= 16,
	SLIMBUS_PR_8K						= 17,
	SLIMBUS_PR_16K						= 18,
	SLIMBUS_PR_32K						= 19,
	SLIMBUS_PR_64K						= 20,
	SLIMBUS_PR_128K 					= 21,
	SLIMBUS_PR_256K 					= 22,
	SLIMBUS_PR_512K 					= 23,

} slimbus_presence_rate_t;

/* data types */
typedef enum
{
	SLIMBUS_DF_NOT_INDICATED			= 0,				/* not indicated. */
	SLIMBUS_DF_LPCM 					= 1,				/* LPCM audio. */
	SLIMBUS_DF_IEC61937 				= 2,				/* IEC61937 compressed audio. */
	SLIMBUS_DF_PACKED_PDM_AUDIO 		= 3,				/* packed PDM audio. */
	SLIMBUS_DF_USER_DEFINED_1			= 14,				/* user defined 1. */
	SLIMBUS_DF_USER_DEFINED_2			= 15,				/* user defined 2. */

} slimbus_data_type_t;

/* auxilary field formats formats */
typedef enum
{
	SLIMBUS_AF_NOT_APPLICABLE			= 0,				/* not applicable. */
	SLIMBUS_AF_ZCUV 					= 1,				/* ZCUV for tunneling IEC60958. */
	SLIMBUS_AF_USER_DEFINED 			= 11,				/* user defined. */

} slimbus_aux_field_format_t;

/* subframe mode codings. CSW - control space width (slots), sl - subframe length (slots) */
typedef enum
{
	SLIMBUS_SM_24_CSW_32_SL 			= 31,
	SLIMBUS_SM_16_CSW_32_SL 			= 29,
	SLIMBUS_SM_16_CSW_24_SL 			= 28,
	SLIMBUS_SM_12_CSW_32_SL 			= 27,
	SLIMBUS_SM_12_CSW_24_SL 			= 26,
	SLIMBUS_SM_8_CSW_32_SL				= 25,
	SLIMBUS_SM_8_CSW_24_SL				= 24,
	SLIMBUS_SM_6_CSW_32_SL				= 23,
	SLIMBUS_SM_6_CSW_24_SL				= 22,
	SLIMBUS_SM_6_CSW_8_SL				= 21,
	SLIMBUS_SM_4_CSW_32_SL				= 19,
	SLIMBUS_SM_4_CSW_24_SL				= 18,
	SLIMBUS_SM_4_CSW_8_SL				= 17,
	SLIMBUS_SM_4_CSW_6_SL				= 16,
	SLIMBUS_SM_3_CSW_32_SL				= 15,
	SLIMBUS_SM_3_CSW_24_SL				= 14,
	SLIMBUS_SM_3_CSW_8_SL				= 13,
	SLIMBUS_SM_3_CSW_6_SL				= 12,
	SLIMBUS_SM_2_CSW_32_SL				= 11,
	SLIMBUS_SM_2_CSW_24_SL				= 10,
	SLIMBUS_SM_2_CSW_8_SL				= 9,
	SLIMBUS_SM_2_CSW_6_SL				= 8,
	SLIMBUS_SM_1_CSW_32_SL				= 7,
	SLIMBUS_SM_1_CSW_24_SL				= 6,
	SLIMBUS_SM_1_CSW_8_SL				= 5,
	SLIMBUS_SM_1_CSW_6_SL				= 4,
	SLIMBUS_SM_8_CSW_8_SL				= 0,				/* 100% control space, 0% data space */
} slimbus_subframe_mode_t;

/** SLIMbus Frequencies and Clock Gear Codings. */
typedef enum
{
	SLIMBUS_CG_0						= 0,				/* not Indicated, Min: 0 MHz, max: 28.8 MHz */
	SLIMBUS_CG_1						= 1,				/* min: 0.025 MHz, max: 0.05625 MHz */
	SLIMBUS_CG_2						= 2,				/* min: 0.05 MHz, max: 0.1125 MHz */
	SLIMBUS_CG_3						= 3,				/* min: 0.1 MHz, max: 0.225 MHz */
	SLIMBUS_CG_4						= 4,				/* min: 0.2 MHz, max: 0.45 MHz */
	SLIMBUS_CG_5						= 5,				/* min: 0.4 MHz, max: 0.9 MHz */
	SLIMBUS_CG_6						= 6,				/* min: 0.8 MHz, max: 1.8 MHz */
	SLIMBUS_CG_7						= 7,				/* min: 1.6 MHz, max: 3.6 MHz */
	SLIMBUS_CG_8						= 8,				/* min: 3.2 MHz, max: 7.2 MHz */
	SLIMBUS_CG_9						= 9,				/* min: 6.4 MHz, max: 14.4 MHz */
	SLIMBUS_CG_10						= 10,				/* min: 12.8 MHz, max: 28.8 MHz */
} slimbus_clock_gear_t;


/** SLIMbus Root Frequency (RF) and Phase Modulus (PM) Codings. */
typedef enum
{
	SLIMBUS_RF_0						= 0,			   /* rf: not indicated, pm: 160 */
	SLIMBUS_RF_1						= 1,			   /* rf: 24.576 MHz, pm: 160 */
	SLIMBUS_RF_2						= 2,			   /* rf: 22.5792 MHz, pm: 147 */
	SLIMBUS_RF_3						= 3,			   /* rf: 15.36 MHz, pm: 100 */
	SLIMBUS_RF_4						= 4,			   /* rf: 16.8 MHz, pm: 875 */
	SLIMBUS_RF_5						= 5,			   /* rf: 19.2 MHz, pm: 125 */
	SLIMBUS_RF_6						= 6,			   /* rf: 24 MHz, pm: 625 */
	SLIMBUS_RF_7						= 7,			   /* rf: 25 MHz, pm: 15625 */
	SLIMBUS_RF_8						= 8,			   /* rf: 26 MHz, pm: 8125 */
	SLIMBUS_RF_9						= 9,			   /* rf: 27 MHz, pm: 5625 */
} slimbus_root_frequency_t;

/* root frequency type */
typedef enum {
	SLIMBUS_RF_24576					= 0,
	SLIMBUS_RF_6144 					= 1,
	SLIMBUS_RF_MAX
} slimbus_rf_type_t;

/* platform type */
typedef enum {
	PLATFORM_PHONE						= 0,
	PLATFORM_UDP						= 1,
	PLATFORM_FPGA						= 2,
} platform_type_t;

/* a track is a combination of channels */
typedef enum {
	SLIMBUS_TRACK_NULL					= -1,
	SLIMBUS_TRACK_AUDIO_PLAY			= 0,
	SLIMBUS_TRACK_AUDIO_CAPTURE,
	SLIMBUS_TRACK_VOICE_DOWN,
	SLIMBUS_TRACK_VOICE_UP,

	SLIMBUS_TRACK_IMAGE_LOAD,
	SLIMBUS_TRACK_ECREF,
	SLIMBUS_TRACK_SOUND_TRIGGER,

	SLIMBUS_TRACK_DEBUG,

	SLIMBUS_TRACK_MAX,
} slimbus_track_type_t;

/* slimbus channel index definition */
typedef enum
{
	AUDIO_PLAY_CHANNEL_LEFT 			= 1,
	AUDIO_PLAY_CHANNEL_RIGHT			= 2,
	AUDIO_CAPTURE_CHANNEL_LEFT			= 3,
	AUDIO_CAPTURE_CHANNEL_RIGHT 		= 4,
	VOICE_DOWN_CHANNEL_LEFT 			= 5,
	VOICE_DOWN_CHANNEL_RIGHT			= 6,
	VOICE_UP_CHANNEL_MIC1				= 7,
	VOICE_UP_CHANNEL_MIC2				= 8,
	VOICE_UP_CHANNEL_MIC3				= 9,
	VOICE_UP_CHANNEL_MIC4				= 10,

	IMAGE_DOWNLOAD						= 11,
	VOICE_ECREF 						= 12,
	AUDIO_ECREF 						= 13,
	SOUND_TRIGGER_CHANNEL_LEFT			= 14,
	SOUND_TRIGGER_CHANNEL_RIGHT 		= 15,
	AUDIO_CAPTURE_CHANNEL_MIC3			= 16,
	AUDIO_CAPTURE_CHANNEL_MIC4			= 17,
	DEBUG_LEFT					= 18,
	DEBUG_RIGHT					= 19,
} slimbus_channel_index_t;


/* restart Time Values. */
typedef enum
{
	/* after a restart request, the active Framer shall resume toggling the CLK line within four cycles of the CLK line frequency (as indicated by the Clock Gear and Root Frequency) used for the upcoming Frame. Optional. */
	SLIMBUS_RT_FAST_RECOVERY			= 0,
	/* after the restart request, the active Framer shall resume toggling the CLK line so the duration of the Pause is an integer number of Superframes in the upcoming Clock Gear. Optional. */
	SLIMBUS_RT_CONSTANT_PHASE_RECOVERY	= 1,
	/* after a restart request, the active Framer shall resume toggling the CLK line after an unspecified delay. Mandatory */
	SLIMBUS_RT_UNSPECIFIED_DELAY		= 2,
} slimbus_restart_time_t;

typedef enum
{
	SLIMBUS_DUMP_IRQ					= 0,
	SLIMBUS_DUMP_FRAMER 				= 1,
	SLIMBUS_DUMP_LOSTMS 				= 2,
	SLIMBUS_DUMP_MAX
} slimbus_dump_state_t;

typedef struct slimbus_device_info {
	uint8_t			generic_la; 			/* generic device logical address  */
	uint8_t			voice_up_chnum; 		/* channel numbers of voice up */
	uint8_t			audio_up_chnum; 		/* channel numbers of audio up */
	uint32_t		page_sel_addr;
	struct mutex		mutex;

	slimbus_rf_type_t	rf; 				/* root frequency */
	int 			slimbusclk_drv;
	int 			slimbusdata_drv;
}slimbus_device_info_t;



/*
 * Data Channel Endpoints
 */
typedef struct {
	uint8_t 							la; 			   /* logical address */
	uint8_t 							pn; 			   /* port number */
} slimbus_port_t;

/*
 * Data Channel properties
 */
typedef struct {
	uint32_t							cn; 				/* channel number */

	/* payload of CONNECT_SOURCE/SINK message */
	slimbus_port_t						source;
	slimbus_port_t						sinks[16];
	uint32_t							sink_num;

	/* payload of NEXT_DEFINE_CHANNEL message*/
	slimbus_transport_protocol_t		tp; 				/* transport protocol */
	uint16_t							sd; 				/* segment_distribution */
	uint16_t							sl; 				/* segment_length */

	/* payload of NEXT_DEFINE_CONTENT message*/
	uint32_t							fl; 				/* frequency locked_bit */
	slimbus_presence_rate_t 			pr; 				/* presence_rate */
	slimbus_aux_field_format_t			af; 				/* auxiliary bit format */
	slimbus_data_type_t 				dt; 				/* dataType */
	uint8_t 							cl; 				/* channel link */
	uint8_t 							dl; 				/* data length */

	uint32_t							active; 			/* whether channel is active */

} slimbus_channel_property_t;


typedef struct slimbus_bus_config {
	slimbus_subframe_mode_t 			sm; 				/* subframe mode */
	slimbus_clock_gear_t				cg; 				/* clock gear */
	slimbus_root_frequency_t			rf; 				/* root frequency */

} slimbus_bus_config_t;

#endif /* __SLIMBUS_TYPES_H__ */
