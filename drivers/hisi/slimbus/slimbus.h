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

#ifndef __SLIMBUS_H__
#define __SLIMBUS_H__

#include <linux/types.h>
#include "slimbus_types.h"
#include <sound/asound.h>

/* slimbus can attach more than one devices */
typedef enum {
	SLIMBUS_DEVICE_HI6402			= 0,
	SLIMBUS_DEVICE_HI6403,
	SLIMBUS_DEVICE_NUM,

} slimbus_device_type_t;

typedef enum {
	SLIMBUS_FRAMER_SOC			= 0,
	SLIMBUS_FRAMER_CODEC,
	SLIMBUS_FRAMER_NUM,

} slimbus_framer_type_t;

typedef enum {
	SLIMBUS_BUS_CONFIG_NORMAL			= 0,
	SLIMBUS_BUS_CONFIG_IMGDOWN			= 1,
	SLIMBUS_BUS_CONFIG_SWITCH_FRAMER	= 2,
	SLIMBUS_BUS_CONFIG_REGIMGDOWN		= 3,
	SLIMBUS_BUS_CONFIG_MAX,

} slimbus_bus_config_type_t;

/* configuration for a stream */
typedef struct slimbus_track_param {
	uint32_t			channels;
	uint32_t			rate;
	uint32_t			period_size;
	uint32_t			period_count;
	snd_pcm_format_t	format;
} slimbus_track_param_t;

/*
 * read element value via byte address (see specification for more details
 * about difference between byte address and element address)
 * @dev, pointer to slimbus device instance
 * @byte_address, byte address of element
 * @slice_size, see slimbus_slice_size_t
 * @value, pre-allocated memory, contains read element value
 *
 * return 0 if read successful, otherwise, read failed
 */
extern int slimbus_element_read(
				slimbus_device_info_t	*dev,
				int32_t			byte_address,
				slimbus_slice_size_t	slice_size,
				void				   *value);

/*
 * write element value via byte address (see specification for more details
 * about difference between byte address and element address)
 * @dev_type, pointer to slimbus device type
 * @byte_address, byte address of element
 * @slice_size, see slimbus_slice_size_t
 * @value, values to be writtern
 *
 * return 0 if write successful, otherwise, write failed
 */
extern int slimbus_element_write(
				slimbus_device_info_t	*dev,
				int32_t			byte_address,
				slimbus_slice_size_t	slice_size,
				void			*value);

/*
 * setup channel, this step should be done by sending CONNECT_SOURCE,
 * CONNECT_SINK, NEXT_DEFINE_CHANNEL, NEXT_DEFINE_CONTENT messages
 * @dev_type, pointer to slimbus device type
 * @track,	track type
 * @params, pcm parameters
 *
 * return 0 if successful, otherwise, failed
 */
extern int slimbus_track_configure(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t	*params);

/*
 * activate channel, this step should be done by sending
 * NEXT_ACTIVATE_CHANNEL message
 * @dev_type, pointer to slimbus device type
 * @track,	track type
 *
 * return 0 if successful, otherwise, failed
 */
extern int slimbus_track_activate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track);
/*
 * de-activate channel, this step should be done by sending
 * NEXT_DEACTIVATE_CHANNEL message
 * @dev_type, pointer to slimbus device type
 * @track,	track type
 *
 * return 0 if successful, otherwise, failed
 */
extern int slimbus_track_deactivate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track);

/*
 * remove channel, this step should be done by sending
 * NEXT_REMOVE_CHANNEL message
 * @dev_type, pointer to slimbus device type
 * @track,	track type
 *
 * return 0 if successful, otherwise, failed
 */
extern int slimbus_track_remove(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track);

/*
 * switch framer, this step should be done by sending
 * NEXT_ACTIVE_FRAMER message
 * @dev_type, pointer to slimbus device
 * @framer_type, which device switch to
 *
 * return 0 if successful, otherwise, failed
 */
extern int slimbus_switch_framer(
				slimbus_device_type_t	dev_type,
				slimbus_framer_type_t	framer_type);

/*
 * pause clock, this step should be done by sending
 * NEXT_PAUSE_CLOCK message
 * @dev_type, pointer to slimbus device
 * @newrestarttime restart time control flag.
 *
 * return 0 if successful, otherwise, failed
 */
extern int slimbus_pause_clock(
				slimbus_device_type_t	dev_type,
				slimbus_restart_time_t	newrestarttime);

/*
 * set slimbus params
 * @dev_type, pointer to slimbus device type
 * @track,	track type
 * @params, pcm parameters
 *
 * return 0 if successful, otherwise, failed
 */

extern int slimbus_param_set(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t  *params);

extern int slimbus_track_recover(void);

#endif /* __SLIMBUS_H__ */
