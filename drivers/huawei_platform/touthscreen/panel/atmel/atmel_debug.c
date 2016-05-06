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
#define DEBUG_MSG_MAX		200
#define MXT_T25_PROCESS_TIMEOUT 50
#define MXT_T25_PROCESS_RETRY 100
extern struct ts_data g_ts_data;
static struct mxt_data *mxt_g_data_debug;

void get_average_max_min_data(struct mxt_data *data, char *buf)
{
	int i = 0;

	snprintf((buf), PAGE_SIZE,
		"[%4d,%4d,%4d]",
		data->refs_delta_data.refs_data_Average,
		data->refs_delta_data.refs_data_MaxNum,
		data->refs_delta_data.refs_data_MinNum);

	i = strlen(buf);
	if (i >= 50) {
		TS_LOG_ERR("over buf limit, buf size is %d\n", sizeof(buf));
		return;
	}
	snprintf((buf+i), PAGE_SIZE,
		"[%4d,%4d,%4d]",
		data->refs_delta_data.deltas_data_Average,
		data->refs_delta_data.deltas_data_MaxNum,
		data->refs_delta_data.deltas_data_MinNum);

        return;
}

int get_refs_rx2rx_delta_test(struct mxt_data *data, int data_uplimit, int data_lowlimit)
{
	int tx_n,rx_n;
	s16 rx_value1 = 0;
	s16 rx_value2 = 0;
	s16 rx_delta_value = 0;
	size_t result = 0;

	for(rx_n = 0; rx_n < (data->y_size -data->y_origin) - 1; rx_n++) {
		for(tx_n = 0; tx_n < (data->x_size -data->x_origin); tx_n++) {
			rx_delta_value = data->T37_buf[tx_n*(data->y_size -data->y_origin)+rx_n+1] - data->T37_buf[tx_n*(data->y_size -data->y_origin)+rx_n];
			if((rx_delta_value <= data_uplimit) && (rx_delta_value >= data_lowlimit)){
				result++;
			}
			//printk("%5d", rx_delta_value);
		}
		//printk("\n");
	}

	if (result == (data->T37_buf_size/sizeof(int) -(data->x_size -data->x_origin))) {
		TS_LOG_INFO("rawdata rx diff is all right, result = %d\n", result);
		return 1;
	} else
		return 0;
}

int get_refs_tx2tx_delta_test(struct mxt_data *data, int data_uplimit, int data_lowlimit)
{
	int tx_n,rx_n;
	s16 tx_delta_value = 0;
	size_t result = 0;

	for(tx_n = 0; tx_n < (data->x_size -data->x_origin) - 1; tx_n++) {
		for(rx_n = 0; rx_n < (data->y_size -data->y_origin); rx_n++) {
			tx_delta_value = data->T37_buf[(tx_n+1)*(data->y_size -data->y_origin)+rx_n] - data->T37_buf[tx_n*(data->y_size -data->y_origin)+rx_n];
			if((tx_delta_value <= data_uplimit) && (tx_delta_value >= data_lowlimit))
				result++;
			//printk("%5d", tx_delta_value);
		}
		//printk("\n");
	}

	if (result == (data->T37_buf_size/sizeof(int) -(data->y_size -data->y_origin))) {
		TS_LOG_INFO("rawdata tx diff is all right, result = %d\n", result);
		return 1;
	} else
		return 0;
}


int get_refs_max_minus_min_test(struct mxt_data *data, int data_limit)
{
	int max_num = data->refs_delta_data.refs_data_MaxNum;
	int min_num = data->refs_delta_data.refs_data_MinNum;

	if (max_num - min_num < data_limit) {
		return 1;
	} else {
		return 0;
	}
}

int get_refs_or_deltas_data_test(struct mxt_data *data, int data_uplimit, int data_lowlimit)
{
	int i = 0;
	size_t result = 0;
	int DataSum = 0;
	int Data_Val = 0;
	int Data_Max, Data_Min, Data_ave;
	int Data_count = 0;

	Data_Max = data->T37_buf[0];
	Data_Min = data->T37_buf[0];

	for (i = 0; i < data->T37_buf_size/sizeof(int); i++) {
		if ((data->T37_buf[i] <= data_uplimit) && (data->T37_buf[i] >= data_lowlimit))
			result ++;
		else
			TS_LOG_INFO("overlimit[%d]:[%d]\n", i, data->T37_buf[i]);

		Data_Val = data->T37_buf[i];
		DataSum += Data_Val;
		if (Data_Val > Data_Max)
			Data_Max = Data_Val;
		if (Data_Val < Data_Min)
			Data_Min = Data_Val;
	}

	Data_count = data->T37_buf_size/sizeof(int);
	Data_ave = DataSum/Data_count;
	data->refs_delta_data.MaxNum = Data_Max;
	data->refs_delta_data.MinNum = Data_Min;
	data->refs_delta_data.Average = Data_ave;

	TS_LOG_INFO("DataSum:%d, count:%d, Average:%d, MaxNum:%d, MinNum:%d\n",
		DataSum, data->T37_buf_size/sizeof(int), data->refs_delta_data.Average, data->refs_delta_data.MaxNum, data->refs_delta_data.MinNum);
	if (result == data->T37_buf_size/sizeof(int)) {
		TS_LOG_INFO("all data is ok, result:%d\n", result);
		return 1;
	} else {
		TS_LOG_INFO("some data is bad, result:%d\n", result);
		return 0;
	}
}

static inline int mxt_obj_instances(const struct mxt_object *obj)
{
	return obj->instances_minus_one + 1;
}

static inline int mxt_obj_size(const struct mxt_object *obj)
{
	return obj->size_minus_one + 1;
}

/*
 * Helper function for performing a T6 diagnostic command
 */
static int mxt_T6_diag_cmd(struct mxt_data *data, struct mxt_object *T6,
			   u8 cmd)
{
	int ret;
	u16 addr = T6->start_address + MXT_COMMAND_DIAGNOSTIC;

	ret = mxt_write_reg(data, addr, cmd);
	if (ret) {
		TS_LOG_ERR("%s: write reg %u error\n",__func__,addr);
		return ret;
	}

	/*
	 * Poll T6.diag until it returns 0x00, which indicates command has
	 * completed.
	 */
	while (cmd != 0) {
		ret = __mxt_read_reg(data, addr, 1, &cmd);
		if (ret) {
			TS_LOG_ERR("%s: read reg %u error\n",__func__,addr);
			return ret;
		}
	}
	return 0;
}
/*
 *Function for reading DELTAS and REFERENCE values for T37 object
 *
 * For both modes, a T37_buf is allocated to stores matrix_xsize * matrix_ysize
 * 2-byte (little-endian) values, which are returned to userspace unmodified.
 *
 * It is left to userspace to parse the 2-byte values.
 * - deltas are signed 2's complement 2-byte little-endian values.
 *     s32 delta = (b[0] + (b[1] << 8));
 * - refs are signed 'offset binary' 2-byte little-endian values, with offset
 *   value 0x4000:
 *     s32 ref = (b[0] + (b[1] << 8)) - 0x4000;
 */
int mxt_T37_fetch(struct mxt_data *data, u8 mode)
{
	struct mxt_object *T6, *T37;
	u8 *obuf;
	ssize_t ret = 0;
	size_t i, j;
	size_t T37_buf_size, num_pages;
	size_t pos;
	u8* T37_tem_buf = NULL;
	size_t T37_tem_buf_size = 0;
	int *tem_buf = NULL;
	size_t tem_buf_size = 0;

	if (!data || !data->object_table) {
		TS_LOG_ERR("data=%ld data->object_table=%ld\n",PTR_ERR(data),PTR_ERR(data->object_table));
		return -ENODEV;
	}

	T6 = mxt_get_object(data, MXT_GEN_COMMANDPROCESSOR_T6);
	T37 = mxt_get_object(data, MXT_DEBUG_DIAGNOSTIC_T37);
	if (!T6 || mxt_obj_size(T6) < 6 || !T37 || mxt_obj_size(T37) < 3) {
		TS_LOG_ERR("Invalid T6 or T37 object\n");
		return -ENODEV;
	}

	tem_buf_size = (data->info->matrix_xsize) * (data->info->matrix_ysize) * sizeof(int);
	tem_buf = kmalloc(tem_buf_size, GFP_KERNEL);
	if (!tem_buf) {
		TS_LOG_ERR("alloc tem_buf failed\n");
		return -ENOMEM;
	}

	//T37_tem_buf_size = (data->x_size -data->x_origin) * (data->y_size -data->y_origin)*sizeof(u8)* 2;
	T37_tem_buf_size = (data->info->matrix_xsize)*(data->info->matrix_ysize)*sizeof(u8)* 2;
	T37_tem_buf = kzalloc(T37_tem_buf_size, GFP_KERNEL);
	if (!T37_tem_buf) {
		TS_LOG_ERR("alloc mem for T37_tem_buf failed\n");
		ret = -ENOMEM;
		goto out;
	}

	/* Something has gone wrong if T37_buf is already allocated */
//	if (data->T37_buf)
	//	return -EINVAL;

	T37_buf_size = (data->x_size -data->x_origin) * (data->y_size -data->y_origin) * sizeof(int);

	/* Temporary buffer used to fetch one T37 page */
	obuf = kmalloc(mxt_obj_size(T37), GFP_KERNEL);
	if (!obuf) {
		TS_LOG_ERR("alloc mem for obuf failed\n");
		ret = -ENOMEM;
		goto out;
	}

	num_pages = DIV_ROUND_UP(T37_buf_size, mxt_obj_size(T37) - 2);
	TS_LOG_INFO("%s, num_pages = %d\n", __func__, num_pages);
	pos = 0;
	for (i = 0; i < num_pages; i++) {
		u8 cmd;
		size_t chunk_len;

		/* For first page, send mode as cmd, otherwise PageUp */
		cmd = (i == 0) ? mode : MXT_T6_DEBUG_PAGEUP;
		ret = mxt_T6_diag_cmd(data, T6, cmd);
		if (ret) {
			TS_LOG_ERR("mxt_T6_diag_cmd failed ret=%d\n",ret);
			goto out;
		}

		ret = __mxt_read_reg(data, T37->start_address,
				mxt_obj_size(T37), obuf);
		if (ret) {
			TS_LOG_ERR("read MXT_DEBUG_DIAGNOSTIC_T37 failed\n");
			goto out;
		}

		/* Verify first two bytes are current mode and page # */
		if (obuf[0] != mode) {
			TS_LOG_ERR("Unexpected mode (%u != %u)\n", obuf[0], mode);
			ret = -EIO;
			goto out;
		}

		if (obuf[1] != i) {
			TS_LOG_ERR("Unexpected page (%u != %zu)\n", obuf[1], i);
			ret = -EIO;
			goto out;
		}

		/*
		 * Copy the data portion of the page, or however many bytes are
		 * left, whichever is less.
		 */
		chunk_len = min(mxt_obj_size(T37) - 2, T37_buf_size - pos);
		//memcpy(&data->T37_buf[pos], &obuf[2], chunk_len);
		memcpy(&T37_tem_buf[pos], &obuf[2], chunk_len);
		pos += chunk_len;
	}

	for (i = 0, j = 0; i < T37_tem_buf_size; i +=2, j++) {
		if (mode == MXT_T6_DEBUG_REF) {
			tem_buf[j]  = (u16)((T37_tem_buf[i+1] << 8) | (T37_tem_buf[i]));
		} else if (mode == MXT_T6_DEBUG_DELTA) {
			tem_buf[j]  = (s16)((T37_tem_buf[i+1] << 8) | (T37_tem_buf[i]));
		}
	}

	/*remove extra data*/
	i = 0;
	j = 0;
	while((i < (data->info->matrix_xsize)*(data->info->matrix_ysize)) && (j < (data->x_size -data->x_origin)*(data->y_size -data->y_origin))) {
		data->T37_buf[j] = tem_buf[i];
		i ++;
		j ++;
		if (0 == j%(data->y_size -data->y_origin))
			i += (data->info->matrix_ysize - data->y_size + data->y_origin);
	}

	ret = 0;

out:

	if (T37_tem_buf) {
		kfree(T37_tem_buf);
		T37_tem_buf = NULL;
	}

	if (tem_buf) {
		kfree(tem_buf);
		tem_buf = NULL;
	}

	if (obuf) {
		kfree(obuf);
		obuf = NULL;
	}
	return ret;
}


void mxt_debug_msg_remove(struct mxt_data *data)
{
	if (data->debug_msg_attr.attr.name)
		sysfs_remove_bin_file(&g_ts_data.client->dev.kobj,
					  &data->debug_msg_attr);
}

/* Firmware Version is returned as Major.Minor.Build */
static ssize_t mxt_fw_version_show(struct device *dev,
					struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = mxt_g_data_debug;

	if (!data)
		return -ENODEV;

	if (!data->info)
		return 0;
		
	return scnprintf(buf, PAGE_SIZE, "%u.%u.%02X\n",
			 data->info->version >> 4, data->info->version & 0xf,
			 data->info->build);
}

/* Hardware Version is returned as FamilyID.VariantID */
static ssize_t mxt_hw_version_show(struct device *dev,
					struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = mxt_g_data_debug;

	if (!data)
		return -ENODEV;

	if (!data->info)
		return 0;
	
	return scnprintf(buf, PAGE_SIZE, "%02x.%02x\n",
			data->info->family_id, data->info->variant_id);
}

static bool mxt_object_readable(unsigned int type)
{
	switch (type) {
	/*
	case MXT_GEN_COMMAND_T6:
	case MXT_GEN_POWER_T7:
	case MXT_GEN_ACQUIRE_T8:
	case MXT_GEN_DATASOURCE_T53:
	case MXT_TOUCH_MULTI_T9:
	case MXT_TOUCH_KEYARRAY_T15:
	case MXT_TOUCH_PROXIMITY_T23:
	case MXT_TOUCH_PROXKEY_T52:
	case MXT_PROCI_GRIPFACE_T20:
	case MXT_PROCG_NOISE_T22:
	case MXT_PROCI_ONETOUCH_T24:
	case MXT_PROCI_TWOTOUCH_T27:
	case MXT_PROCI_GESTURE_T92:
	case MXT_PROCI_GRIP_T40:
	case MXT_PROCI_PALM_T41:
	case MXT_PROCI_TOUCHSUPPRESSION_T42:
	case MXT_PROCI_STYLUS_T47:
	case MXT_PROCG_NOISESUPPRESSION_T48:
	case MXT_SPT_COMMSCONFIG_T18:
	case MXT_SPT_GPIOPWM_T19:
	case MXT_SPT_SELFTEST_T25:
	case MXT_SPT_CTECONFIG_T28:
	case MXT_SPT_USERDATA_T38:
	case MXT_SPT_DIGITIZER_T43:
	case MXT_SPT_CTECONFIG_T46:
	*/
		return true;
	default:
		return false;
	}
}

static ssize_t mxt_show_instance(char *buf, int count,
				 struct mxt_object *object, int instance,
				 const u8 *val)
{
	int i;

	if (mxt_obj_instances(object) > 1)
		count += scnprintf(buf + count, PAGE_SIZE - count,
					"Instance %u\n", instance);

	for (i = 0; i < mxt_obj_size(object); i++)
		count += scnprintf(buf + count, PAGE_SIZE - count,
				"\t[%2u]: %02x (%d)\n", i, val[i], val[i]);
	count += scnprintf(buf + count, PAGE_SIZE - count, "\n");

	return count;
}

static ssize_t mxt_object_show(struct device *dev,
					struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = mxt_g_data_debug;
	struct mxt_object *object;
	int count = 0;
	int i, j;
	int error;
	u8 *obuf;

	if (!data)
		return -ENODEV;

	/* Pre-allocate buffer large enough to hold max sized object. */
	obuf = kmalloc(256, GFP_KERNEL);
	if (!obuf)
		return -ENOMEM;

	error = 0;
	for (i = 0; i < data->info->object_num; i++) {
		object = data->object_table + i;

		if (!mxt_object_readable(object->type))
			continue;

		count += scnprintf(buf + count, PAGE_SIZE - count,
				"T%u:\n", object->type);

		for (j = 0; j < mxt_obj_instances(object); j++) {
			u16 size = mxt_obj_size(object);
			u16 addr = object->start_address + j * size;

			error = __mxt_read_reg(data, addr, size, obuf);
			if (error)
				goto done;

			count = mxt_show_instance(buf, count, object, j, obuf);
		}
	}

done:
	kfree(obuf);
	return error ?: count;
}

static ssize_t mxt_update_fw_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	return count;
}

static ssize_t mxt_update_cfg_store(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	return count;
}

static void mxt_debug_msg_enable(struct mxt_data *data)
{
	if (data->debug_v2_enabled)
		return;

	mutex_lock(&data->debug_msg_lock);

	data->debug_msg_data = kcalloc(DEBUG_MSG_MAX,
				data->T5_msg_size, GFP_KERNEL);
	if (!data->debug_msg_data) {
		TS_LOG_ERR( "Failed to allocate buffer\n");
		return;
	}

	data->debug_v2_enabled = true;
	mutex_unlock(&data->debug_msg_lock);

	TS_LOG_DEBUG("Enabled message output\n");
}

static void mxt_debug_msg_disable(struct mxt_data *data)
{
	if (!data->debug_v2_enabled)
		return;

	TS_LOG_DEBUG("disabling message output\n");
	data->debug_v2_enabled = false;

	mutex_lock(&data->debug_msg_lock);
	kfree(data->debug_msg_data);
	data->debug_msg_data = NULL;
	data->debug_msg_count = 0;
	mutex_unlock(&data->debug_msg_lock);
	TS_LOG_DEBUG("Disabled message output\n");
}

static ssize_t mxt_debug_v2_enable_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	int i;

	if (!data)
		return -ENODEV;

	if (sscanf(buf, "%u", &i) == 1 && i < 2) {
		if (i == 1)
			mxt_debug_msg_enable(data);
		else
			mxt_debug_msg_disable(data);

		return count;
	} else {
		TS_LOG_DEBUG("debug_enabled write error\n");
		return -EINVAL;
	}
}

static ssize_t mxt_debug_notify_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "0\n");
}

static ssize_t mxt_debug_enable_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = mxt_g_data_debug;
	char c;

	if (!data)
		return -ENODEV;

	c = data->debug_enabled ? '1' : '0';
	return scnprintf(buf, PAGE_SIZE, "%c\n", c);
}

static ssize_t mxt_debug_enable_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	int i;

	if (!data)
		return -ENODEV;

	if (sscanf(buf, "%u", &i) == 1 && i < 2) {
		data->debug_enabled = (i == 1);

		TS_LOG_DEBUG("%s\n", i ? "debug enabled" : "debug disabled");
		return count;
	} else {
		TS_LOG_DEBUG("debug_enabled write error\n");
		return -EINVAL;
	}
}

static ssize_t mxt_bootloader_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = mxt_g_data_debug;
	char c;

	if (!data)
		return -ENODEV;

	c = data->in_bootloader ? '1' : '0';
	return scnprintf(buf, PAGE_SIZE, "%c\n", c);
}

static ssize_t mxt_bootloader_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	int i;

	if (!data)
		return 0;

	if (sscanf(buf, "%u", &i) == 1 && i < 2) {
		data->in_bootloader = (i == 1);

		TS_LOG_DEBUG("%s\n", i ? "in bootloader" : "app mode");
		return count;
	} else {
		TS_LOG_DEBUG("in_bootloader write error\n");
		return -EINVAL;
	}
}

static ssize_t mxt_t19_gpio_show(struct device *dev,
					struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = mxt_g_data_debug;

	if (!data)
		return -ENODEV;
	
	return scnprintf(buf, PAGE_SIZE, "%02x (GPIO 0x%02x)\n",
			 data->t19_msg[0],
			 (data->t19_msg[0]>>2) & 0xf);
}

static int mxt_t19_command(struct mxt_data *data, bool enable, bool wait)
{
	u16 reg;
	int timeout_counter = 0;
	int ret;
	u8  val[1];

	reg = data->T19_address;
	val[0] = 60;

	ret = __mxt_write_reg(data, reg + 3, sizeof(val), val);
	if (ret)
		return ret;

	val[0] = 7;
	ret = __mxt_write_reg(data, reg, sizeof(val), val);
	if (ret)
		return ret;

	if (!wait)
		return 0;

	do {
		msleep(25);
		ret = __mxt_read_reg(data, reg, 1, &val[0]);
		if (ret)
			return ret;
	} while ((val[0] & 0x4) && (timeout_counter++ <= 100));

	if (timeout_counter > 100) {
		TS_LOG_ERR( "Command failed!\n");
		return -EIO;
	}

	return 0;
}


static ssize_t mxt_t19_gpio_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	u8 cmd;

	if (!data)
		return -ENODEV;

	if (sscanf(buf, "%hhd", &cmd) == 1) {
		if (cmd == 0) {
			data->alt_chip = 0;
			return count;
		}else if (cmd == 1) {
			if (mxt_t19_command(data,!!cmd,1) == 0) {
				data->alt_chip = cmd;
				return count;
			}
			TS_LOG_DEBUG("mxt_t19_cmd_store write cmd %x error\n",cmd);
		}
		return -EINVAL;
	} else {
		TS_LOG_DEBUG("mxt_t19_cmd_store write error\n");
		return -EINVAL;
	}
}

/* Firmware Version is returned as Major.Minor.Build */
static ssize_t mxt_t25_selftest_show(struct device *dev,
					struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = mxt_g_data_debug;
	ssize_t offset = 0;

	if (!data)
		return -ENODEV;

	if (data->t25_msg[0] == 0xFE)
		offset += scnprintf(buf, PAGE_SIZE, "PASS\n");
	else
		offset += scnprintf(buf, PAGE_SIZE, "FAILED\n");

	offset += scnprintf(buf + offset, PAGE_SIZE, "%x %x %x %x %x %x\n",
		 data->t25_msg[0],
		 data->t25_msg[1],
		 data->t25_msg[2],
		 data->t25_msg[3],
		 data->t25_msg[4],
		 data->t25_msg[5]);
	return offset;
}

static int mxt_t25_command(struct mxt_data *data, u8 cmd, bool wait)
{
	u16 reg;
	int timeout_counter = 0;
	int ret;
	u8  val[2];

	reg = data->T25_address;
	val[0] = 0x3;
	val[1] = cmd;

	ret = __mxt_write_reg(data, reg, sizeof(val), val);
	if (ret) {
		TS_LOG_ERR( "write T25 command failed\n");
		return ret;
	}

	if (!wait) {
		TS_LOG_INFO("no need to wait\n");
		return 0;
	}

	do {
		msleep(14);
		ret = __mxt_read_reg(data, reg + 1, 1, &val[1]);
		if (ret) {
			TS_LOG_ERR( "read T25 command failed,already try %d times\n",timeout_counter);
			return ret;
		}
	} while ((val[1] != 0) && (timeout_counter++ <= 50));

	if (timeout_counter > 100) {
		TS_LOG_ERR( "Command failed!\n");
		return -EIO;
	}

	return 0;
}

int mxt_t25_selftest(struct mxt_data *data)
{
	u32 cmd = 0;
	data->t25_msg[0] = 0;
	data->t25_msg[5] = 0;
	u32 i;

	cmd = 1;
	if (mxt_t25_command(data,(u8)cmd,1) == 0) {
		TS_LOG_INFO("mxt_t25_command ok\n");
	}

	mdelay(100);
	for ( i = 0 ; i < MXT_T25_PROCESS_RETRY ; i ++ ) {
		process_messages(data, MXT_T25_PROCESS_TIMEOUT);
		TS_LOG_DEBUG("%x %x %x %x %x %x %x\n",
			data->t25_msg[0], data->t25_msg[1], data->t25_msg[2],
			data->t25_msg[3], data->t25_msg[4], data->t25_msg[5]);
		if (data->t25_msg[0] == 0xFE) {
			break;
		}
	}

	if ( i == MXT_T25_PROCESS_RETRY) {
           TS_LOG_INFO("mxt_t25_selftest fail\n");
           return 0;
	}
	TS_LOG_INFO("mxt_t25_selftest success\n");
	return 1;

}

static ssize_t mxt_t25_selftest_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	u32 cmd;

	if (!data)
		return -ENODEV;

	if (sscanf(buf, "%x", &cmd) == 1) {
		if (mxt_t25_command(data,(u8)cmd,1) == 0)
			return count;
			
		TS_LOG_DEBUG("mxt_t25_cmd_store write cmd %x error\n",cmd);
		return -EINVAL;
	} else {
		TS_LOG_DEBUG("mxt_t25_cmd_store write error\n");
		return -EINVAL;
	}
}

static ssize_t mxt_cmd_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	u32 cmd;
	const char *command_list[] = {
		"# por",
		"# reset",
	};

	TS_LOG_DEBUG("[mxt]%s\n",buf);

	if (!data)
		return -ENODEV;

	if (sscanf(buf, "%x", &cmd) >= 1) {
		TS_LOG_DEBUG("[mxt] cmd %d (%d): %s\n",cmd,ARRAY_SIZE(command_list),command_list[cmd]);
		if (cmd >=0 && cmd < ARRAY_SIZE(command_list)) {
			if (cmd == 0) {
				return count;
			}
		}
		return -EINVAL;
	} else {
		TS_LOG_DEBUG("mxt_t19_cmd_store write error\n");
		return -EINVAL;
	}
}

static DEVICE_ATTR(fw_version, S_IRUGO, mxt_fw_version_show, NULL);
static DEVICE_ATTR(hw_version, S_IRUGO, mxt_hw_version_show, NULL);
static DEVICE_ATTR(object, S_IRUGO, mxt_object_show, NULL);
static DEVICE_ATTR(update_fw, S_IWUSR /*| S_IWGRP | S_IWOTH */, NULL, mxt_update_fw_store);
static DEVICE_ATTR(update_cfg, S_IWUSR/* | S_IWGRP | S_IWOTH */, NULL, mxt_update_cfg_store);
static DEVICE_ATTR(debug_v2_enable, 0660/*S_IWUSR | S_IRUSR*/, NULL, mxt_debug_v2_enable_store);
static DEVICE_ATTR(debug_notify, S_IRUGO, mxt_debug_notify_show, NULL);
static DEVICE_ATTR(debug_enable, S_IWUSR | S_IRUSR, mxt_debug_enable_show,
			mxt_debug_enable_store);
static DEVICE_ATTR(bootloader, S_IWUSR | S_IRUSR, mxt_bootloader_show,
			mxt_bootloader_store);
static DEVICE_ATTR(t19, S_IWUSR | S_IRUSR /*| S_IWGRP | S_IWOTH */, mxt_t19_gpio_show,
			mxt_t19_gpio_store);
static DEVICE_ATTR(t25, S_IWUSR | S_IRUSR /*| S_IWGRP | S_IWOTH*/, mxt_t25_selftest_show,
			mxt_t25_selftest_store);
static DEVICE_ATTR(cmd, S_IWUSR, NULL, mxt_cmd_store);

static struct attribute *mxt_attrs[] = {
	&dev_attr_fw_version.attr,
	&dev_attr_hw_version.attr,
	&dev_attr_object.attr,
	&dev_attr_update_fw.attr,
	&dev_attr_update_cfg.attr,
	&dev_attr_debug_enable.attr,
	&dev_attr_debug_v2_enable.attr,
	&dev_attr_debug_notify.attr,
	&dev_attr_bootloader.attr,
	&dev_attr_t19.attr,
	&dev_attr_t25.attr,
	&dev_attr_cmd.attr,
	NULL
};

static const struct attribute_group mxt_attr_group = {
	.attrs = mxt_attrs,
};
static int mxt_check_mem_access_params(struct mxt_data *data, loff_t off,
						size_t *count, int max_size)
{
	if (off >= data->mem_size)
		return -EIO;

	if (off + *count > data->mem_size)
		*count = data->mem_size - off;

	if (*count > max_size)
		*count = max_size;

	return 0;
}

static ssize_t mxt_debug_msg_write(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off,
	size_t count)
{
	return -EIO;
}

static ssize_t mxt_debug_msg_read(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off, size_t bytes)
{
	struct mxt_data *data = mxt_g_data_debug;
	
	int count;
	size_t bytes_read;

	if (!data)
		return 0;

	if (!data->debug_msg_data) {
		TS_LOG_ERR("No buffer!\n");
		return 0;
	}

	mutex_lock(&data->debug_msg_lock);

	count = bytes / data->T5_msg_size;

	if (count > DEBUG_MSG_MAX)
		count = DEBUG_MSG_MAX;

	if (count > data->debug_msg_count)
		count = data->debug_msg_count;

	bytes_read = count * data->T5_msg_size;

	memcpy(buf, data->debug_msg_data, bytes_read);
	data->debug_msg_count = 0;

	mutex_unlock(&data->debug_msg_lock);

	return bytes_read;
}

static ssize_t mxt_mem_access_read(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	int ret = 0;

	if (!data)
		return -ENODEV;

	ret = mxt_check_mem_access_params(data, off, &count, MXT_MAX_BLOCK_READ);
	if (ret < 0)
		return ret;

	mutex_lock(&data->access_mutex);
	
	if (count > 0)
		ret = __mxt_read_reg(data, off, count, buf);

	mutex_unlock(&data->access_mutex);

	return ret == 0 ? count : ret;
}

static ssize_t mxt_mem_access_write(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off,
	size_t count)
{
	struct mxt_data *data = mxt_g_data_debug;
	int ret = 0;

	if (!data)
		return -ENODEV;

	ret = mxt_check_mem_access_params(data, off, &count, MXT_MAX_BLOCK_WRITE);
	if (ret < 0)
		return ret;

	mutex_lock(&data->access_mutex);
	
	if (count > 0)
		ret = __mxt_write_reg(data, off, count, buf);
	
	mutex_unlock(&data->access_mutex);

	return ret == 0 ? count : 0;
}

void mxt_debug_msg_add(struct mxt_data *data, u8 *msg)
{
	if (!data->debug_msg_data) {
		TS_LOG_ERR("No buffer!\n");
		return;
	}

	mutex_lock(&data->debug_msg_lock);

	if (data->debug_msg_count < DEBUG_MSG_MAX) {
		memcpy(data->debug_msg_data + data->debug_msg_count * data->T5_msg_size,
				msg,
				data->T5_msg_size);
		data->debug_msg_count++;
	} else {
		TS_LOG_DEBUG("Discarding %u messages\n", data->debug_msg_count);
		data->debug_msg_count = 0;
	}

	mutex_unlock(&data->debug_msg_lock);

	sysfs_notify(&g_ts_data.client->dev.kobj, NULL, "debug_notify");
}

int mxt_mem_access_init(struct mxt_data *data)
{
	int error = 0;

	error = sysfs_create_group(&g_ts_data.client->dev.kobj, &mxt_attr_group);
	if (error) {
		TS_LOG_ERR("Failure %d creating sysfs group\n", error);
		return 0;
	}

	sysfs_bin_attr_init(&data->mem_access_attr);
	data->mem_access_attr.attr.name = "mem_access";
	data->mem_access_attr.attr.mode = 0660 /*S_IRUGO | S_IWUSR*/;
	data->mem_access_attr.read = mxt_mem_access_read;
	data->mem_access_attr.write = mxt_mem_access_write;
	data->mem_access_attr.size = data->mem_size;

	if (sysfs_create_bin_file(&g_ts_data.client->dev.kobj,
				  &data->mem_access_attr) < 0) {
		TS_LOG_ERR("Failed to create %s\n", data->mem_access_attr.attr.name);
		goto err_remove_sysfs_group;
	}

	return 0;
err_remove_sysfs_group:
	sysfs_remove_group(&g_ts_data.client->dev.kobj, &mxt_attr_group);
	return 0;
}

int mxt_debug_msg_init(struct mxt_data *data)
{
	mxt_g_data_debug = data;

	sysfs_bin_attr_init(&data->debug_msg_attr);
	data->debug_msg_attr.attr.name = "debug_msg";
	data->debug_msg_attr.attr.mode = 0660;
	data->debug_msg_attr.read = mxt_debug_msg_read;
	data->debug_msg_attr.write = mxt_debug_msg_write;
	data->debug_msg_attr.size = data->T5_msg_size * DEBUG_MSG_MAX;

	if (sysfs_create_bin_file(&g_ts_data.client->dev.kobj,
				  &data->debug_msg_attr) < 0) {
		TS_LOG_ERR("Failed to create %s\n", data->debug_msg_attr.attr.name);
		return -EINVAL;
	}

	return NO_ERR;

err_remove_mem_access:
	sysfs_remove_group(&g_ts_data.client->dev.kobj, &mxt_attr_group);
	return 0;
}
