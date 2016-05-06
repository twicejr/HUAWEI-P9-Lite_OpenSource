/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef _HW_CCI_H
#define _HW_CCI_H

#include "../sensor/hwsensor.h"
#include "../platform/hi3635/platform_cfg.h"
#include "../platform/sensor_commom.h"

/*I2C control register */
#define REG_SCCB_MAST1_SPEED            (0x63600)
#define REG_SCCB_MAST1_SLAVE_ID         (0x63601)
#define REG_SCCB_MAST1_ADDRESS_H        (0x63602)
#define REG_SCCB_MAST1_ADDRESS_L        (0x63603)
#define REG_SCCB_MAST1_OUTPUT_DATA_H    (0x63604)
#define REG_SCCB_MAST1_OUTPUT_DATA_L    (0x63605)
#define REG_SCCB_MAST1_2BYTE_CONTROL    (0x63606)
#define REG_SCCB_MAST1_INPUT_DATA_H     (0x63607)
#define REG_SCCB_MAST1_INPUT_DATA_L     (0x63608)
#define REG_SCCB_MAST1_COMMAND          (0x63609)
#define REG_SCCB_MAST1_STATUS           (0x6360a)

#define REG_SCCB_MAST2_SPEED            (0x63700)
#define REG_SCCB_MAST2_SLAVE_ID         (0x63701)
#define REG_SCCB_MAST2_ADDRESS_H        (0x63702)
#define REG_SCCB_MAST2_ADDRESS_L        (0x63703)
#define REG_SCCB_MAST2_OUTPUT_DATA_H    (0x63704)
#define REG_SCCB_MAST2_OUTPUT_DATA_L    (0x63705)
#define REG_SCCB_MAST2_2BYTE_CONTROL    (0x63706)
#define REG_SCCB_MAST2_INPUT_DATA_H     (0x63707)
#define REG_SCCB_MAST2_INPUT_DATA_L     (0x63708)
#define REG_SCCB_MAST2_COMMAND          (0x63709)
#define REG_SCCB_MAST2_STATUS           (0x6370a)

#define REG_SCCB_BUS_MUTEX 		(0x1c4ee)

#define REG_SCCB_MAST1_BUS_MUTEX 	(0x32c60)
#define REG_SCCB_MAST2_BUS_MUTEX 	(0x32c70)

#define REG_SCCB_FIRMWARE1_ID           (0x33056)
#define REG_SCCB_FIRMWARE2_ID           (0x33656)

#define MASK_16BIT_ADDR_ENABLE          (1)
#define MASK_16BIT_DATA_ENABLE          (1 << 1)

#define SCCB_BUS_MUTEX_WAIT			(1)
#define SCCB_BUS_MUTEX_NOWAIT		(0)

#define SCCB_MASTER_BUSY                (1)
#define SCCB_MASTER_LOCK           (1)
#define SCCB_MASTER_UNLOCK      (0)

#define ISP_I2C_POLL_INTERVAL 10 /* 10us */
#define ISP_I2C_POLL_MAX_COUNT 4000 /* 4000x10us=40ms */

void hw_isp_config_i2c(i2c_t *i2c_info);

int hw_isp_write_sensor_byte(i2c_t *i2c_info, u16 reg, u16 val, u8 mask);

int hw_isp_write_sensor_seq(i2c_t *i2c_info, const struct sensor_i2c_reg *buf, u32 size);

int hw_isp_read_sensor_byte(i2c_t *i2c_info, u16 reg, u16 *val);

 int hw_isp_write_vcm(u8 i2c_addr, u16 reg, u16 val, i2c_length length);
#endif
