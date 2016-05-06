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

#ifndef __SLIMBUS_CSMI_H__
#define __SLIMBUS_CSMI_H__

#include <linux/types.h>
#include "csmi.h"
#include "slimbus_types.h"
#include "slimbus_debug.h"

/* address of soc generic device */
#define SOC_EA_GENERIC_DEVICE						0xaaaac1000200
#define SOC_LA_GENERIC_DEVICE						0xD0

/* address of hi6402 generic device */
#define HI6402_EA_GENERIC_DEVICE					0xaaaabbbb0601
#define HI6402_LA_GENERIC_DEVICE					0xD1


/* address of elements */
#define SLIMBUS_USER_DATA_BASE_ADDR 				0x800

/* hi6402 page selection register address */
#define HI6402_PAGE_SELECT_REG_0					(0x1FD + SLIMBUS_USER_DATA_BASE_ADDR)
#define HI6402_PAGE_SELECT_REG_1					(0x1FE + SLIMBUS_USER_DATA_BASE_ADDR)
#define HI6402_PAGE_SELECT_REG_2					(0x1FF + SLIMBUS_USER_DATA_BASE_ADDR)

/* framer id */
#define SLIMBUS_FRAMER_SOC_ID						0
#define SLIMBUS_FRAMER_HI6402_ID					1
#define SLIMBUS_LOSTMS_COUNT						5
extern struct dsm_client *dsm_audio_client;

extern int slimbus_dev_init(platform_type_t plattype);

extern int slimbus_drv_init(platform_type_t plattype, void *regBase, void *asp_reg_base_addr, int irq);

extern int slimbus_drv_stop(void);

extern int slimbus_drv_release(int irq);

extern int slimbus_drv_bus_configure(slimbus_bus_config_t *bus_config);

extern int slimbus_drv_switch_framer(uint8_t  laif, uint16_t NCo, uint16_t NCi, slimbus_bus_config_t *bus_config);

extern int slimbus_drv_element_read(uint8_t  targetLa, uint16_t address, slimbus_slice_size_t sliceSize, void *valueRead);

extern int slimbus_drv_element_write(uint8_t  targetLa, uint16_t address, slimbus_slice_size_t sliceSize, void *valueRead);

extern int slimbus_drv_request_info(uint8_t  targetLa, uint16_t address, slimbus_slice_size_t sliceSize, void *valueRead);

extern int slimbus_drv_track_configure(slimbus_channel_property_t *channel, uint32_t ch_num);

extern int slimbus_drv_track_activate(slimbus_channel_property_t *channel, uint32_t ch_num);

extern int slimbus_drv_track_deactivate(slimbus_channel_property_t *channel, uint32_t ch_num);

extern int slimbus_drv_track_remove(slimbus_channel_property_t *channel, uint32_t ch_num);

extern uint8_t slimbus_drv_get_framerla(int framer_id);

extern int slimbus_drv_pause_clock(slimbus_restart_time_t newrestarttime);

extern int slimbus_drv_resume_clock(void);

extern int slimbus_drv_reset_bus(void);

extern int slimbus_drv_shutdown_bus(void);

extern volatile bool slimbus_int_need_clear_get(void);

extern void slimbus_int_need_clear_set(volatile bool flag);

#endif /* __SLIMBUS_CSMI_H__ */
