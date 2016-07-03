#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <../../huawei_touchscreen_chips.h>
#include <linux/regulator/consumer.h>
#include <linux/hisi/hi6xxx-lcd_type.h>
#include <huawei_platform/log/log_jank.h>
#include "../../huawei_touchscreen_algo.h"
#include "atmel.h"
extern struct ts_data g_ts_data;

#define MXT_FW_CHG_TIMEOUT 5000
#define MXT_FW_RESET_TIME 250
#define CONFIG_MXT_UPDATE_BY_OBJECT

/*
 *Function for enabling T37 diagnostic mode through T6.
 *
 *t37 is used to store diagnostic data which can be references, delta and so on. Which kind of data is stored is controled by byte 5 of t6.
 *this function fist set t6 byte 5 and then read t37 for the data wanted.
 *
 */
int mxt_diagnostic_command(struct mxt_data *data, u8 cmd, u8 page, u8 index, u8 num, char * buf, int interval, int interval_c)
{
	u16 reg;
	s8 command_register[2];
	s8 current_page,page_cmd;
	int ret;
	int timeout_counter,retry;

	long unsigned int time_start = jiffies;

	reg = data->T37_address;
	ret = __mxt_read_reg(data, reg, sizeof(command_register), &command_register[0]);
	if (ret) {
		TS_LOG_ERR("T37 read offset 0 failed %d!\n",ret);
		return -EIO;
	}

#define T37_COMMAND_RESEND_INDEX  2
	if ((u8)command_register[0] != cmd
		&& (page == 0 && index < T37_COMMAND_RESEND_INDEX)) {
		TS_LOG_INFO("%s, cmd = %d, command_register[0] = %d ,  page = %d , index = %d\n", __func__, cmd,  command_register[0], page, index);
		ret = mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC, cmd, 0);
		if (ret) {
			TS_LOG_ERR("T6 Command DIAGNOSTIC cmd 0x%x failed %d!\n",cmd,ret);
			return -EIO;
		}
		current_page = 0;
	} else {
		current_page = command_register[1];
		if (abs((s8)current_page - (s8)page) > (s8)page) {// far away with dis page
			ret = mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC, cmd, 0);
			if  (ret) {
				TS_LOG_ERR("T6 Command DIAGNOSTIC cmd 0x%x failed %d!\n",cmd,ret);
				return -EIO;
			}
			current_page = 0;
		}
	}

	//wait command
	timeout_counter = 0;
	do {	
		msleep(interval);
		reg = data->T37_address;
		ret = __mxt_read_reg(data, reg, sizeof(command_register), &command_register[0]);
		if (ret) {
			TS_LOG_ERR("T37 read offset 0 failed %d!\n",ret);
			return -EIO;
		}

		if ((u8)command_register[0] == cmd)
			break;

		if (!interval_c)
			return -EAGAIN;

	} while (timeout_counter++ <= interval_c);

	if (timeout_counter > interval_c) {
		TS_LOG_ERR(
			"T37 wait cmd %d page %d current page %d timeout, T37 buf(%d %d) ##1\n",
			cmd,page,current_page,(u8)command_register[0],command_register[1]);
		return -EBUSY;
	}

	//current_page = command_register[1];
	retry = 0;
	while (current_page != page) {

		if (current_page > page) {
			page_cmd = MXT_T6_DEBUG_PAGEDOWN;
			current_page--;
		} else {
			page_cmd = MXT_T6_DEBUG_PAGEUP;
			current_page++;
		}

		time_start = jiffies;

		ret = mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC,page_cmd, 0);
		if (ret) {
			TS_LOG_ERR("T6 Command DIAGNOSTIC page %d to page %d failed %d!\n",current_page,page,ret);
			return -EIO;
		}

		if (!interval_c)
			return -EAGAIN;

		//fix me: here need wait every cycle?
		timeout_counter = 0;
		do {
			reg = data->T37_address;
			ret = __mxt_read_reg(data, reg,
						sizeof(command_register), &command_register[0]);
			if (ret) {
				TS_LOG_ERR("T37 read offset 0 failed %d!\n",ret);
				return -EIO;
			}
			if ((u8)command_register[0] != cmd) {
				break;
			}
			if (current_page == command_register[1])
				break;

			msleep(interval);
		} while (timeout_counter++ <= interval_c);

		if (timeout_counter > interval_c) {
			if (retry++ > interval_c) {
				TS_LOG_ERR(
					"T37 wait cmd %d page %d current page %d timeout, T37 buf(%d %d) page_cmd %d retry %d ##2\n",
					cmd,page,current_page,(u8)command_register[0],command_register[1],page_cmd,retry);
				return -EBUSY;
			}
		}
		if ((u8)command_register[0] != cmd) {
			TS_LOG_ERR(
				"T37 wait cmd %d page %d current page %d timeout, T37 buf(%d %d) ##3\n",
				cmd,page,current_page,(u8)command_register[0],command_register[1]);
			return -EBUSY;
		}
		current_page = command_register[1];

		TS_LOG_ERR( "T37 page command ticks %lu\n",jiffies - time_start);
	}

	if (buf) {
		ret = __mxt_read_reg(data, data->T37_address + sizeof(command_register) + index,
				num, buf);
		if (ret) {
			TS_LOG_ERR(
				"Failed to read T37 val at page %d.%d (%d)\n", page, index, ret);
			return -EIO;
		}

		//check the command again
		ret = __mxt_read_reg(data, reg, sizeof(command_register), &command_register[0]);
		if (ret) {
			TS_LOG_ERR("T37 read offset 0 failed %d!\n",ret);
			return -EIO;
		} 

		if ((u8)command_register[0] != cmd || command_register[1] != page) {
			TS_LOG_ERR("%s, T37 page changed (%d,%d) -> (%d,%d)\n",
					__func__,
					cmd,
					page,
					(u8)command_register[0],
					command_register[1]);
			return -EIO;
		}
		TS_LOG_DEBUG("%s, T37 cmd %d page %d, T37 buf(%03d %03d %03d %03d)\n",
				__func__, command_register[0], command_register[1], buf[0], buf[1], buf[2], buf[3]);
	}

	return 0;
}

/*
 *Function for getting t68 product data store.
 *
 *the pds data is read out through t37.
 *
 */
int mxt_pds_get_data(struct mxt_data *data, struct pds_code *code)
{
	int ret = -EINVAL;

	int i = 0;
	int retry = 3;

	if (!code)
		return ret;

#ifdef ROI
	gMxtT6Cmd58Flag = MXT_T6_CMD58_OFF;
#endif
	do {
		ret = mxt_diagnostic_command(data, MXT_T6_DEBUG_PID, 0, 0, MISC_PDS_HEAD_LEN, (char *)&code->head[0], 10, 5);
		if (ret == 0)  {
			TS_LOG_DEBUG("Found PID head %02x %02x.\n",code->head[0],code->head[1]);
			if (code->head[0] == PID_MAGIC_WORD0 && code->head[1] == PID_MAGIC_WORD1) {
				ret = mxt_diagnostic_command(data, MXT_T6_DEBUG_PID, 0, MISC_PDS_HEAD_LEN, MISC_PDS_DATA_LEN, (char *)&code->id[0], 10, 5);
				if (ret == 0)
					break;
			}
		}
		msleep(10);
	}while(--retry);
#ifdef ROI
	gMxtT6Cmd58Flag = MXT_T6_CMD58_ON;
#endif

	if(!retry) {
		ret = -ENODATA;
	}

	if (ret == 0) {
		TS_LOG_INFO("Found PDS Data %c%c%c%c%c%c%c%c%c\n",
			code->id[0],code->id[1],code->id[2],code->id[3],code->id[4],
			code->id[5],code->id[6],code->id[7],code->id[8]);
			code->id[MISC_PDS_DATA_LEN-1] = '\0';
			TS_LOG_INFO("%s\n", code->id);
        }else{
		TS_LOG_ERR("Read PDS Data failed %d\n",ret);
		memset(code, 0, sizeof(struct pds_code));
	}

	for (i = 0; i < MISC_PDS_DATA_LEN; i++) {
		if (code->id[i] < 32 || code->id[i] > 126) {
			code->id[i] = 0;
			break;
		}
	}

	if (i == 0) {
		strncpy(code->id, "NULL", MISC_PDS_DATA_LEN);
	}

	return ret;
}

static inline int mxt_obj_instances(const struct mxt_object *obj)
{
	return obj->instances_minus_one + 1;
}

static inline int mxt_obj_size(const struct mxt_object *obj)
{
	return obj->size_minus_one + 1;
}

static void mxt_update_crc(struct mxt_data *data, u8 cmd, u8 value)
{
	/* on failure, CRC is set to 0 and config will always be downloaded */
	data->config_crc = 0;

	mxt_t6_command(data, cmd, value, true);

	/* Wait for crc message. On failure, CRC is set to 0 and config will
	 * always be downloaded */
	process_messages(data, MXT_FW_CHG_TIMEOUT);
}

/*
 * mxt_check_reg_init - download configuration to chip
 *
 * Atmel Raw Config File Format
 *
 * The first four lines of the raw config file contain:
 *  1) Version
 *  2) Chip ID Information (first 7 bytes of device memory)
 *  3) Chip Information Block 24-bit CRC Checksum
 *  4) Chip Configuration 24-bit CRC Checksum
 *
 * The rest of the file consists of one line per object instance:
 *	<TYPE> <INSTANCE> <SIZE> <CONTENTS>
 *
 *	<TYPE> - 2-byte object type as hex
 *	<INSTANCE> - 2-byte object instance number as hex
 *	<SIZE> - 2-byte object size as hex
 *	<CONTENTS> - array of <SIZE> 1-byte hex values
 */
static int mxt_check_reg_init(struct mxt_data *data)
{
	struct mxt_info cfg_info;
	struct mxt_object *object;
	const struct firmware *cfg = NULL;
	int ret;
	int offset;
	int data_pos;
	int byte_offset;
	int i;
	int cfg_start_ofs;
	u32 info_crc, config_crc, calculated_crc;
	u8 *config_mem;
	size_t config_mem_size;
	unsigned int type, instance, size;
	u8 val;
	u16 reg;
#if defined(CONFIG_MXT_UPDATE_BY_OBJECT)
	u8 *object_mem,*object_offset;
#endif

	if (!data->cfg_name) {
		TS_LOG_INFO("Skipping cfg download\n");
		return 0;
	}

	ret = request_firmware(&cfg, data->cfg_name, &data->ts_dev->dev);
	if (ret < 0) {
		TS_LOG_ERR("Failure to request config file %s\n",
			data->cfg_name);			
		return 0;
	}

	mxt_update_crc(data, MXT_COMMAND_REPORTALL, 1);

	if (strncmp(cfg->data, MXT_CFG_MAGIC, strlen(MXT_CFG_MAGIC))) {
		TS_LOG_ERR("Unrecognised config file\n");
		ret = -EINVAL;
		goto release;
	}

	data_pos = strlen(MXT_CFG_MAGIC);

	/* Load information block and check */
	for (i = 0; i < sizeof(struct mxt_info); i++) {
		ret = sscanf(cfg->data + data_pos, "%hhx%n",
				 (unsigned char *)&cfg_info + i,
				 &offset);
		if (ret != 1) {
			TS_LOG_ERR("Bad format\n");
			ret = -EINVAL;
			goto release;
		}

		data_pos += offset;
	}

	if (cfg_info.family_id != data->info->family_id) {
		TS_LOG_ERR("Family ID mismatch!\n");
		ret = -EINVAL;
		goto release;
	}

	if (cfg_info.variant_id != data->info->variant_id) {
		TS_LOG_ERR("Variant ID mismatch!\n");
		ret = -EINVAL;
		goto release;
	}

	/* Read CRCs */
	ret = sscanf(cfg->data + data_pos, "%x%n", &info_crc, &offset);
	if (ret != 1) {
		TS_LOG_ERR("Bad format: failed to parse Info CRC\n");
		ret = -EINVAL;
		goto release;
	}
	data_pos += offset;

	ret = sscanf(cfg->data + data_pos, "%x%n", &config_crc, &offset);
	if (ret != 1) {
		TS_LOG_ERR("Bad format: failed to parse Config CRC\n");
		ret = -EINVAL;
		goto release;
	}
	data_pos += offset;

	TS_LOG_INFO("File configure CRC: 0x%06X, Chip configure CRC: 0x%06X\n", config_crc, data->config_crc);
	/* The Info Block CRC is calculated over mxt_info and the object table
	 * If it does not match then we are trying to load the configuration
	 * from a different chip or firmware version, so the configuration CRC
	 * is invalid anyway. */
	if (info_crc == data->info_crc) {
		if (config_crc == 0 || data->config_crc == 0) {
			TS_LOG_DEBUG("CRC zero, attempting to apply config\n");
		} else if (config_crc == data->config_crc) {
			TS_LOG_DEBUG("Config CRC 0x%06X: OK\n",
				 data->config_crc);
#if defined(CONFIG_MXT_CAL_TRIGGER_CAL_WHEN_CFG_MATCH)
		mxt_t6_command(data, MXT_COMMAND_CALIBRATE, 1, false);
#endif
			ret = 0;
			goto release;
		} else {
			TS_LOG_DEBUG("Config CRC 0x%06X: does not match file 0x%06X\n",
				 data->config_crc, config_crc);
		}
	} else {
		TS_LOG_ERR(
			 "Warning: Info CRC error - device=0x%06X file=0x%06X\n",
			data->info_crc, info_crc);
	}

	/* Malloc memory to store configuration */
	cfg_start_ofs = MXT_OBJECT_START
		+ data->info->object_num * sizeof(struct mxt_object)
		+ MXT_INFO_CHECKSUM_SIZE;
	config_mem_size = data->mem_size - cfg_start_ofs;
#if defined(CONFIG_MXT_UPDATE_BY_OBJECT)
	config_mem_size <<= 1;
#endif
	config_mem = kzalloc(config_mem_size, GFP_KERNEL);
	if (!config_mem) {
		TS_LOG_ERR("Failed to allocate memory\n");
		ret = -ENOMEM;
		goto release;
	}
#if defined(CONFIG_MXT_UPDATE_BY_OBJECT)
	object_mem = config_mem + (config_mem_size>>1);
#endif

	while (data_pos < cfg->size - 16) {
		/* Read type, instance, length */
		ret = sscanf(cfg->data + data_pos, "%x %x %x%n",
				 &type, &instance, &size, &offset);
#if defined(CONFIG_MXT_UPDATE_BY_OBJECT)
		object_offset = object_mem;
#endif
		if (ret == 0) {
			/* EOF */
			break;
		} else if (ret != 3) {
			TS_LOG_ERR("Bad format: failed to parse object\n");
			/*ret = -EINVAL;
			goto release_mem;*/
			break;
		}
		data_pos += offset;

		object = mxt_get_object(data, type);
		if (!object) {
			/* Skip object */
			for (i = 0; i < size; i++) {
				ret = sscanf(cfg->data + data_pos, "%hhx%n",
						 &val,
						 &offset);
				data_pos += offset;
			}
			continue;
		}

		if (size > mxt_obj_size(object)) {
			/* Either we are in fallback mode due to wrong
			 * config or config from a later fw version,
			 * or the file is corrupt or hand-edited */
			TS_LOG_ERR("Discarding %ud byte(s) in T%d\n",
				 size - mxt_obj_size(object), type);
		} else if (mxt_obj_size(object) > size) {
			/* If firmware is upgraded, new bytes may be added to
			 * end of objects. It is generally forward compatible
			 * to zero these bytes - previous behaviour will be
			 * retained. However this does invalidate the CRC and
			 * will force fallback mode until the configuration is
			 * updated. We warn here but do nothing else - the
			 * malloc has zeroed the entire configuration. */
			TS_LOG_ERR("Zeroing %d byte(s) in T%d\n",
				 mxt_obj_size(object) - size, type);
		}

		if (instance >= mxt_obj_instances(object)) {
			TS_LOG_ERR("Object instances exceeded!\n");
			ret = -EINVAL;
			goto release_mem;
		}

		reg = object->start_address + mxt_obj_size(object) * instance;

		for (i = 0; i < size; i++) {
			ret = sscanf(cfg->data + data_pos, "%hhx%n",
					 &val,
					 &offset);
			if (ret != 1) {
				TS_LOG_ERR("Bad format in T%d\n", type);
				ret = -EINVAL;
				goto release_mem;
			}
			data_pos += offset;

			if (i > mxt_obj_size(object))
				continue;

			byte_offset = reg + i - cfg_start_ofs;

			if ((byte_offset >= 0)
				&& (byte_offset <= config_mem_size)) {
				*(config_mem + byte_offset) = val;
		#if defined(CONFIG_MXT_UPDATE_BY_OBJECT)
				*(object_offset++)=val ;
		#endif
			} else {
				TS_LOG_ERR("Bad object: reg:%d, T%d, ofs=%d\n",
					reg, object->type, byte_offset);
				ret = -EINVAL;
				goto release_mem;
			}
		}
		
#if defined(CONFIG_MXT_UPDATE_BY_OBJECT)
		ret = __mxt_write_reg(data,reg,size,object_mem);
		if(ret!=0){
			TS_LOG_ERR("write object[%d] error\n",object->type);
			goto release_mem ;
		}
#endif
	}

	/* calculate crc of the received configs (not the raw config file) */
	if (data->T7_address < cfg_start_ofs) {
		TS_LOG_ERR("Bad T7 address, T7addr = %x, config offset %x\n",
			data->T7_address, cfg_start_ofs);
		ret = 0;
		goto release_mem;
	}

	calculated_crc = mxt_calculate_crc(config_mem,
						data->T7_address - cfg_start_ofs,
						config_mem_size);

	if (config_crc > 0 && (config_crc != calculated_crc))
		TS_LOG_DEBUG("Config CRC different, calculated=%06X, file=%06X\n",
			 calculated_crc, config_crc);

	/* Write configuration as blocks */
	byte_offset = 0;

#if defined(CONFIG_MXT_UPDATE_BY_OBJECT)
	while (byte_offset < config_mem_size) {
		size = config_mem_size - byte_offset;

		if (size > MXT_MAX_BLOCK_WRITE)
			size = MXT_MAX_BLOCK_WRITE;

		ret = __mxt_write_reg(data,
					  cfg_start_ofs + byte_offset,
					  size, config_mem + byte_offset);
		if (ret != 0) {
			TS_LOG_ERR("Config write error, ret=%d\n", ret);
			goto release_mem;
		}

		byte_offset += size;
	}
#endif

	mxt_update_crc(data, MXT_COMMAND_BACKUPNV, MXT_BACKUP_VALUE);

	mxt_soft_reset(data);
	
	TS_LOG_INFO("Config written\n");

	/* T7 config may have changed */
	mxt_init_t7_power_cfg(data);

release_mem:
	kfree(config_mem);
release:
	release_firmware(cfg);
	return ret;
}

int mxt_update_cfg(struct mxt_data *data)
{
	int ret;
	TS_LOG_INFO("mxt_update_cfg\n");

	if (!data)
		return -ENODEV;

	if (data->in_bootloader) {
		TS_LOG_ERR("Not in appmode\n");
		return -EINVAL;
	}

	if (!data->object_table) {
		TS_LOG_ERR("Not initialized\n");
		return -EINVAL;
	}

	mxt_update_config_file_name(data, &data->cfg_name);

	data->enable_reporting = false;
	//there wait for a while after report disable

	mxt_free_input_device(data);

	mxt_check_reg_init(data);

	ret = mxt_configure_objects(data);

	//mxt_acquire_irq(data);
out:
	return ret;
}

/*
 * mxt_check_firmware_version - check if firmware need updating.
 *
 * File firmware version is read out from CONFIG file, and then it is compared to the current firmware version.
 */
int mxt_check_firmware_version(struct mxt_data *data)
{
	int error = 0;
	const struct firmware *cfg = NULL;
	int data_pos, offset;
	int i;
	struct mxt_info cfg_info;

	if (data->info == NULL) {
		TS_LOG_ERR("%s:data->info = %ld\n",__func__,PTR_ERR(data->info));
		return 0;
	}
	mxt_update_config_file_name(data, &data->cfg_name);

	error = request_firmware(&cfg, data->cfg_name, &data->ts_dev->dev);
	if (error < 0) {
		TS_LOG_ERR("Fail to get config file %s\n",data->cfg_name);
		return -EINVAL;
	}

	if (strncmp(cfg->data, MXT_CFG_MAGIC, strlen(MXT_CFG_MAGIC))) {
		TS_LOG_ERR("Unrecognised config file\n");
		error = -EINVAL;
		goto release;
	}
	data_pos = strlen(MXT_CFG_MAGIC);
	/* Load information block and check */
	for (i = 0; i < sizeof(struct mxt_info); i++) {
		error = sscanf(cfg->data + data_pos, "%hhx%n", (unsigned char *)&cfg_info + i, &offset);
		if (error != 1) {
			TS_LOG_ERR("Bad format\n");
	 		error = -EINVAL;
	 		goto release;
		}
		data_pos += offset;
	}
	TS_LOG_INFO("File firmware version: %02X.%02X\n", cfg_info.version,cfg_info.build);
	TS_LOG_INFO("Chip firmware version: %02X.%02X\n", data->info->version,data->info->build);
	/*family_id, variant_id maxtouch chiptype*/
	if (cfg_info.family_id != data->info->family_id ||cfg_info.variant_id != data->info->variant_id) {
		TS_LOG_INFO("Firmware is not for this maxtouch chip. Will try update from %d.%d to %d.%d\n",
			data->info->family_id,data->info->variant_id,cfg_info.family_id,cfg_info.variant_id);
		error = 0;
		goto release;
	}

	/*version,build firmware version*/
	if (cfg_info.version != data->info->version || cfg_info.build != data->info->build) {
		TS_LOG_INFO("Firmware need updating from %d.%d to %d.%d\n",
			data->info->version,data->info->build,cfg_info.version,cfg_info.build);
		error = 0;
		goto release;
	}

	TS_LOG_INFO("Firmware does not need updating, firmware version and chiptype is the same:family_id:%d, variant_id:%d, version:%d, build:%d\n", 
		data->info->family_id,  data->info->variant_id, data->info->version, data->info->build);
	error = -EINVAL;

release:
	release_firmware(cfg);
	return error;
}

extern int update_sd_mode;
void mxt_update_fw_file_name(struct mxt_data *data, char *file_name)
{
	int offset;

	if (update_sd_mode == 0) {
		/* Find file by product name. */
		offset = snprintf(file_name, PAGE_SIZE, "ts/atmel/");

		offset += snprintf(file_name+offset, PAGE_SIZE-offset, g_ts_data.product_name);

		snprintf(file_name+offset, PAGE_SIZE-offset, "_firmware.fw");
	} else {
		/*
		 * Relative path to /vendor/firmware/
		 * (/vendor is a symbolic link to /system/vendor/)
		 */
		offset = snprintf(file_name, PAGE_SIZE, "../../../sdcard/update/firmware.fw");
	}

	TS_LOG_INFO("update fw file name: %s\n", file_name);
}

void mxt_update_config_file_name(struct mxt_data *data, char *file_name)
{
	int offset;

	if (update_sd_mode == 0) {
		/* Find file by product name. */
		offset = snprintf(file_name, PAGE_SIZE, "ts/atmel/");
		if (data->description[0] != '\0') {
			offset += snprintf(file_name+offset, PAGE_SIZE-offset, data->description);
		} else {
			offset += snprintf(file_name+offset, PAGE_SIZE-offset, g_ts_data.product_name);
		}
		snprintf(file_name+offset, PAGE_SIZE-offset, "_config.raw");
	} else {
		offset = snprintf(file_name, PAGE_SIZE, "../../../sdcard/update/config.raw");
	}

	TS_LOG_INFO("update config file name: %s\n", file_name);
}

static int mxt_check_firmware_format(struct mxt_data *data,
					 const struct firmware *fw)
{
	unsigned int pos = 0;
	char c;

	while (pos < fw->size) {
		c = *(fw->data + pos);

		if (c < '0' || (c > '9' && c < 'A') || c > 'F')
			return 0;

		pos++;
	}

	/* To convert file try
	 * xxd -r -p mXTXXX__APP_VX-X-XX.enc > maxtouch.fw */
	TS_LOG_ERR("Aborting: firmware file must be in binary format\n");

	return -1;
}

static u8 mxt_get_bootloader_version(struct mxt_data *data, u8 val)
{
	
	u8 buf[3];

	if (val & MXT_BOOT_EXTENDED_ID) {
		if (mxt_bootloader_read(data, &buf[0], 3) != 0) {
			TS_LOG_ERR("%s: i2c failure\n", __func__);
			return -EIO;
		}

		TS_LOG_INFO("Bootloader ID:%d Version:%d\n", buf[1], buf[2]);

		return buf[0];
	} else {
		TS_LOG_INFO("Bootloader ID:%d\n", val & MXT_BOOT_ID_MASK);

		return val;
	}
}

static int mxt_wait_for_int_status_change(struct mxt_data *data, int timeout)
{
	int irq_gpio = data->chip_data->irq_gpio;

	do {
		if (0 == gpio_get_value(irq_gpio))
			return 0;
		else
			udelay(100);
	} while(timeout --);

	TS_LOG_INFO("mxt_wait_for_int_status_change timeout\n");
	return -1;
}

static int mxt_check_bootloader(struct mxt_data *data, unsigned int state,
				bool wait)
{
	u8 val;
	int ret;

recheck:
	if (wait) {
		/*
		 * In application update mode, the interrupt
		 * line signals state transitions. We must wait for the
		 * CHG assertion before reading the status byte.
		 * Once the status byte has been read, the line is deasserted.
		 */
		ret = mxt_wait_for_int_status_change(data, MXT_FW_CHG_TIMEOUT);
		if (ret) {
			/*
			 * TODO: handle -EINTR better by terminating fw update
			 * process before returning to userspace by writing
			 * length 0x000 to device (iff we are in
			 * WAITING_FRAME_DATA state).
			 */
			TS_LOG_ERR("Update wait error %d\n", ret);
			// don't return false if there is interrupt issue
			//return ret;
		}
	}

	ret = mxt_bootloader_read(data, &val, 1);
	if (ret) {
		TS_LOG_ERR("%s:mxt_bootloader_read read failed\n",__func__);
		return ret;
	}

	if (state == MXT_WAITING_BOOTLOAD_CMD)
		val = mxt_get_bootloader_version(data, val);

	switch (state) {
	case MXT_WAITING_BOOTLOAD_CMD:
	case MXT_WAITING_FRAME_DATA:
	case MXT_APP_CRC_FAIL:
		val &= ~MXT_BOOT_STATUS_MASK;
		break;
	case MXT_FRAME_CRC_PASS:
		if (val == MXT_FRAME_CRC_CHECK) {
			goto recheck;
		} else if (val == MXT_FRAME_CRC_FAIL) {
			TS_LOG_ERR("Bootloader CRC fail\n");
			return -EINVAL;
		}
		break;
	default:
		TS_LOG_ERR("%s:default branch called\n",__func__);
		return -EINVAL;
	}

	if (val != state) {
		TS_LOG_ERR("Invalid bootloader state %02X != %02X\n",
			val, state);
		return -EINVAL;
	}

	return 0;
}

static void wait_exit_bootloader(struct mxt_data *data, int timeout)
{
	int ret = 0;

	do {
		ret = mxt_probe_info_block(data);
		if (!ret)
			return;
		else
			udelay(200);
	} while(timeout --);

	TS_LOG_INFO("wait_exit_bootloader timeout\n");
}

int mxt_load_fw(struct mxt_data *data)
{
	const struct firmware *fw = NULL;
	unsigned int frame_size;
	unsigned int pos = 0;
	unsigned int retry = 0;
	unsigned int frame = 0;
	int ret;

	if (!data->fw_name) {
		TS_LOG_ERR("%s:data->fw_name is null\n",__func__);
		return -EEXIST;
	}
	TS_LOG_INFO("mxt_load_fw %s\n",data->fw_name);

	ret = request_firmware(&fw, data->fw_name, &data->ts_dev->dev);
	if (ret) {
		TS_LOG_ERR("Unable to open firmware %s\n", data->fw_name);
		return ret;
	}

	/* Check for incorrect enc file */
	ret = mxt_check_firmware_format(data, fw);
	if (ret) {
		TS_LOG_ERR("%s: mxt_check_firmware_format fail\n",__func__);
		goto release_firmware;
	}

	if (data->in_bootloader) {
		ret = mxt_check_bootloader(data, MXT_WAITING_BOOTLOAD_CMD, false);
		if(ret) {
			TS_LOG_ERR("false bootloader check %d\n", ret);
			data->in_bootloader = false;
		}
	}

	if (!data->in_bootloader) {
		/* Change to the bootloader mode */				
		data->in_bootloader = true;

		ret = mxt_t6_command(data, MXT_COMMAND_RESET,
					 MXT_BOOT_VALUE, false);
		if (ret) {
			TS_LOG_ERR("reset to boot loader mode return %d\n", ret);
			//don't return failed, maybe it's in bootloader mode
			//goto release_firmware;
		}
		msleep(200);

		mxt_lookup_bootloader_address(data, 0);

		/* At this stage, do not need to scan since we know
		 * family ID */
		do {
			ret = mxt_check_bootloader(data, MXT_WAITING_BOOTLOAD_CMD, false);
			if(ret == 0)
				break;
			TS_LOG_ERR("mxt_bootloader_read failed %d retry %d\n", ret,retry);
			mxt_lookup_bootloader_address(data, retry);
		}while(++retry <= 3);
		
		if (ret) {
			data->in_bootloader = false;
			goto release_firmware;
		}
	}

	mxt_free_object_table(data);
	
	ret = mxt_check_bootloader(data, MXT_WAITING_BOOTLOAD_CMD, false);
	if (ret) {
		/* Bootloader may still be unlocked from previous update
		 * attempt */
		ret = mxt_check_bootloader(data, MXT_WAITING_FRAME_DATA, false);
		if (ret) {
			TS_LOG_INFO("%s: mxt_check_bootloader fail\n",__func__);
			data->in_bootloader = false;
			goto release_firmware;
		}
	} else {
		TS_LOG_INFO("Unlocking bootloader\n");

		/* Unlock bootloader */
		ret = mxt_send_bootloader_cmd(data, true);
		if (ret) {
			TS_LOG_INFO("mxt_send_bootloader_cmd fail\n");
			data->in_bootloader = false;
			goto release_firmware;
		}
	}

	while (pos < fw->size) {
		ret = mxt_check_bootloader(data, MXT_WAITING_FRAME_DATA, true);
		if (ret) {
			TS_LOG_ERR("mxt_check_bootloader fail\n");
			goto release_firmware;
		}

		frame_size = ((*(fw->data + pos) << 8) | *(fw->data + pos + 1));

		/* Take account of CRC bytes */
		frame_size += 2;

		/* Write one frame to device */
		ret = mxt_bootloader_write(data, fw->data + pos, frame_size);
		//print_hex_dump(KERN_INFO, "[mxt] ", DUMP_PREFIX_OFFSET, 16, 1, fw->data+pos, frame_size, false);
		if (ret) {
			TS_LOG_ERR("mxt_bootloader_write fail\n");
			goto release_firmware;
		}

		ret = mxt_check_bootloader(data, MXT_FRAME_CRC_PASS, true);
		if (ret) {
			retry++;

			/* Back off by 20ms per retry */
			msleep(retry * 20);

			if (retry > 20) {
				TS_LOG_ERR("Retry count exceeded\n");
				goto release_firmware;
			}
		} else {
			retry = 0;
			pos += frame_size;
			frame++;
		}

		if (frame % 50 == 0)
			TS_LOG_DEBUG("Sent %d frames, %d/%zd bytes\n",
				 frame, pos, fw->size);
	}

	
	TS_LOG_INFO("Sent %ud frames, %ud bytes\n", frame, pos);
	mdelay(105);
	wait_exit_bootloader(data, MXT_FW_RESET_TIME);

	data->in_bootloader = false;

release_firmware:
	release_firmware(fw);
	return ret;
}

