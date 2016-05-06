/*
 * Synaptics DSX touchscreen driver
 *
 * Copyright (C) 2012 Synaptics Incorporated
 *
 * Copyright (C) 2012 Alexandra Chin <alexandra.chin@tw.synaptics.com>
 * Copyright (C) 2012 Scott Lin <scott.lin@tw.synaptics.com>
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
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/firmware.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/vmalloc.h>
#include "synaptics.h"
#include <../../huawei_touchscreen_chips.h>

#define FORCE_UPDATE false
//#define DO_LOCKDOWN false

//#define MAX_IMAGE_NAME_LEN 256
//#define MAX_FIRMWARE_ID_LEN 10

//#define LOCKDOWN_OFFSET 0xb0
#define FW_IMAGE_OFFSET 0x100

#define BOOTLOADER_ID_OFFSET 0
#define BLOCK_NUMBER_OFFSET 0

#define V5_PROPERTIES_OFFSET 2
#define V5_BLOCK_SIZE_OFFSET 3
#define V5_BLOCK_COUNT_OFFSET 5
#define V5_BLOCK_DATA_OFFSET 2

#define V6_PROPERTIES_OFFSET 1
#define V6_BLOCK_SIZE_OFFSET 2
#define V6_BLOCK_COUNT_OFFSET 3
#define V6_BLOCK_DATA_OFFSET 1
#define V6_FLASH_COMMAND_OFFSET 2
#define V6_FLASH_STATUS_OFFSET 3
#define FIRMWARE_LEN 100*1024

//#define LOCKDOWN_BLOCK_COUNT 5

//#define REG_MAP (1 << 0)
//#define UNLOCKED (1 << 1)
//#define HAS_CONFIG_ID (1 << 2)
#define HAS_PERM_CONFIG (1 << 3)
#define HAS_BL_CONFIG (1 << 4)
#define HAS_DISP_CONFIG (1 << 5)
//#define HAS_CTRL1 (1 << 6)
#define RMI_PRODUCT_ID_LENGTH    10

enum flash_config_area {
	UI_CONFIG_AREA		= 0x00,
	PERM_CONFIG_AREA	= 0x01,
	BL_CONFIG_AREA		= 0x02,
	DISP_CONFIG_AREA	= 0x03
};

enum flash_command {
	CMD_WRITE_FW_BLOCK		= 0x2,
	CMD_ERASE_ALL			= 0x3,
	CMD_WRITE_LOCKDOWN_BLOCK = 0x4,
	CMD_READ_CONFIG_BLOCK	= 0x5,
	CMD_WRITE_CONFIG_BLOCK	= 0x6,
	CMD_ERASE_CONFIG		= 0x7,
	CMD_READ_SENSOR_ID		= 0x8,
	CMD_ERASE_BL_CONFIG		= 0x9,
	CMD_ERASE_DISP_CONFIG	= 0xA,
	CMD_ENABLE_FLASH_PROG	= 0xF
};

enum flash_area {
	NONE,
	UI_FIRMWARE,
	CONFIG_AREA
};


#define SLEEP_MODE_NORMAL (0x00)
//#define SLEEP_MODE_SENSOR_SLEEP (0x01)
//#define SLEEP_MODE_RESERVED0 (0x02)
//#define SLEEP_MODE_RESERVED1 (0x03)

#define ENABLE_WAIT_MS (1 * 1000)
#define WRITE_WAIT_MS (3 * 1000)
#define ERASE_WAIT_MS (5 * 1000)

#define MIN_SLEEP_TIME_US 50
#define MAX_SLEEP_TIME_US 100


enum bl_version {
	V5 = 5,
	V6 = 6,
};

struct image_header {
	/* 0x00 - 0x0f */
	unsigned char checksum[4];
	unsigned char reserved_04;
	unsigned char reserved_05;
	unsigned char options_firmware_id:1;
	unsigned char options_contain_bootloader:1;
	unsigned char options_reserved:6;
	unsigned char bootloader_version;
	unsigned char firmware_size[4];
	unsigned char config_size[4];
	/* 0x10 - 0x1f */
	unsigned char product_id[SYNAPTICS_RMI4_PRODUCT_ID_SIZE];
	unsigned char package_id[2];
	unsigned char package_id_revision[2];
	unsigned char product_info[SYNAPTICS_RMI4_PRODUCT_INFO_SIZE];
	/* 0x20 - 0x2f */
	unsigned char reserved_20_2f[16];
	/* 0x30 - 0x3f */
	unsigned char ds_id[16];
	/* 0x40 - 0x4f */
	unsigned char ds_info[10];
	unsigned char reserved_4a_4f[6];
	/* 0x50 - 0x53 */
	unsigned char firmware_id[4];
};

struct image_header_data {
	bool contains_firmware_id;
	unsigned int firmware_id;
	unsigned int checksum;
	unsigned int firmware_size;
	unsigned int config_size;
	unsigned char bootloader_version;
	unsigned char product_id[SYNAPTICS_RMI4_PRODUCT_ID_SIZE + 1];
	unsigned char product_info[SYNAPTICS_RMI4_PRODUCT_INFO_SIZE];
};

struct pdt_properties {
	union {
		struct {
			unsigned char reserved_1:6;
			unsigned char has_bsr:1;
			unsigned char reserved_2:1;
		} __packed;
		unsigned char data[1];
	};
};

struct f01_device_status {
	union {
		struct {
			unsigned char status_code:4;
			unsigned char reserved:2;
			unsigned char flash_prog:1;
			unsigned char unconfigured:1;
		} __packed;
		unsigned char data[1];
	};
};

struct f01_device_control {
	union {
		struct {
			unsigned char sleep_mode:2;
			unsigned char nosleep:1;
			unsigned char reserved:2;
			unsigned char charger_connected:1;
			unsigned char report_rate:1;
			unsigned char configured:1;
		} __packed;
		unsigned char data[1];
	};
};

struct synaptics_rmi4_fwu_handle {
	enum bl_version bl_version;
	bool initialized;
	bool program_enabled;
	bool has_perm_config;
	bool has_bl_config;
	bool has_disp_config;
	bool force_update;
	bool in_flash_prog_mode;
	bool do_lockdown;
	unsigned int data_pos;
	unsigned int image_size;
	const unsigned char *fw_image;
	unsigned char *fw_entry_sd;
	const struct firmware *fw_entry_boot;
	unsigned char *image_name;
	unsigned char *ext_data_source;
	unsigned char *read_config_buf;
	unsigned char command;
	unsigned char bootloader_id[2];
	unsigned char flash_properties;
	unsigned char flash_status;
	unsigned char productinfo1;
	unsigned char productinfo2;
	unsigned char properties_off;
	unsigned char blk_size_off;
	unsigned char blk_count_off;
	unsigned char blk_data_off;
	unsigned char flash_cmd_off;
	unsigned char flash_status_off;
	unsigned short block_size;
	unsigned short fw_block_count;
	unsigned short config_block_count;
	unsigned short lockdown_block_count;
	unsigned short perm_config_block_count;
	unsigned short bl_config_block_count;
	unsigned short disp_config_block_count;
	unsigned short config_size;
	unsigned short config_area;
	char product_id[SYNAPTICS_RMI4_PRODUCT_ID_SIZE + 1];
	const unsigned char *firmware_data;
	const unsigned char *config_data;
	const unsigned char *lockdown_data;
	struct synaptics_rmi4_fn_desc f01_fd;
	struct synaptics_rmi4_fn_desc f34_fd;
	struct synaptics_rmi4_exp_fn_ptr *fn_ptr;
	struct synaptics_rmi4_data *rmi4_data;
};

static struct synaptics_rmi4_fwu_handle *fwu = NULL;

#if defined (CONFIG_HUAWEI_DSM)
extern struct ts_data g_ts_data;
#endif

static int fwu_scan_pdt(void);

static DECLARE_COMPLETION(fwu_remove_complete);

static unsigned int extract_uint_le(const unsigned char *ptr)
{
	return (unsigned int)ptr[0] +
			(unsigned int)ptr[1] * 0x100 +
			(unsigned int)ptr[2] * 0x10000 +
			(unsigned int)ptr[3] * 0x1000000;
}

static unsigned int extract_uint_be(const unsigned char *ptr)
{
	return (unsigned int)ptr[3] +
			(unsigned int)ptr[2] * 0x100 +
			(unsigned int)ptr[1] * 0x10000 +
			(unsigned int)ptr[0] * 0x1000000;
}

static void parse_header(struct image_header_data *header,
		const unsigned char *fw_image)
{
	struct image_header *data = (struct image_header *)fw_image;

	header->checksum = extract_uint_le(data->checksum);

	header->bootloader_version = data->bootloader_version;

	header->firmware_size = extract_uint_le(data->firmware_size);

	header->config_size = extract_uint_le(data->config_size);

	memcpy(header->product_id, data->product_id, sizeof(data->product_id));
	header->product_id[sizeof(data->product_id)] = 0;

	memcpy(header->product_info, data->product_info,
			sizeof(data->product_info));

	header->contains_firmware_id = data->options_firmware_id;
	if (header->contains_firmware_id)
		header->firmware_id = extract_uint_le(data->firmware_id);

	return;
}

static int fwu_read_f01_device_status(struct f01_device_status *status)
{
	int retval;

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f01_fd.data_base_addr,
			status->data,
			sizeof(status->data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read F01 device status\n");
		return retval;
	}

	return 0;
}

static int synaptics_get_f34_addr(struct synaptics_rmi4_data *rmi4_data, unsigned char*f34_address)
{
	int retval;
	unsigned short addr;
	struct synaptics_rmi4_fn_desc rmi_fd;

	for (addr = PDT_START; addr > PDT_END; addr -= PDT_ENTRY_SIZE)
	{
		retval = rmi4_data->i2c_read(rmi4_data, addr, (unsigned char *)&rmi_fd, sizeof(rmi_fd));
		if (retval < 0) {
			TS_LOG_ERR("Failed to read map register\n");
			return retval;
		}

		if (SYNAPTICS_RMI4_F34 == rmi_fd.fn_number) {
			TS_LOG_INFO("Found F%02x\n", rmi_fd.fn_number);
			*f34_address = rmi_fd.ctrl_base_addr;
			return NO_ERR;
		}
	}
	TS_LOG_ERR("Failed to get f34 addr\n");
	return -EINVAL;
}

int synaptics_fw_configid(struct synaptics_rmi4_data *rmi4_data, u8 *buf, size_t buf_size)
{
	int rc = 0;
	unsigned char config_id[4];
	unsigned char f34_ctrl_base_addr = 0;

	TS_LOG_INFO("synaptics_fw_configid called\n");

	rc = synaptics_get_f34_addr(rmi4_data, &f34_ctrl_base_addr);
	if (rc < 0){
		TS_LOG_ERR("failed to scan pdt\n");
	}

	rc = rmi4_data->i2c_read(rmi4_data, f34_ctrl_base_addr, config_id, sizeof(config_id));
	if (rc < 0) {
		TS_LOG_ERR("Could not read configid\n");
		return rc;
	}

	TS_LOG_INFO("config ID 0x%02X, 0x%02X, 0x%02X, 0x%02X,addr = 0x%02x\n",
                                config_id[0], config_id[1], config_id[2], config_id[3], f34_ctrl_base_addr);

	snprintf(buf, buf_size, "%02x %02x %02x %02x\n",
			config_id[0],
			config_id[1],
			config_id[2],
			config_id[3]);

	TS_LOG_INFO("buf = %s\n", buf);
	return 0;
}

static int fwu_read_f34_queries(void)
{
	int retval;
	unsigned char count;
	unsigned char buf[10];

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f34_fd.query_base_addr + BOOTLOADER_ID_OFFSET,
			fwu->bootloader_id,
			sizeof(fwu->bootloader_id));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read bootloader ID\n");
		return retval;
	}

	TS_LOG_INFO("bootloader_id[1] = %c", fwu->bootloader_id[1]);

	if (fwu->bootloader_id[1] == '5') {
		fwu->bl_version = V5;
	} else if (fwu->bootloader_id[1] == '6') {
		fwu->bl_version = V6;
	} else {
		TS_LOG_ERR("Unrecognized bootloader version\n");
		return -EINVAL;
	}

	if (fwu->bl_version == V5) {
		fwu->properties_off = V5_PROPERTIES_OFFSET;
		fwu->blk_size_off = V5_BLOCK_SIZE_OFFSET;
		fwu->blk_count_off = V5_BLOCK_COUNT_OFFSET;
		fwu->blk_data_off = V5_BLOCK_DATA_OFFSET;
	} else if (fwu->bl_version == V6) {
		fwu->properties_off = V6_PROPERTIES_OFFSET;
		fwu->blk_size_off = V6_BLOCK_SIZE_OFFSET;
		fwu->blk_count_off = V6_BLOCK_COUNT_OFFSET;
		fwu->blk_data_off = V6_BLOCK_DATA_OFFSET;
	}

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f34_fd.query_base_addr + fwu->properties_off,
			&fwu->flash_properties,
			sizeof(fwu->flash_properties));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read flash properties\n");
		return retval;
	}

	count = 4;

	if (fwu->flash_properties & HAS_PERM_CONFIG) {
		fwu->has_perm_config = 1;
		count += 2;
	}

	if (fwu->flash_properties & HAS_BL_CONFIG) {
		fwu->has_bl_config = 1;
		count += 2;
	}

	if (fwu->flash_properties & HAS_DISP_CONFIG) {
		fwu->has_disp_config = 1;
		count += 2;
	}

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f34_fd.query_base_addr + fwu->blk_size_off,
			buf,
			2);
	if (retval < 0) {
		TS_LOG_ERR("Failed to read block size info\n");
		return retval;
	}

	batohs(&fwu->block_size, &(buf[0]));

	if (fwu->bl_version == V5) {
		fwu->flash_cmd_off = fwu->blk_data_off + fwu->block_size;
		fwu->flash_status_off = fwu->flash_cmd_off;
	} else if (fwu->bl_version == V6) {
		fwu->flash_cmd_off = V6_FLASH_COMMAND_OFFSET;
		fwu->flash_status_off = V6_FLASH_STATUS_OFFSET;
	}

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f34_fd.query_base_addr + fwu->blk_count_off,
			buf,
			count);
	if (retval < 0) {
		TS_LOG_ERR("Failed to read block count info\n");
		return retval;
	}

	batohs(&fwu->fw_block_count, &(buf[0]));
	batohs(&fwu->config_block_count, &(buf[2]));

	count = 4;

	if (fwu->has_perm_config) {
		batohs(&fwu->perm_config_block_count, &(buf[count]));
		count += 2;
	}

	if (fwu->has_bl_config) {
		batohs(&fwu->bl_config_block_count, &(buf[count]));
		count += 2;
	}

	if (fwu->has_disp_config)
		batohs(&fwu->disp_config_block_count, &(buf[count]));

	return 0;
}

static int fwu_read_f34_flash_status(void)
{
	int retval;
	unsigned char status;
	unsigned char command;

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f34_fd.data_base_addr + fwu->flash_status_off,
			&status,
			sizeof(status));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read flash status\n");
		return retval;
	}

	fwu->program_enabled = status >> 7;

	if (fwu->bl_version == V5)
		fwu->flash_status = (status >> 4) & MASK_3BIT;
	else if (fwu->bl_version == V6)
		fwu->flash_status = status & MASK_3BIT;

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f34_fd.data_base_addr + fwu->flash_cmd_off,
			&command,
			sizeof(command));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read flash command\n");
		return retval;
	}

	if (fwu->bl_version == V5)
		fwu->command = command & MASK_4BIT;
	else if (fwu->bl_version == V6)
		fwu->command = command & MASK_4BIT;

	return 0;
}

static int fwu_reset_device(void)
{
	int retval;

	TS_LOG_INFO("fwu_reset_device called\n");

	retval = fwu->rmi4_data->reset_device(fwu->rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to reset core driver after reflash\n");
		return retval;
	}
	return 0;
}

static int fwu_write_f34_command(unsigned char cmd)
{
	int retval;
	unsigned char command;

	fwu->command = cmd;

	if (fwu->bl_version == V5)
		command = cmd & MASK_4BIT;
	else if (fwu->bl_version == V6)
		command = cmd & MASK_4BIT;

	retval = fwu->fn_ptr->write(fwu->rmi4_data,
			fwu->f34_fd.data_base_addr + fwu->flash_cmd_off,
			&command,
			sizeof(command));
	if (retval < 0) {
		TS_LOG_ERR("Failed to write command 0x%02x\n", command);
		return retval;
	}

	return 0;
}

static int fwu_wait_for_idle(int timeout_ms)
{
	int count = 0;
	int timeout_count = ((timeout_ms * 1000) / MAX_SLEEP_TIME_US) + 1;
	int retval = 0;

	do {
		usleep_range(MIN_SLEEP_TIME_US, MAX_SLEEP_TIME_US);

		count++;
		/*if (count == timeout_count)*/
		TS_LOG_DEBUG("flash command 0x%02x, status 0x%02x\n", fwu->command, fwu->flash_status);

		retval = fwu_read_f34_flash_status();
		if(retval < 0){
			TS_LOG_ERR("Failed to read f34 flash status: %d\n", retval);
		}
		if ((fwu->command == 0x00) && (fwu->flash_status == 0x00))
			return 0;

	} while (count < timeout_count);

	TS_LOG_ERR("timeout\n");
	return -ETIMEDOUT;
}

static enum flash_area fwu_go_nogo(struct image_header_data *header)
{
	int retval = 0;
	int imageConfigID;
	int deviceConfigID;
	unsigned char config_id[4];
	enum flash_area flash_area = NONE;
	struct f01_device_status f01_device_status;

	retval = fwu_read_f01_device_status(&f01_device_status);
	if (retval < 0) {
		flash_area = NONE;
		goto exit;
	}

	/* Force update firmware when device is in bootloader mode */
	if (f01_device_status.flash_prog) {
		TS_LOG_INFO("In flash prog mode\n");
		flash_area = UI_FIRMWARE;
		goto exit;
	}

	/* device config id */
	retval = fwu->fn_ptr->read(fwu->rmi4_data,
				fwu->f34_fd.ctrl_base_addr,
				config_id,
				sizeof(config_id));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read config ID (code %d).\n", retval);
		flash_area = NONE;
		goto exit;
	}
	deviceConfigID = extract_uint_be(config_id);

	TS_LOG_INFO("Device config ID 0x%02X, 0x%02X, 0x%02X, 0x%02X,addr = 0x%02x\n",
			config_id[0], config_id[1], config_id[2], config_id[3],fwu->f34_fd.ctrl_base_addr);

	/* .img config id */
	TS_LOG_INFO("Img config ID 0x%02X, 0x%02X, 0x%02X, 0x%02X\n",
			fwu->config_data[0],
			fwu->config_data[1],
			fwu->config_data[2],
			fwu->config_data[3]);
	imageConfigID =  extract_uint_be(fwu->config_data);
	
	snprintf(fwu->rmi4_data->rmi4_mod_info.device_config_id, sizeof(unsigned char) * CHIP_INFO_LENGTH, 
		"%02x %02x %02x %02x\n",
		config_id[0], config_id[1], config_id[2], config_id[3]);
	snprintf(fwu->rmi4_data->rmi4_mod_info.image_config_id, sizeof(unsigned char) * CHIP_INFO_LENGTH, 
		"%02x %02x %02x %02x\n",
		fwu->config_data[0], fwu->config_data[1], fwu->config_data[2], fwu->config_data[3]);

	TS_LOG_INFO("Device config ID %d, .img config ID %d\n", deviceConfigID, imageConfigID);

	if (imageConfigID != deviceConfigID) {
		TS_LOG_INFO("img configid is different from device configid\n");
		flash_area = UI_FIRMWARE;
		goto exit;
	}

exit:
	if (flash_area == NONE)
		TS_LOG_INFO("Nothing needs to be updated\n");
	else
		TS_LOG_INFO("Update %s block\n", flash_area == UI_FIRMWARE ? "UI FW" : "CONFIG");
	return flash_area;
}

static int fwu_scan_pdt(void)
{
	int retval;
	unsigned short addr;
	bool f01found = false;
	bool f34found = false;
	struct synaptics_rmi4_fn_desc rmi_fd;

	TS_LOG_INFO("fwu_scan_pdt called\n");

	for (addr = PDT_START; addr > PDT_END; addr -= PDT_ENTRY_SIZE) {
		retval = fwu->fn_ptr->read(fwu->rmi4_data,
					addr,
					(unsigned char *)&rmi_fd,
					sizeof(rmi_fd));
		if (retval < 0)
			return retval;

		if (rmi_fd.fn_number) {
			TS_LOG_INFO("Found F%02x\n", rmi_fd.fn_number);
			switch (rmi_fd.fn_number) {
			case SYNAPTICS_RMI4_F01:
				f01found = true;
				fwu->f01_fd.query_base_addr =
						rmi_fd.query_base_addr;
				fwu->f01_fd.ctrl_base_addr =
						rmi_fd.ctrl_base_addr;
				fwu->f01_fd.data_base_addr =
						rmi_fd.data_base_addr;
				fwu->f01_fd.cmd_base_addr =
						rmi_fd.cmd_base_addr;
				break;
			case SYNAPTICS_RMI4_F34:
				f34found = true;
				fwu->f34_fd.query_base_addr =
						rmi_fd.query_base_addr;
				fwu->f34_fd.ctrl_base_addr =
						rmi_fd.ctrl_base_addr;
				fwu->f34_fd.data_base_addr =
						rmi_fd.data_base_addr;

				break;
			}
		} else {
			break;
		}
	}

	if (!f01found || !f34found) {
		TS_LOG_ERR("Failed to find both F01 and F34\n");
		return -EINVAL;
	}

	return 0;
}

static int fwu_write_blocks(unsigned char *block_ptr, unsigned short block_cnt,
		unsigned char command)
{
	int retval;
	unsigned char block_offset[] = {0, 0};
	unsigned short block_num;

	TS_LOG_INFO("Start to update %s blocks\n",
			command == CMD_WRITE_CONFIG_BLOCK ?
			"config" : "firmware");
	block_offset[1] |= (fwu->config_area << 5);

	retval = fwu->fn_ptr->write(fwu->rmi4_data,
			fwu->f34_fd.data_base_addr + BLOCK_NUMBER_OFFSET,
			block_offset,
			sizeof(block_offset));
	if (retval < 0) {
		TS_LOG_ERR("Failed to write to block number registers\n");
		return retval;
	}

	TS_LOG_INFO("write block number registers ok,block_cnt=%d\n", block_cnt);
	for (block_num = 0; block_num < block_cnt; block_num++) {
		retval = fwu->fn_ptr->write(fwu->rmi4_data,
				fwu->f34_fd.data_base_addr + fwu->blk_data_off,
				block_ptr,
				fwu->block_size);
		if (retval < 0) {
			TS_LOG_ERR("Failed to write block data (block %d)\n", block_num);
			return retval;
		}

		retval = fwu_write_f34_command(command);
		if (retval < 0) {
			TS_LOG_ERR("Failed to write command for block %d\n", block_num);
			return retval;
		}

		retval = fwu_wait_for_idle(WRITE_WAIT_MS);
		if (retval < 0) {
			TS_LOG_ERR("Failed to wait for idle status (block %d)\n", block_num);
			return retval;
		}

		block_ptr += fwu->block_size;
	}

	return 0;
}

static int fwu_write_firmware(void)
{
	return fwu_write_blocks((unsigned char *)fwu->firmware_data,
		fwu->fw_block_count, CMD_WRITE_FW_BLOCK);
}

static int fwu_write_configuration(void)
{
	return fwu_write_blocks((unsigned char *)fwu->config_data,
		fwu->config_block_count, CMD_WRITE_CONFIG_BLOCK);
}

static int fwu_write_bootloader_id(void)
{
	int retval;

	TS_LOG_INFO("Write bootloader ID 0x%02X 0x%02X\n",
			fwu->bootloader_id[0],
			fwu->bootloader_id[1]);

	TS_LOG_INFO("bootloader id addr = 0x%04x\n", fwu->f34_fd.data_base_addr + fwu->blk_data_off);
	retval = fwu->fn_ptr->write(fwu->rmi4_data,
			fwu->f34_fd.data_base_addr + fwu->blk_data_off,
			fwu->bootloader_id,
			sizeof(fwu->bootloader_id));
	if (retval < 0) {
		TS_LOG_ERR("Failed to write bootloader ID\n");
		return retval;
	}

	return 0;
}

static int fwu_enter_flash_prog(void)
{
	int retval;
	struct f01_device_status f01_device_status;
	struct f01_device_control f01_device_control;

	TS_LOG_INFO("Enter bootloader mode\n");

	retval = fwu_write_bootloader_id();
	if (retval < 0)
		return retval;

	TS_LOG_INFO("fwu_write_f34_command\n");
	retval = fwu_write_f34_command(CMD_ENABLE_FLASH_PROG);
	if (retval < 0)
		return retval;

	msleep(500);
	TS_LOG_INFO("fwu_wait_for_idle 500\n");

	retval = fwu_wait_for_idle(ENABLE_WAIT_MS);
	if (retval < 0)
		return retval;

	TS_LOG_DEBUG("fwu->command = 0x%02x, fwu->flash_status = 0x%02x\n", fwu->command, fwu->flash_status);

	if (!fwu->program_enabled) {
		TS_LOG_ERR("Program enabled bit not set : %d\n", fwu->program_enabled);
		return -EINVAL;
	}

	retval = fwu_scan_pdt();
	if (retval < 0)
		return retval;

	retval = fwu_read_f01_device_status(&f01_device_status);
	if (retval < 0)
		return retval;

	if (!f01_device_status.flash_prog) {
		TS_LOG_ERR("Not in flash prog mode : %d\n", f01_device_status.flash_prog);
		//return -EINVAL;
	}

	retval = fwu_read_f34_queries();
	if (retval < 0)
		return retval;

	retval = fwu->fn_ptr->read(fwu->rmi4_data,
			fwu->f01_fd.ctrl_base_addr,
			f01_device_control.data,
			sizeof(f01_device_control.data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read F01 device control\n");
		return retval;
	}

	f01_device_control.nosleep = true;
	f01_device_control.sleep_mode = SLEEP_MODE_NORMAL;

	retval = fwu->fn_ptr->write(fwu->rmi4_data,
			fwu->f01_fd.ctrl_base_addr,
			f01_device_control.data,
			sizeof(f01_device_control.data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to write F01 device control\n");
		return retval;
	}

	return retval;
}

static int fwu_do_reflash(void)
{
	int retval;

	retval = fwu_enter_flash_prog();
	if (retval < 0) {
		TS_LOG_INFO("fwu_enter_flash_prog fail\n");
		#if defined (CONFIG_HUAWEI_DSM)
		g_ts_data.dsm_info.constraints_UPDATE_status = fwu_enter_flash_prog_fail;
		#endif
		return retval;
	}

	TS_LOG_INFO("Entered flash prog mode\n");

	retval = fwu_write_bootloader_id();
	if (retval < 0) {
		TS_LOG_INFO("fwu_write_bootloader_id fail\n");
		#if defined (CONFIG_HUAWEI_DSM)
		g_ts_data.dsm_info.constraints_UPDATE_status = fwu_write_bootloader_id_fail;
		#endif
		return retval;
	}

	TS_LOG_INFO("Bootloader ID written done\n");

	retval = fwu_write_f34_command(CMD_ERASE_ALL);
	if (retval < 0) {
		TS_LOG_INFO("fwu_write_f34_command fail\n");
		#if defined (CONFIG_HUAWEI_DSM)
		g_ts_data.dsm_info.constraints_UPDATE_status = fwu_write_f34_command_fail;
		#endif
		return retval;
	}

	TS_LOG_INFO("fwu_write_f34_command done\n");

	msleep(2000);

	retval = fwu_wait_for_idle(ERASE_WAIT_MS);
	if (retval < 0) {
		TS_LOG_INFO("fwu_wait_for_idle fail\n");
		#if defined (CONFIG_HUAWEI_DSM)
		g_ts_data.dsm_info.constraints_UPDATE_status = fwu_wait_for_idle_fail;
		#endif
		return retval;
	}

	TS_LOG_INFO("Idle status detected\n");

	if (fwu->firmware_data) {
		retval = fwu_write_firmware();
		if (retval < 0) {
			TS_LOG_INFO("fwu_write_firmware fail\n");
			#if defined (CONFIG_HUAWEI_DSM)
			g_ts_data.dsm_info.constraints_UPDATE_status = fwu_write_firmware_fail;
			#endif
			return retval;
		}
		TS_LOG_INFO("Firmware programmed\n");
	}

	if (fwu->config_data) {
		retval = fwu_write_configuration();
		if (retval < 0) {
			TS_LOG_INFO("fwu_write_configuration fail\n");
			#if defined (CONFIG_HUAWEI_DSM)
			g_ts_data.dsm_info.constraints_UPDATE_status = fwu_write_configuration_fail;
			#endif
			return retval;
		}
		TS_LOG_INFO("Configuration programmed\n");
	}

	TS_LOG_INFO("fwu_do_reflash suc\n");

	return retval;
}

int synaptics_fw_update(void)
{
	int retval = 0;
	struct f01_device_status f01_device_status;

	TS_LOG_INFO("synaptics_fw_update called\n");
	retval = fwu_do_reflash();
	if (retval < 0) {
		TS_LOG_ERR("Failed to do reflash\n");
	}
	/* reset device */
	retval = fwu_reset_device();
	if (retval < 0) {
		TS_LOG_ERR("Failed to reset device\n");
		goto exit;
	}

	/* check device status */
	retval = fwu_read_f01_device_status(&f01_device_status);
	if (retval < 0)
		goto exit;

	TS_LOG_INFO("Device is in %s mode\n", f01_device_status.flash_prog == 1 ? "bootloader" : "UI");

	if (f01_device_status.flash_prog) {
		TS_LOG_INFO("Device is in flash prog mode, Flash status 0x%02X\n", f01_device_status.status_code);
		retval = 0;
		goto exit;
	}

	TS_LOG_INFO("End of reflash process\n");
exit:
	return retval;
}

static int file_open_firmware(u8 **buf)
{
	struct inode *inode = NULL;
	mm_segment_t oldfs;
	uint32_t	length;
	struct file *filp;
	const char filename[]="/sdcard/update/synaptics.img";
	const char filename_bak[]="/cache/synaptics.img";
	/* open file */
	oldfs = get_fs();
	set_fs(KERNEL_DS);
	filp = filp_open(filename, O_RDONLY, S_IRUSR);
	if (IS_ERR(filp)) {

		printk("%s: file %s filp_open error,try %s\n", __FUNCTION__,filename,filename_bak);
		filp = filp_open(filename_bak, O_RDONLY, S_IRUSR);
		if (IS_ERR(filp)) {
			printk("%s: file %s filp_open error\n", __FUNCTION__,filename_bak);
			set_fs(oldfs);
			return -1;
		}
	}

	if (!(filp)->f_op) {
		printk("%s: File Operation Method Error\n", __FUNCTION__);
		filp_close(filp, NULL);
		set_fs(oldfs);
		return -1;
	}

	inode = (filp)->f_path.dentry->d_inode;
	if (!inode) {
		printk("%s: Get inode from filp failed\n", __FUNCTION__);
		filp_close(filp, NULL);
		set_fs(oldfs);
		return -1;
	}

	/* file's size */
	length = i_size_read(inode->i_mapping->host);
	if (!( length > 0 && length < FIRMWARE_LEN )) {
		printk("file size error\n");
		filp_close((filp), NULL);
		set_fs(oldfs);
		return -1;
	}

	/* allocation buff size */
	*buf = vmalloc(length+(length%2));		/* buf size if even */
	if (!(*buf)) {
		printk("alloctation memory failed\n");
		filp_close((filp), NULL);
		set_fs(oldfs);
		return -1;
	}

	/* read data */
	if ((filp)->f_op->read((filp), (*buf), length, &(filp)->f_pos) != length) {
		printk("%s: file read error\n", __FUNCTION__);
		filp_close((filp), NULL);
		set_fs(oldfs);
		return -1;
	}

	set_fs(oldfs);
	filp_close((filp), NULL);
	return 0;
}

static int synaptics_read_project_id(void)
{
	unsigned char *project_id = fwu->rmi4_data->rmi4_mod_info.project_id_string;

	memcpy(project_id, fwu->rmi4_data->rmi4_mod_info.product_id_string, SYNAPTICS_RMI4_PROJECT_ID_SIZE);
	project_id[SYNAPTICS_RMI4_PROJECT_ID_SIZE] = 0;

	TS_LOG_INFO( "%s: project id is: %s\n",__func__, project_id);

	return NO_ERR;
}

/*
 *   init the resource for fw update.
*/
int synaptics_fw_data_init(struct synaptics_rmi4_data *rmi4_data)
{
	int retval = 0;
	struct pdt_properties pdt_props;
	TS_LOG_INFO("synaptics_rmi4_fwu_init called\n");

	if (NULL == fwu) {
		fwu = kzalloc(sizeof(*fwu), GFP_KERNEL);
		if (!fwu) {
			TS_LOG_ERR("Failed to alloc mem for fwu\n");
			retval = -ENOMEM;
			goto exit;
		}
	}

	if (NULL == fwu->fn_ptr) {
		fwu->fn_ptr = kzalloc(sizeof(*(fwu->fn_ptr)), GFP_KERNEL);
		if (!fwu->fn_ptr) {
			TS_LOG_ERR("Failed to alloc mem for fn_ptr\n");
			retval = -ENOMEM;
			goto exit;
		}
	}

	fwu->rmi4_data = rmi4_data;
	fwu->fn_ptr->read = rmi4_data->i2c_read;
	fwu->fn_ptr->write = rmi4_data->i2c_write;

	retval = fwu->fn_ptr->read(rmi4_data,
			PDT_PROPS,
			pdt_props.data,
			sizeof(pdt_props.data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read PDT properties, assuming 0x00\n");
	} else if (pdt_props.has_bsr) {
		TS_LOG_ERR("Reflash for LTS not currently supported\n");
		goto exit;
	}

	retval = fwu_scan_pdt();
	if (retval < 0){
		TS_LOG_ERR("Failed to scan pdt\n");
		goto exit;
	}

	fwu->productinfo1 = rmi4_data->rmi4_mod_info.product_info[0];
	fwu->productinfo2 = rmi4_data->rmi4_mod_info.product_info[1];

	memcpy(fwu->product_id, rmi4_data->rmi4_mod_info.product_id_string, SYNAPTICS_RMI4_PRODUCT_ID_SIZE);
	fwu->product_id[SYNAPTICS_RMI4_PRODUCT_ID_SIZE] = 0;

	TS_LOG_INFO("F01 product info: 0x%04x 0x%04x, F01 product ID: %s\n", fwu->productinfo1, fwu->productinfo2, fwu->product_id);

	retval = fwu_read_f34_queries();
	if (retval < 0){
		TS_LOG_ERR("Failed to read f34 queries\n");
		goto exit;
	}

	retval = synaptics_read_project_id();
	if (retval < 0){
		TS_LOG_ERR("Failed to read project id\n");
		goto exit;
	}

	fwu->initialized = true;
	fwu->force_update = FORCE_UPDATE;

	TS_LOG_INFO("synaptics_fw_data_init done\n");
	return 0;

exit:
	return retval;
}

/*    get the firmware data form boot.img
 */
int synaptics_get_fw_data_boot(char *file_name, struct touch_settings *synaptics_sett_param_regs)
{
	int retval;
	size_t file_name_size = strlen(file_name)+strlen(synaptics_sett_param_regs->module_name);
	char firmware_name[RMI_PRODUCT_ID_LENGTH + file_name_size +1];
	struct device *dev = &fwu->rmi4_data->synaptics_dev->dev;

	snprintf(firmware_name, sizeof(firmware_name), "ts/%s_%s.img", file_name,synaptics_sett_param_regs->module_name);
	firmware_name[RMI_PRODUCT_ID_LENGTH + file_name_size] = 0;

	TS_LOG_INFO("file_name size = %ld, Requesting firmware image %s\n",
		file_name_size, firmware_name);

	retval = request_firmware(&fwu->fw_entry_boot, firmware_name, dev);
	if (retval != 0) {
		TS_LOG_ERR("Firmware image %s not available\n", firmware_name);
		return retval;
	}

	if (fwu->fw_entry_boot == NULL) {
		TS_LOG_ERR("fw is null\n");
		return -EINVAL;
	}

	fwu->fw_image = fwu->fw_entry_boot->data;

	TS_LOG_INFO("Firmware image size = %ld\n", fwu->fw_entry_boot->size);
	return NO_ERR;
}

/*    get the firmware data form file in sd card.
 */
int synaptics_get_fw_data_sd(void)
{
	int retval;

	TS_LOG_INFO("synaptics_get_fw_data_sd called\n");

	retval = file_open_firmware(&(fwu->fw_entry_sd));
	if (retval != 0) {
		TS_LOG_ERR("file_open_firmware error, code = %d\n", retval);
		return retval;
	}

	fwu->fw_image = fwu->fw_entry_sd;

	TS_LOG_INFO("synaptics_get_fw_data_sd done\n");
	return NO_ERR;
}

bool synaptics_check_fw_version(void)
{
	enum flash_area flash_area;
	struct image_header_data header;
	const unsigned char *fw_image = fwu->fw_image;

	parse_header(&header, fw_image);

	if (header.firmware_size)
		fwu->firmware_data = fw_image + FW_IMAGE_OFFSET;
	if (header.config_size) {
		fwu->config_data = fw_image + FW_IMAGE_OFFSET + header.firmware_size;
	}

	flash_area = fwu_go_nogo(&header);
	if (flash_area == UI_FIRMWARE) {
		TS_LOG_INFO("update fw\n");
		return true;
	} else {
		TS_LOG_INFO("no need to update fw\n");
		return false;
	}
}

void synaptics_fw_data_release(void)
{
	TS_LOG_INFO("release fw resource\n");

	if (fwu && fwu->fn_ptr) {
		kfree(fwu->fn_ptr);
		fwu->fn_ptr = NULL;
	}
	if (fwu && fwu->fw_entry_sd) {
		vfree(fwu->fw_entry_sd);
		fwu->fw_entry_sd = NULL;
	}
	if (fwu && fwu->fw_entry_boot) {
		release_firmware(fwu->fw_entry_boot);
		fwu->fw_entry_boot = NULL;
	}
	if (fwu) {
		kfree(fwu);
		fwu = NULL;
	}
}

