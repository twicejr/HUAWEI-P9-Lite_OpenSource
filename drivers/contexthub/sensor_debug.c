#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include "inputhub_route.h"
#include "sensor_info.h"
#include "sensor_debug.h"
#include "rdr_sensorhub.h"

#define MAX_STR_SIZE (1024)
#define MAX_CMD_BUF_ARGC (64)

static struct class *sensors_class = NULL;
struct t_sensor_debug_operations_list sensor_debug_operations_list =
{
	.mlock = __MUTEX_INITIALIZER(sensor_debug_operations_list.mlock),
	.head = LIST_HEAD_INIT(sensor_debug_operations_list.head),
};

//to find tag by str
static const struct sensor_debug_tag_map tag_map_tab[] =
{
	{"accel",				TAG_ACCEL},
	{"magnitic",			TAG_MAG},
	{"gyro",				TAG_GYRO},
	{"als_light",			TAG_ALS},
	{"ps_promixy",			TAG_PS},
	{"linear_accel",		TAG_LINEAR_ACCEL},
	{"gravity",				TAG_GRAVITY},
	{"orientation",			TAG_ORIENTATION},
	{"rotationvector",		TAG_ROTATION_VECTORS},
	{"maguncalibrated",		TAG_MAG_UNCALIBRATED},
	{"gamerv",				TAG_GAME_RV},
	{"gyrouncalibrated",	TAG_GYRO_UNCALIBRATED},
	{"significantmotion",	TAG_SIGNIFICANT_MOTION},
	{"stepdetector",		TAG_STEP_DETECTOR},
	{"stepcounter",			TAG_STEP_COUNTER},
	{"geomagnetic",			TAG_GEOMAGNETIC_RV},
	{"airpress",			TAG_PRESSURE},
	{"handpress",			TAG_HANDPRESS},
	{"cap_prox",			TAG_CAP_PROX},
	{"hall",				TAG_HALL},
	{"fault",				TAG_FAULT},
	{"ar",				    TAG_AR},
};

static const char *fault_type_table[] =
{
	{"hardfault"},
	{"busfault"},
	{"memfault"},
	{"usagefault"},
	{"rdrdump"},
};

static int open_sensor(int tag, int argv[], int argc)
{
	int ret = 0;
	if (-1 == tag) {
		return -1;
	}

	if (ap_sensor_enable(tag, true)) {
		return 0;
	}

	hwlog_info("open sensor %d\n", tag);
	ret = inputhub_sensor_enable(tag, true);
	if (!ret && (argc > 0)) {
		hwlog_info("set sensor %d delay %d ms\n", tag, argv[0]);
		ret = inputhub_sensor_setdelay(tag, argv[0]);
	}

	return ret;
}

static int set_delay(int tag, int argv[], int argc)
{
	if (-1 == tag || 0 == argc) {
		return -1;
	}

	if (ap_sensor_setdelay(tag, argv[0])) {
		return 0;
	}

	hwlog_info("set sensor %d delay %d ms\n", tag, argv[0]);
	inputhub_sensor_setdelay(tag, argv[0]);

	return 0;
}

static int close_sensor(int tag, int argv[], int argc)
{
	if (-1 == tag) {
		return -1;
	}

	if (ap_sensor_enable(tag, false)) {
		return 0;
	}

	hwlog_info("close sensor %d\n", tag);
	inputhub_sensor_enable(tag, false);

	return 0;
}

//This funciton is Only for Test:
//I2C address should be modified by virtual address. This virtual address is for Test. 
//And Tools out can put data into system for simulating
static int set_sensor_slave_addr(int tag, int argv[], int argc)
{
    write_info_t    pkg_ap;
    read_info_t pkg_mcu;
    unsigned int i2c_address = 0;
    int ret = -1;

    if (argc == 0){
        return -1;
    }

    i2c_address = argv[0] & 0xFF;
    memset(&pkg_ap, 0, sizeof(pkg_ap));
    memset(&pkg_mcu, 0, sizeof(pkg_mcu));

    pkg_ap.tag = tag;
    pkg_ap.cmd=CMD_SET_SLAVE_ADDR_REQ;
    pkg_ap.wr_buf=&i2c_address;
    pkg_ap.wr_len=sizeof(i2c_address);

    hwlog_info("set_sensor_slave_addr, %s, i2c_addr:0x%x\n", obj_tag_str[tag], i2c_address);

    if ((ret = write_customize_cmd(&pkg_ap, &pkg_mcu)) != 0) {
        hwlog_err("set %s slave addr failed, ret = %d in %s\n", obj_tag_str[tag], ret, __func__);
        return -1;
    }

    if (pkg_mcu.errno != 0) {
        hwlog_err("set %s slave addr failed errno = %d in %s\n", obj_tag_str[tag], pkg_mcu.errno, __func__);
    } else {
        hwlog_info("set %s new slave addr:0x%x success\n", obj_tag_str[tag], i2c_address);
    }

    return 0;
}

#define DEBUG_LEVEL 4
extern struct CONFIG_ON_DDR *pConfigOnDDr;

static int set_log_level(int tag, int argv[], int argc)
{
    write_info_t    pkg_ap;
    read_info_t pkg_mcu;
    uint32_t log_level;
    int ret = -1;

    if (argc != 1){
        return -1;
    }

    log_level = argv[0];
    
    if(log_level > DEBUG_LEVEL)
        return -1;
        
    memset(&pkg_ap, 0, sizeof(pkg_ap));
    memset(&pkg_mcu, 0, sizeof(pkg_mcu));

    pkg_ap.tag = TAG_SYS;
    pkg_ap.cmd= CMD_SYS_LOG_LEVEL_REQ;
    pkg_ap.wr_buf = &log_level;
    pkg_ap.wr_len = sizeof(log_level);



    if ((ret = write_customize_cmd(&pkg_ap,&pkg_mcu)) != 0) {
        hwlog_err("% faile to write cmd\n",__func__);
        return -1;
    }

    if (pkg_mcu.errno != 0) {
        hwlog_err("%s set log level failed errno = %d \n", __func__, pkg_mcu.errno );
        return -1;
    } else {
        pConfigOnDDr->log_level = log_level;
        hwlog_info("%s set log level %d success\n", __func__, log_level);
    }

    return 0;
}

static int set_fault_type(int tag, int argv[], int argc)
{
    write_info_t    pkg_ap;
    uint8_t fault_type = 0;
    int ret = -1;

    if (argc == 0){
        return -1;
    }

    fault_type = argv[0] & 0xFF;

    memset(&pkg_ap, 0, sizeof(pkg_ap));

    pkg_ap.tag = TAG_FAULT;
    pkg_ap.cmd=CMD_SET_FAULT_TYPE_REQ;
    pkg_ap.wr_buf=&fault_type;
    pkg_ap.wr_len=sizeof(fault_type);

    hwlog_info("set_fault_type, %s, fault type:%s\n", obj_tag_str[tag], fault_type_table[fault_type]);

    if ((ret = write_customize_cmd(&pkg_ap, NULL)) != 0) {
        hwlog_err("set fault type %s failed, ret = %d in %s\n", fault_type_table[fault_type], ret, __func__);
        return -1;
    }
	
    hwlog_info("set fault type %s success\n", fault_type_table[fault_type]);

    return 0;
}
// ar_test cmd para1 para2
// cmd  1: enable 3:close 33:start 35:stop 37:update 39:flush
// para1: 1/3/39 ignore 33/37/35/39:time
// para2: 33/37 bitmask 0x1111 of concern events 1/3/39/35 ignore
static int ar_test(int tag, int argv[], int argc)
{
    write_info_t pkg_ap;
    read_info_t pkg_mcu;
    ar_start_cmd_t ar_start;
    ar_stop_cmd_t ar_stop;

    int ret = -1;
    int cmd = argv[0];
    int para1 = argv[1];
    int para2 = argv[2];
    
    memset(&pkg_ap, 0, sizeof(pkg_ap));
    memset(&pkg_mcu, 0, sizeof(pkg_mcu));

    pkg_ap.tag = TAG_AR;

    if ((cmd == CMD_CMN_OPEN_REQ) || (cmd == CMD_CMN_CLOSE_REQ)) {
        pkg_ap.cmd = cmd;
        pkg_ap.wr_buf = NULL;
        pkg_ap.wr_len = 0;
    }
    else if((cmd == CMD_FLP_AR_START_REQ) || (cmd == CMD_FLP_AR_UPDATE_REQ)) {
        pkg_ap.cmd = CMD_CMN_CONFIG_REQ;
        ar_start.sub_cmd = cmd;
        ar_start.start_param.report_interval = para1*1000;
        ar_start.start_param.activity_list[0].activity = AR_ACTIVITY_VEHICLE;
        ar_start.start_param.activity_list[0].event_type = EVENT_BOTH * ((para2>>0)&1);
        ar_start.start_param.activity_list[1].activity = AR_ACTIVITY_RIDING;
        ar_start.start_param.activity_list[1].event_type = EVENT_BOTH * ((para2>>4)&1);
        ar_start.start_param.activity_list[2].activity = AR_ACTIVITY_WALK_SLOW;
        ar_start.start_param.activity_list[2].event_type = EVENT_BOTH * ((para2>>8)&1);
        ar_start.start_param.activity_list[3].activity = AR_ACTIVITY_RUN_FAST;
        ar_start.start_param.activity_list[3].event_type = EVENT_BOTH * ((para2>>12)&1);
        ar_start.start_param.activity_list[4].activity = AR_ACTIVITY_STATIONARY;
        ar_start.start_param.activity_list[4].event_type = EVENT_BOTH * ((para2>>16)&1);
        ar_start.start_param.activity_list[5].activity = AR_ACTIVITY_UNKNOWN;
        ar_start.start_param.activity_list[5].event_type = EVENT_NONE;
        pkg_ap.wr_buf=&ar_start;
        pkg_ap.wr_len=sizeof(ar_start);
    }
    else if ((cmd == CMD_FLP_AR_STOP_REQ) || (cmd == CMD_FLP_AR_FLUSH_REQ))  {
        pkg_ap.cmd = CMD_CMN_CONFIG_REQ;
        ar_stop.sub_cmd = cmd;
        ar_stop.para  = para1*1000;
        pkg_ap.wr_buf=&ar_stop;
        pkg_ap.wr_len=sizeof(ar_stop);
    }
    else {
        hwlog_err("error command in ar_test, cmd=%d\n", cmd);
        return -1;
    }

    ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
    if(ret)
    {
            hwlog_err("send ar cmd to mcu fail,ret=%d\n", ret);
            return ret;
    }
    
    if(pkg_mcu.errno!=0) {
        hwlog_err("set ar cmd fail cmd=%d para1=0x%x para2=0x%x\n", cmd, para1, para2);
    }
    else {
        hwlog_info("set ar cmd success cmd=%d para1=0x%x para2=0x%x\n", cmd, para1, para2);
    }

    return 0;
}

bool find_and_do_cmd(int tag, struct sensor_debug_search_info *tab, int size, int (*op)(struct sensor_debug_search_info *info))
{
	int i;

	if (NULL == tab || NULL == op) {
		hwlog_err("NULL pointer in %s\n", __func__);
		return false;
	}

	for (i = 0; i < size; ++i) {
		if (tag == tab[i].tag) {
			op(&tab[i]);
			break;
		}
	}

	return (i != size);
}

int register_sensorhub_debug_operation(const char *func_name, sensor_debug_pfunc op)
{
	struct sensor_debug_cmd *node = NULL, *n = NULL;
	int ret = 0;

	if (NULL == func_name || NULL == op) {
		hwlog_err("error in %s\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(node, n, &sensor_debug_operations_list.head, entry) {
		if (op == node->operation) {
			hwlog_warn("%s has already registed in %s\n!", func_name, __func__);
			goto out;//return when already registed
		}
	}

	if (NULL == (node = kzalloc(sizeof(*node), GFP_ATOMIC))) {
		hwlog_err("alloc failed in %s\n", __func__);
		ret = -ENOMEM;
		goto out;
	}

	node->str = func_name;
	node->operation = op;
	list_add_tail(&node->entry, &sensor_debug_operations_list.head);

out:
	mutex_unlock(&sensor_debug_operations_list.mlock);

	return ret;
}

int unregister_sensorhub_debug_operation(sensor_debug_pfunc op)
{
	struct sensor_debug_cmd *pos = NULL, *n = NULL;

	if (NULL == op) {
		hwlog_err("error in %s\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(pos, n, &sensor_debug_operations_list.head, entry) {
		if (op == pos->operation) {
			list_del(&pos->entry);
			kfree(pos);
			break;
		}
	}
	mutex_unlock(&sensor_debug_operations_list.mlock);

	return 0;
}

static void register_my_debug_operations(void)
{
	REGISTER_SENSORHUB_DEBUG_OPERATION(open_sensor);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_delay);
	REGISTER_SENSORHUB_DEBUG_OPERATION(close_sensor);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_sensor_slave_addr);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_fault_type);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_log_level);	
	REGISTER_SENSORHUB_DEBUG_OPERATION(ar_test);
}

static inline bool is_space_ch(char ch)
{
	return (' ' == ch) || ('\t' == ch);
}

static inline bool end_of_string(char ch)
{
	bool ret = false;
	switch (ch) {
		case '\0':
		case '\r':
		case '\n':
			ret = true;
			break;

		default:
			ret = false;
			break;
	}

	return ret;
}

//find first pos
static const char *get_str_begin(const char *cmd_buf)
{
	if (NULL == cmd_buf) {
		return NULL;
	}

	while (is_space_ch(*cmd_buf)) {
		++cmd_buf;
	}

	if (end_of_string(*cmd_buf)) {
		return NULL;
	}

	return cmd_buf;
}

//find last pos
static const char *get_str_end(const char *cmd_buf)
{
	if (NULL == cmd_buf) {
		return NULL;
	}

	while (!is_space_ch(*cmd_buf) && !end_of_string(*cmd_buf)) {
		++cmd_buf;
	}

	return cmd_buf;
}

//fuzzy matching
static bool str_fuzzy_match(const char *cmd_buf, const char *target)
{
	if (NULL == cmd_buf || NULL == target) {
		return false;
	}

	for (; !is_space_ch(*cmd_buf) && !end_of_string(*cmd_buf) && *target; ++target) {
		if (*cmd_buf == *target) {
			++cmd_buf;
		}
	}

	return is_space_ch(*cmd_buf) || end_of_string(*cmd_buf);
}

static sensor_debug_pfunc get_operation(const char *str)
{
	sensor_debug_pfunc op = NULL;
	struct sensor_debug_cmd *node = NULL, *n = NULL;

	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(node, n, &sensor_debug_operations_list.head, entry) {
		if (str_fuzzy_match(str, node->str)) {
			op = node->operation;
			break;
		}
	}
	mutex_unlock(&sensor_debug_operations_list.mlock);

	return op;
}

static int get_sensor_tag(const char *str)
{
	int i;
	for (i = 0; i < sizeof(tag_map_tab) / sizeof(tag_map_tab[0]); ++i) {
		if (str_fuzzy_match(str, tag_map_tab[i].str)) {
			return tag_map_tab[i].tag;
		}
	}
	return -1;
}

#define CH_IS_DIGIT(ch) ('0' <= (ch) && (ch) <= '9')
#define CH_IS_HEX(ch) (('A' <= (ch) && (ch) <= 'F') || ('a' <= (ch) && (ch) <= 'f'))
#define CH_IS_HEXDIGIT(ch) (CH_IS_DIGIT(ch) || CH_IS_HEX(ch))
static bool get_arg(const char *str, int *arg)
{
	int val = 0;
	bool neg = false;
	bool hex = false;

	if ('-' == *str) {
		++str;
		neg = true;
	}

	if (('0' == *str) && (('x' == *(str + 1)) || ('X' == *(str + 1)))) {
		str += 2;
		hex = true;
	}

	if (hex) {
		for (; !is_space_ch(*str) && !end_of_string(*str); ++str) {
			if (!CH_IS_HEXDIGIT(*str)) {
				return false;
			}
			val <<= 4;
			val |= (CH_IS_DIGIT(*str) ? (*str - '0') : (((*str | 0x20) - 'a') + 10));
		}
	} else {
		for (; !is_space_ch(*str) && !end_of_string(*str); ++str) {
			if (!CH_IS_DIGIT(*str)) {
				return false;
			}
			val *= 10;
			val += *str - '0';
		}
	}

	*arg = neg ? -val : val;
	return true;
}

static void parse_str(const char *cmd_buf)
{
	sensor_debug_pfunc operation = NULL;
	int tag = -1;
	int arg = -1;
	int argv[MAX_CMD_BUF_ARGC] = {0};
	int argc = 0;

	for (; (cmd_buf = get_str_begin(cmd_buf)) != NULL; cmd_buf = get_str_end(cmd_buf)) {
		if ((NULL == operation) && ((operation = get_operation(cmd_buf)) != NULL)) {//operation
			;
		} else if ((-1 == tag) && ((tag = get_sensor_tag(cmd_buf)) != -1)) {//tag
			;
		} else if (get_arg(cmd_buf, &arg)) {//arg
			if (argc < MAX_CMD_BUF_ARGC) {
				argv[argc++] = arg;
			} else {
				hwlog_err("too many args, %d will be ignored\n", arg);
			}
		} else {
			;
		}
	}

	if (operation != NULL) {
		operation(tag, argv, argc);
	}
}

static ssize_t cls_attr_debug_show_func(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	int i = 0;
	unsigned int offset = 0;
	struct sensor_debug_cmd *node = NULL, *n = NULL;

	offset += sprintf(buf + offset, "operations format:\necho operation+tag+optarg > %s\n", attr->attr.name);
	offset += sprintf(buf + offset, "for example:\nto open accel we input: echo open_sensor accel > %s\n", attr->attr.name);
	offset += sprintf(buf + offset, "to setdelay accel 100 ms we input: echo set_delay accel 100 > %s\n", attr->attr.name);

	offset += sprintf(buf + offset, "\noperations supported as follow:\n");
	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(node, n, &sensor_debug_operations_list.head, entry) {
		offset += sprintf(buf + offset, "%s\n", node->str);
	}
	mutex_unlock(&sensor_debug_operations_list.mlock);

	offset += sprintf(buf + offset, "\ntags supported as follow:\n");
	for (i = 0; i < sizeof(tag_map_tab) / sizeof(tag_map_tab[0]); ++i) {
		offset += sprintf(buf + offset, "%s\n", tag_map_tab[i].str);
	}

	return offset;
}

static ssize_t cls_attr_debug_store_func(struct class *cls,
				struct class_attribute *attr,
				const char *buf, size_t size)
{
	parse_str(buf);
	return size;
}

static CLASS_ATTR(sensorhub_dbg, 0660, cls_attr_debug_show_func, cls_attr_debug_store_func);

static void sensorhub_debug_init(void)
{
	if (class_create_file(sensors_class, &class_attr_sensorhub_dbg)) {
		hwlog_err("create files failed in %s\n", __func__);
	}

	register_my_debug_operations();
}



#define CHECK_SENSOR_COOKIE(data) \
do {\
	if (NULL == data || (!(TAG_SENSOR_BEGIN <= data->tag && data->tag < TAG_SENSOR_END)) || (NULL == data->name)) {\
		hwlog_err("error in %s\n", __func__);\
		return -EINVAL;\
	}\
} while (0)


static ssize_t show_enable(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);
	return snprintf(buf, MAX_STR_SIZE, "%d\n", sensor_status.status[data->tag]);
}
static ssize_t store_enable(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	unsigned long val = 0;
	int ret = -1;
	write_info_t	pkg_ap;
	read_info_t pkg_mcu;
	const char *operation = NULL;

	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	if (strict_strtoul(buf, 10, &val)) {
		return -EINVAL;
	}

	if (ap_sensor_enable(data->tag, (1 == val))) {
		return size;
	}

	operation = ((1 == val) ? "enable" : "disable");
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	pkg_ap.tag = data->tag;
	pkg_ap.cmd = (1 == val) ? CMD_CMN_OPEN_REQ : CMD_CMN_CLOSE_REQ;
	pkg_ap.wr_buf = NULL;
	pkg_ap.wr_len = 0;
	if ((ret = write_customize_cmd(&pkg_ap, &pkg_mcu)) != 0) {
		hwlog_err("%s %s failed, ret = %d in %s\n", operation, data->name, ret, __func__);
		return size;
	}

	if (pkg_mcu.errno != 0) {
		hwlog_err("%s %s failed errno = %d in %s\n", operation, data->name, pkg_mcu.errno, __func__);
	} else {
		hwlog_info("%s %s success\n", operation, data->name);
	}

	return size;
}

static ssize_t show_set_delay(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);
	return snprintf(buf, MAX_STR_SIZE, "%d\n", sensor_status.delay[data->tag]);
}
static ssize_t store_set_delay(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	unsigned long val = 0;
	int ret = 0;
	write_info_t	pkg_ap;
	read_info_t pkg_mcu;

	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val)) {
		return -EINVAL;
	}

	if (ap_sensor_setdelay(data->tag, val)) {
		return size;
	}

	if(val >= 10 && val <= 1000) {//range [10, 1000]
		pkg_ap.tag = data->tag;
		pkg_ap.cmd = CMD_CMN_INTERVAL_REQ;
		pkg_ap.wr_buf = &val;
		pkg_ap.wr_len = sizeof(val);
		if ((ret = write_customize_cmd(&pkg_ap, &pkg_mcu)) != 0) {
			hwlog_err("set %s delay cmd to mcu fail, ret = %d in %s\n", data->name, ret, __func__);
			return ret;
		}
		if (pkg_mcu.errno != 0) {
			hwlog_err("set %s delay failed errno %d in %s\n", data->name, pkg_mcu.errno, __func__);
			return -EINVAL;
		} else {
			hwlog_info("set %s delay (%ld)success\n", data->name, val);
		}
	} else {
		hwlog_err("set %s delay_ms %d ms range error in %s\n", data->name, (int)val, __func__);
		return -EINVAL;
	}

	return size;
}

static ssize_t show_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return snprintf(buf, MAX_STR_SIZE, "%s\n", get_sensor_info_by_tag(data->tag));
}

static ssize_t show_get_data(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	{
		struct t_sensor_get_data *get_data = &sensor_status.get_data[data->tag];
		unsigned int offset = 0;
		int i = 0, mem_num = 0;

		atomic_set(&get_data->reading, 1);
		INIT_COMPLETION(get_data->complete);
		if (0 == wait_for_completion_interruptible(&get_data->complete)) {//return -ERESTARTSYS if interrupted, 0 if completed.
			for (mem_num = get_data->data.length / sizeof(get_data->data.value[0]); i < mem_num; i++) {
				offset += sprintf(buf + offset, "%d\t", get_data->data.value[i]);
			}
			offset += sprintf(buf + offset, "\n");
		}

		return offset;
	}

	return 0;
}
static ssize_t store_get_data(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	{
		struct sensor_data event;
		int arg;
		int argc = 0;

		//parse cmd buffer
		for (; (buf = get_str_begin(buf)) != NULL; buf = get_str_end(buf)) {
			if (get_arg(buf, &arg)) {//arg
				if (argc < (sizeof(event.value) / sizeof(event.value[0]))) {
					event.value[argc++] = arg;
				} else {
					hwlog_err("too many args, %d will be ignored\n", arg);
				}
			}
		}

		//fill sensor event and write to sensor event buffer
		report_sensor_event(data->tag, event.value, sizeof(event.value[0]) * argc);
	}

	return size;
}

static ssize_t show_selftest(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);
	return snprintf(buf, MAX_STR_SIZE, "%s\n", sensor_status.selftest_result[data->tag]);
}

static ssize_t store_selftest(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	unsigned long val = 0;
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	if (strict_strtoul(buf, 10, &val)) {
		return -EINVAL;
	}
	if (1 == val) {
		pkt_header_t pkt;
		pkt_header_resp_t resp_pkt;

		pkt.tag = data->tag;
		pkt.cmd = CMD_SELFTEST_REQ;
		pkt.resp = RESP;
		pkt.length = 0;
		if (0 == WAIT_FOR_MCU_RESP_DATA_AFTER_SEND(&pkt,
													inputhub_mcu_write_cmd(&pkt, sizeof(pkt)),
													4000,
													&resp_pkt,
													sizeof(resp_pkt))) {
			hwlog_err("wait for %s selftest timeout\n", data->name);
			memcpy(sensor_status.selftest_result[data->tag], "1", 2);//flyhorse k : SUC-->"0", OTHERS-->"1"
			return size;
		} else {
			if (resp_pkt.errno != 0) {
				hwlog_err("%s selftest fail\n", data->name);
				memcpy(sensor_status.selftest_result[data->tag], "1", 2);
			} else {
				hwlog_info("%s selftest success\n", data->name);
				memcpy(sensor_status.selftest_result[data->tag], "0", 2);
			}
		}
	}

	return size;
}

static ssize_t show_read_airpress(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return show_sensor_read_airpress_common(dev, attr, buf);
}

static ssize_t show_calibrate(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return sensors_calibrate_show(data->tag, dev, attr, buf);
}

static ssize_t store_calibrate(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return sensors_calibrate_store(data->tag, dev, attr, buf, size);
}

static ssize_t show_selftest_timeout(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return snprintf(buf, MAX_STR_SIZE, "%d\n", 5000);//ms
}

static ssize_t show_calibrate_timeout(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return snprintf(buf, MAX_STR_SIZE, "%d\n", 5000);//ms
}

static ssize_t show_calibrate_method(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data = (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return show_mag_calibrate_method(dev, attr, buf);//none:0, DOE:1, DOEaG:2
}
//files create for every sensor
static struct device_attribute sensors_class_attrs[] = {
	__ATTR(enable, 0660, show_enable, store_enable),
	__ATTR(set_delay, 0660, show_set_delay, store_set_delay),
	__ATTR(info, 0440, show_info, NULL),
	__ATTR(get_data, 0660, show_get_data, store_get_data),
	__ATTR_NULL,
};

//files create for specific sensor
static DEVICE_ATTR(self_test, 0660, show_selftest, store_selftest);
static DEVICE_ATTR(self_test_timeout, 0440, show_selftest_timeout, NULL);
static DEVICE_ATTR(read_airpress, 0440, show_read_airpress, NULL);//only for airpress
static DEVICE_ATTR(set_calidata, 0660, show_calibrate, store_calibrate);//only for airpress
static DEVICE_ATTR(calibrate, 0660, show_calibrate, store_calibrate);
static DEVICE_ATTR(calibrate_timeout, 0440, show_calibrate_timeout, NULL);
static DEVICE_ATTR(calibrate_method, 0440, show_calibrate_method, NULL);//only for magnetic
static struct attribute *acc_sensor_attrs[] = {
	&dev_attr_self_test.attr,
	&dev_attr_self_test_timeout.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_calibrate_timeout.attr,
	NULL,
};
static const struct attribute_group acc_sensor_attrs_grp = {
	.attrs = acc_sensor_attrs,
};

static struct attribute *ps_sensor_attrs[] = {
	&dev_attr_calibrate.attr,
	&dev_attr_calibrate_timeout.attr,
	NULL,
};
static const struct attribute_group ps_sensor_attrs_grp = {
	.attrs = ps_sensor_attrs,
};

static struct attribute *als_sensor_attrs[] = {
	NULL,
};
static const struct attribute_group als_sensor_attrs_grp = {
	.attrs = als_sensor_attrs,
};

static struct attribute *mag_sensor_attrs[] = {
	&dev_attr_self_test.attr,
	&dev_attr_self_test_timeout.attr,
	&dev_attr_calibrate_method.attr,
	NULL,
};
static const struct attribute_group mag_sensor_attrs_grp = {
	.attrs = mag_sensor_attrs,
};

static struct attribute *hall_sensor_attrs[] = {
	NULL,
};
static const struct attribute_group hall_sensor_attrs_grp = {
	.attrs = hall_sensor_attrs,
};

static struct attribute *gyro_sensor_attrs[] = {
	&dev_attr_self_test.attr,
	&dev_attr_self_test_timeout.attr,
	NULL,
};
static const struct attribute_group gyro_sensor_attrs_grp = {
	.attrs = gyro_sensor_attrs,
};

static struct attribute *airpress_sensor_attrs[] = {
	&dev_attr_read_airpress.attr,
	&dev_attr_set_calidata.attr,
	NULL,
};
static const struct attribute_group airpress_sensor_attrs_grp = {
	.attrs = airpress_sensor_attrs,
};

static struct sensor_cookie all_sensors[] =
{
	{
		.tag = TAG_ACCEL,
		.name = "acc_sensor",
		.attrs_group = &acc_sensor_attrs_grp,
	},
	{
		.tag = TAG_PS,
		.name = "ps_sensor",
		.attrs_group = &ps_sensor_attrs_grp,
	},
	{
		.tag = TAG_ALS,
		.name = "als_sensor",
		.attrs_group = &als_sensor_attrs_grp,
	},
	{
		.tag = TAG_MAG,
		.name = "mag_sensor",
		.attrs_group = &mag_sensor_attrs_grp,
	},
	{
		.tag = TAG_HALL,
		.name = "hall_sensor",
		.attrs_group = &hall_sensor_attrs_grp,
	},
	{
		.tag = TAG_GYRO,
		.name = "gyro_sensor",
		.attrs_group = &gyro_sensor_attrs_grp,
	},
	{
		.tag = TAG_PRESSURE,
		.name = "airpress_sensor",
		.attrs_group = &airpress_sensor_attrs_grp,
	},
};

struct device *get_sensor_device_by_name(const char *name)
{
	int i;

	if (NULL == name) {
		return NULL;
	}

	for (i = 0; i < sizeof(all_sensors) / sizeof(all_sensors[0]); ++i) {
		if (all_sensors[i].name && (0 == strcmp(name, all_sensors[i].name))) {
			return all_sensors[i].dev;
		}
	}

	return NULL;
}

static void init_sensors_get_data(void)
{
	int tag;
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		atomic_set(&sensor_status.get_data[tag].reading, 0);
		init_completion(&sensor_status.get_data[tag].complete);
	}
}

void sensor_get_data(struct sensor_data *data)
{
	struct t_sensor_get_data *get_data = NULL;
	if (NULL == data || (!(TAG_SENSOR_BEGIN <= data->type && data->type < TAG_SENSOR_END))) {
		return;
	}

	get_data = &sensor_status.get_data[data->type];
	if (atomic_cmpxchg(&get_data->reading, 1, 0)) {
		memcpy(&get_data->data, data, sizeof(get_data->data));
		complete(&get_data->complete);
	}
}

//device_create->device_register->device_add->device_add_attrs->device_add_attributes
static int sensors_register(void)
{
	int i;
	for (i = 0; i < sizeof(all_sensors) / sizeof(all_sensors[0]); ++i) {
		all_sensors[i].dev = device_create(sensors_class, NULL, 0, &all_sensors[i], all_sensors[i].name);
		if (NULL == all_sensors[i].dev) {
			hwlog_err("[%s] Failed", __func__);
			return -1;
		} else {
			if (all_sensors[i].attrs_group != NULL) {
				if (sysfs_create_group(&all_sensors[i].dev->kobj, all_sensors[i].attrs_group)) {
					hwlog_err("create files failed in %s\n", __func__);
				}
			}
		}
	}
	return 0;
}

static void sensors_unregister(void)
{
	device_destroy(sensors_class, 0);
}

static int sensors_debug_init(void)
{
	if(is_sensorhub_disabled())
	    return -1;
	sensors_class = class_create(THIS_MODULE, "sensors");
	if (IS_ERR(sensors_class)) {
		return PTR_ERR(sensors_class);
	}

	sensors_class->dev_attrs = sensors_class_attrs;
	sensors_register();
	sensorhub_debug_init();

	init_sensors_get_data();

	return 0;
}

static void sensors_debug_exit(void)
{
	sensors_unregister();
	class_destroy(sensors_class);
}

module_init(sensors_debug_init);
module_exit(sensors_debug_exit);

MODULE_AUTHOR("SensorHub <smartphone@huawei.com>");
MODULE_DESCRIPTION("SensorHub debug driver");
MODULE_LICENSE("GPL");

