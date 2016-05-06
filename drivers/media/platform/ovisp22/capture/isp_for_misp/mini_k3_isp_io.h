/*
 *  Hisilicon K3 soc camera ISP driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __MINI_K3_ISP_IO_H__
#define __MINI_K3_ISP_IO_H__

#include "k3_isp_io_comm.h"

#include "../camera.h"

typedef struct {
	char name[50];
	struct regulator *regulator;
	u32 vol_min;
	u32 vol_max;
} mini_sensor_ldo_t;

/*
 * isp register struct
 * used for initialize isp registers
 */
struct mini_isp_reg_t {
	u32 subaddr;
	u8 value;
	u8 mask;
};

typedef struct _mini_isp_io_data {
	bool inited;
	bool csi_inited;
} mini_isp_io_data_t;

typedef struct _mini_isp_regulator_info {
    unsigned gpio;
    char    *label;
} mini_isp_regulator_info_t;

typedef struct _mini_isp_io_gpio_regulator {
    mini_isp_regulator_info_t camera_analog;
    mini_isp_regulator_info_t camera_io_vcc;
    mini_isp_regulator_info_t camera_core_vdd;
    mini_isp_regulator_info_t camera_vcm_vcc;
} mini_isp_io_gpio_regulator_t;

struct _mini_sensor_reg_t;
struct _mini_camera_sensor;
struct _mini_sensor_reg_t;
/* Sensor driver read/write I2C through ISP */
int mini_k3_ispio_read_reg(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length, i2c_length addr_len);
int mini_k3_ispio_write_reg(i2c_index_t index, u8 i2c_addr, u16 reg, u16 val, i2c_length length, u8 mask, i2c_length addr_len);
int mini_k3_ispio_write_seq(i2c_index_t index, u8 i2c_addr, const struct _mini_sensor_reg_t *buf,
	u32 size, i2c_length length, u8 mask, i2c_length addr_len);
int mini_k3_ispio_write_group_seq(i2c_index_t index, u8 i2c_addr,
			     const struct _mini_sensor_reg_t *buf, u32 size);
void mini_k3_ispio_write_isp_seq(const struct mini_isp_reg_t *seq, u32 size);
void mini_k3_ispio_read_isp_seq(struct mini_isp_reg_t *seq, u32 size);
void mini_k3_ispio_update_flip(u8 flip_changed, u16 width, u16 height, pixel_order changed);
int mini_k3_ispldo_power_sensor(camera_power_state power_state,  char *ldo_name);
int mini_k3_ispgpio_power_sensor(struct _mini_camera_sensor *sensor,
			    camera_power_state power_state);
int mini_k3_socgpio_power_sensor(int value, unsigned gpio);
int mini_k3_ispio_ioconfig(struct _mini_camera_sensor *sensor,
			  camera_power_state power_state);
int mini_k3_ispgpio_reset_sensor(sensor_index_t sensor_index, camera_power_state power_state, electrical_valid_t reset_valid);
void mini_k3_isp_io_enable_mclk(mclk_state state, sensor_index_t sensor_index);
int mini_k3_ispio_power_init(char *ldo_name, u32 vol_min, u32 vol_max);
void mini_k3_ispio_power_deinit(void);
int mini_k3_ispio_init_csi(csi_index_t mipi_index, csi_lane_t mipi_lane_count, u8 lane_clk);
void mini_k3_ispio_deinit_csi(csi_index_t mipi_index);

struct platform_device;
typedef struct _mini_ispio_controller {
	int (*power_init) (char *ldo_name, u32 vol_min, u32 vol_max);
	void (*power_deinit) (void);
	int (*power_sensor) (camera_power_state power_state, char *ldo_name);
	int (*ispio_hw_init) (struct platform_device *pdev);
	int (*ispio_hw_deinit) (void);
	int (*init_csi) (csi_index_t csi_index, csi_lane_t mipi_lane_count, u8 lane_clk);
	void (*deinit_csi) (csi_index_t index);
	int (*ioconfig) (camera_power_state power_state, data_interface_t);
} mini_ispio_controller;

typedef struct _mini_isp_sensor_reg_controller {
	/* Sensor driver read/write I2C through ISP */
	int (*isp_read_sensor_reg)(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length, i2c_length addr_len);
	int (*isp_write_sensor_reg)(i2c_index_t index, u8 i2c_addr, u16 reg, u16 val, i2c_length length, u8 mask, i2c_length addr_len);
	int (*isp_write_sensor_seq)(i2c_index_t index, u8 i2c_addr, const struct _mini_sensor_reg_t *reg,
		u32 size, i2c_length length, u8 mask, i2c_length addr_len);
	int (*isp_write_sensor_group_seq)(i2c_index_t index, u8 i2c_addr,
					const struct _mini_sensor_reg_t *reg, u32 size);
	void (*isp_write_isp_seq) (const struct mini_isp_reg_t *seq, u32 size);
	void (*isp_read_isp_seq) (struct mini_isp_reg_t *seq, u32 size);

	void (*isp_update_flip)(u8 flip_change, u16 width, u16 height, pixel_order changed);

	void (*isp_power_sensor) (sensor_index_t sensor_index,
				  camera_power_state power_state,
				  electrical_valid_t pd_valid,
				  electrical_valid_t vcmpd_valid);
	void (*isp_reset_sensor) (sensor_index_t sensor_index, camera_power_state power_state,
				  electrical_valid_t reset_valid);
	void (*isp_enable_mclk) (mclk_state state, sensor_index_t sensor_index);
} mini_isp_sensor_reg_controller;

mini_ispio_controller *mini_get_ispio_controller(void);
mini_isp_sensor_reg_controller *mini_get_isp_sensor_reg_controller(void);

#endif /*__K3_ISP_IO_H__ */

/********************** END **********************/
