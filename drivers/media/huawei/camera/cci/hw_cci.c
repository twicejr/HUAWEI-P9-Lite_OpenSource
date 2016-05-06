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

#include <linux/gpio.h>
#include <linux/videodev2.h>
#include <linux/platform_device.h>

#include "../platform/sensor_commom.h"
#include "hw_cci.h"
#include "../io/hw_isp_io.h"

static inline int get_i2c_bus_mutex(int bus_mutex)
{
	int count = 0;
	int rc = 0;

	while (count < ISP_I2C_POLL_MAX_COUNT) {
		if ((ISP_GETREG8(bus_mutex) & SCCB_MASTER_LOCK) != SCCB_MASTER_LOCK) {
			ISP_SETREG8(bus_mutex, SCCB_MASTER_LOCK);
			break;
		}
		udelay(ISP_I2C_POLL_INTERVAL);
		//cam_err("%s: bus mutex lock and timeout, wait_flag %d, count %d", __func__, wait_flag, count);
		count++;
	}

	if (count >= ISP_I2C_POLL_MAX_COUNT) {
		cam_err("%s: bus mutex lock failed, count %d", __func__, count);
		rc = -EBUSY;
	}

	return rc;
}

static inline void free_i2c_bus_mutex(int bus_mutex)
{
	ISP_SETREG8(bus_mutex, SCCB_MASTER_UNLOCK);
}

static inline int wait_i2c_bus_idle(u32 reg_status)
{
	int count = 0;

	while (count < ISP_I2C_POLL_MAX_COUNT) {
		if ((ISP_GETREG8(reg_status) & SCCB_MASTER_BUSY) != SCCB_MASTER_BUSY)
			break;
		udelay(ISP_I2C_POLL_INTERVAL);
		count++;
	}
	if (count >= ISP_I2C_POLL_MAX_COUNT) {
		return -EBUSY;
	}
	return 0;
}

void hw_isp_config_i2c(i2c_t *i2c_info)
{
	cam_notice("%s i2c speed %d", __func__, i2c_info->speed);

	if (i2c_info->index == I2C_PRIMARY) {
		ISP_SETREG8(REG_SCCB_MAST1_SPEED, i2c_info->speed);
		ISP_SETREG8(REG_SCCB_MAST1_SLAVE_ID, i2c_info->addr);
		ISP_SETREG8(REG_SCCB_FIRMWARE1_ID, i2c_info->addr);
	} else {
		ISP_SETREG8(REG_SCCB_MAST2_SPEED, i2c_info->speed);
		ISP_SETREG8(REG_SCCB_MAST2_SLAVE_ID, i2c_info->addr);
		ISP_SETREG8(REG_SCCB_FIRMWARE2_ID, i2c_info->addr);
	}
}

static DEFINE_SPINLOCK(i2c_lock);

int hw_isp_read_sensor_byte(i2c_t *i2c_info, u16 reg, u16 *val)
{
	unsigned long flags;
	int reg_device_id, reg_firmware_id, reg_reg_h, reg_reg_l, reg_cmd, reg_status;
	int reg_value_l, reg_value_len, reg_bus_mutex;
	volatile int val_h, val_l;
	volatile int device_id, firmware_id;
	u8 byte_ctrl = 0;

	if (i2c_info->index == I2C_PRIMARY) {
		reg_device_id = REG_SCCB_MAST1_SLAVE_ID;
		reg_firmware_id = REG_SCCB_FIRMWARE1_ID;
		reg_reg_h = REG_SCCB_MAST1_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST1_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST1_COMMAND;
		reg_status = REG_SCCB_MAST1_STATUS;
		reg_value_l = REG_SCCB_MAST1_INPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST1_2BYTE_CONTROL;
		reg_bus_mutex = REG_SCCB_MAST1_BUS_MUTEX;
	} else {
		reg_device_id = REG_SCCB_MAST2_SLAVE_ID;
		reg_firmware_id = REG_SCCB_FIRMWARE2_ID;
		reg_reg_h = REG_SCCB_MAST2_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST2_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST2_COMMAND;
		reg_status = REG_SCCB_MAST2_STATUS;
		reg_value_l = REG_SCCB_MAST2_INPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST2_2BYTE_CONTROL;
		reg_bus_mutex = REG_SCCB_MAST2_BUS_MUTEX;
	}

	if (get_i2c_bus_mutex(reg_bus_mutex)) {
		cam_err("%s, line %d: I2c get mutex timeout!", __func__, __LINE__);
		return -EFAULT;
	}

	if (wait_i2c_bus_idle(reg_status)) {
		cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out2;
	}

	if (I2C_16BIT == i2c_info->addr_bits)
		byte_ctrl |= MASK_16BIT_ADDR_ENABLE;

	spin_lock_irqsave(&i2c_lock, flags);

	/* backup i2c id in isp reg */
	firmware_id = ISP_GETREG8(reg_firmware_id);
	device_id = ISP_GETREG8(reg_device_id);

	if (I2C_8BIT == i2c_info->val_bits) {
		ISP_SETREG8(reg_value_len, byte_ctrl);
		ISP_SETREG8(reg_device_id, i2c_info->addr);
		ISP_SETREG8(reg_firmware_id, i2c_info->addr);
		ISP_SETREG8(reg_reg_h, reg >> 8 & 0xff);
		ISP_SETREG8(reg_reg_l, reg & 0xff);
		ISP_SETREG8(reg_cmd, 0x33);
		if (wait_i2c_bus_idle(reg_status)) {
			cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		ISP_SETREG8(reg_cmd, 0xf9);
		if (wait_i2c_bus_idle(reg_status)) {
			cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		*(u8 *)val = ISP_GETREG8(reg_value_l);
	} else {
		byte_ctrl |= MASK_16BIT_DATA_ENABLE;
		ISP_SETREG8(reg_value_len, byte_ctrl);
		ISP_SETREG8(reg_device_id, i2c_info->addr);
		ISP_SETREG8(reg_firmware_id, i2c_info->addr);
		ISP_SETREG8(reg_reg_h, reg >> 8 & 0xff);
		ISP_SETREG8(reg_reg_l, reg & 0xff);
		ISP_SETREG8(reg_cmd, 0x33);
		if (wait_i2c_bus_idle(reg_status)) {
			cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		ISP_SETREG8(reg_value_len, byte_ctrl & ~MASK_16BIT_DATA_ENABLE);
		ISP_SETREG8(reg_cmd, 0x59);

		if (wait_i2c_bus_idle(reg_status)) {
			cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}

		val_h = ISP_GETREG8(reg_value_l);

		ISP_SETREG8(reg_cmd, 0xa8);
		if (wait_i2c_bus_idle(reg_status)) {
			cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
			goto error_out1;
		}
		val_l = ISP_GETREG8(reg_value_l);

		*val = (val_h << 8) | val_l;
	}

	/* restore i2c id to isp reg */
	ISP_SETREG8(reg_firmware_id, firmware_id);
	ISP_SETREG8(reg_device_id, device_id);

	spin_unlock_irqrestore(&i2c_lock, flags);
	free_i2c_bus_mutex(reg_bus_mutex);
	return 0;

error_out1:
	spin_unlock_irqrestore(&i2c_lock, flags);
error_out2:
	free_i2c_bus_mutex(reg_bus_mutex);
	return -EFAULT;
}

int hw_isp_write_sensor_byte(i2c_t *i2c_info, u16 reg, u16 val, u8 mask)
{

	unsigned long flags;
	int reg_device_id, reg_firmware_id, reg_reg_h, reg_reg_l, reg_cmd, reg_status;
	int reg_value_h, reg_value_l, reg_value_len, reg_bus_mutex;
	u16 old_val = 0;
	u8 byte_ctrl = 0;

	if (i2c_info->index == I2C_PRIMARY) {
		reg_device_id = REG_SCCB_MAST1_SLAVE_ID;
		reg_firmware_id = REG_SCCB_FIRMWARE1_ID;
		reg_reg_h = REG_SCCB_MAST1_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST1_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST1_COMMAND;
		reg_status = REG_SCCB_MAST1_STATUS;
		reg_value_h = REG_SCCB_MAST1_OUTPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST1_OUTPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST1_2BYTE_CONTROL;
		reg_bus_mutex = REG_SCCB_MAST1_BUS_MUTEX;
	} else {
		reg_device_id = REG_SCCB_MAST2_SLAVE_ID;
		reg_firmware_id = REG_SCCB_FIRMWARE2_ID;
		reg_reg_h = REG_SCCB_MAST2_ADDRESS_H;
		reg_reg_l = REG_SCCB_MAST2_ADDRESS_L;
		reg_cmd = REG_SCCB_MAST2_COMMAND;
		reg_status = REG_SCCB_MAST2_STATUS;
		reg_value_h = REG_SCCB_MAST2_OUTPUT_DATA_H;
		reg_value_l = REG_SCCB_MAST2_OUTPUT_DATA_L;
		reg_value_len = REG_SCCB_MAST2_2BYTE_CONTROL;
		reg_bus_mutex = REG_SCCB_MAST2_BUS_MUTEX;
	}

	if (mask != 0x00) {
		hw_isp_read_sensor_byte(i2c_info, reg, &old_val);
		old_val &= mask;
		val = old_val | (val & ~mask);
	}

	if (get_i2c_bus_mutex(reg_bus_mutex)) {
		cam_err("%s, line %d: I2c get mutex timeout!", __func__, __LINE__);
		return -EFAULT;
	}

	if (wait_i2c_bus_idle(reg_status)) {
		cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out2;
	}

	if (I2C_16BIT == i2c_info->addr_bits)
		byte_ctrl |= MASK_16BIT_ADDR_ENABLE;

	spin_lock_irqsave(&i2c_lock, flags);

	ISP_SETREG8(reg_device_id, i2c_info->addr);
	ISP_SETREG8(reg_firmware_id, i2c_info->addr);
	ISP_SETREG8(reg_reg_h, (reg >> 8) & 0xff);
	ISP_SETREG8(reg_reg_l, reg & 0xff);

	if (I2C_8BIT == i2c_info->val_bits) {
		ISP_SETREG8(reg_value_l, val);
		ISP_SETREG8(reg_value_len, byte_ctrl);
	} else {
		byte_ctrl |= MASK_16BIT_DATA_ENABLE;
		ISP_SETREG8(reg_value_h, (val >> 8) & 0xff);
		ISP_SETREG8(reg_value_l, val & 0xff);
		ISP_SETREG8(reg_value_len, byte_ctrl);
	}
	ISP_SETREG8(reg_cmd, 0x37);
	if (wait_i2c_bus_idle(reg_status)) {
		cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out1;
	}

	spin_unlock_irqrestore(&i2c_lock, flags);
	free_i2c_bus_mutex(reg_bus_mutex);

	if (I2C_16BIT == i2c_info->val_bits)
		udelay(50);

	return 0;

error_out1:
	spin_unlock_irqrestore(&i2c_lock, flags);
error_out2:
	free_i2c_bus_mutex(reg_bus_mutex);
	return -EFAULT;

	return 0;
}

int hw_isp_write_sensor_seq(i2c_t *i2c_info, const struct sensor_i2c_reg *buf, u32 size)
{
    int i;
    int rc = 0;
    i2c_t t_i2c_info;

    memcpy(&t_i2c_info, i2c_info, sizeof(i2c_t));

    /* use AP write mode */
    for (i = 0; i < size; i++) {
        if (0xFF == buf[i].subaddr || 0xFFFF == buf[i].subaddr)
        {
            cam_info("%s entered here to sleep %d ms", __func__, buf[i].value);
            msleep(buf[i].value);
            continue;
        }
        if (1 == buf[i].size)
        {
            t_i2c_info.val_bits = I2C_8BIT;
        }
        else if (2 == buf[i].size)
        {
            t_i2c_info.val_bits = I2C_16BIT;
        }
        else
        {
        }

        rc = hw_isp_write_sensor_byte(&t_i2c_info, buf[i].subaddr, buf[i].value, buf[i].mask);
        if (rc < 0) {
            cam_err("%s  write sensor seq error, i=%d, subaddr=0x%x, value=0x%x, mask=0x%x.",
            __func__, i, buf[i].subaddr, buf[i].value, buf[i].mask);
            return rc;
        }
    }

    return 0;
}

 int hw_isp_write_vcm(u8 i2c_addr, u16 reg, u16 val, i2c_length length)
 {
	unsigned long flags;
	volatile u8 original_config;
	int reg_bus_mutex = REG_SCCB_MAST1_BUS_MUTEX;

	if (get_i2c_bus_mutex(reg_bus_mutex)) {
		cam_err("%s, line %d: I2c get mutex timeout!", __func__, __LINE__);
		return -EFAULT;
	}

	if (wait_i2c_bus_idle(REG_SCCB_MAST1_STATUS)) {
		cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out2;
	}
	original_config = ISP_GETREG8(REG_SCCB_MAST1_2BYTE_CONTROL);
	spin_lock_irqsave(&i2c_lock, flags);

	if (I2C_16BIT == length) {
		if (0 == reg) {
			/*enable 16bit data,disable 16bit address*/
			ISP_SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, 0x02);
		} else {
			/*enable 16bit data,enable 16bit address*/
			ISP_SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, 0x03);
		}
	} else {
		/*disable 16bit data,disable 16bit address*/
		ISP_SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, 0x00);
	}
	ISP_SETREG8(REG_SCCB_MAST1_SLAVE_ID, i2c_addr);
	/*input address*/
	if (0 != reg) {
		if (I2C_16BIT == length) {
			ISP_SETREG8(REG_SCCB_MAST1_ADDRESS_H, (reg >> 8) & 0xff);
		}
		ISP_SETREG8(REG_SCCB_MAST1_ADDRESS_L, reg & 0xff);
	}
	/*input data*/
	if (I2C_16BIT == length) {
		ISP_SETREG16(REG_SCCB_MAST1_OUTPUT_DATA_H, val);
	} else {
		ISP_SETREG8(REG_SCCB_MAST1_OUTPUT_DATA_L, val);
	}

	if (0 != reg) {
		ISP_SETREG8(REG_SCCB_MAST1_COMMAND, 0x37);
	} else {
		/*no address case*/
		ISP_SETREG8(REG_SCCB_MAST1_COMMAND, 0x35);
	}
	ISP_SETREG8(REG_SCCB_MAST1_2BYTE_CONTROL, original_config);
	if (wait_i2c_bus_idle(REG_SCCB_MAST1_STATUS)) {
		cam_err("%s, line %d: I2c wait idle timeout!", __func__, __LINE__);
		goto error_out1;
	}

	spin_unlock_irqrestore(&i2c_lock, flags);
	free_i2c_bus_mutex(reg_bus_mutex);
	return 0;

error_out1:
	spin_unlock_irqrestore(&i2c_lock, flags);
error_out2:
	free_i2c_bus_mutex(reg_bus_mutex);
	return -EFAULT;
}
