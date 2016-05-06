#ifndef __SENSOR_DEBUG_H__
#define __SENSOR_DEBUG_H__


#define REGISTER_SENSORHUB_DEBUG_OPERATION(FUNC) \
register_sensorhub_debug_operation(#FUNC, FUNC);

#define UNREGISTER_SENSORHUB_DEBUG_OPERATION(FUNC) \
unregister_sensorhub_debug_operation(FUNC);

typedef int (*sensor_debug_pfunc)(int tag, int argv[], int argc);

struct t_sensor_debug_operations_list
{
	struct list_head head;
	struct mutex mlock;
};

//to find operation by str
struct sensor_debug_cmd
{
	const char *str;
	sensor_debug_pfunc operation;
	struct list_head entry;
};

//to find tag by str
struct sensor_debug_tag_map
{
	const char *str;
	int tag;
};

//to search info by tag
struct sensor_debug_search_info
{
	const char *sensor;
	int tag;
	void *private_data;
};

struct sensor_cookie
{
	int tag;
	const char *name;
	const struct attribute_group *attrs_group;
	struct device *dev;
};

#pragma pack(1)
typedef struct ar_activity_event {
    unsigned int   event_type;
    unsigned int   activity;
    unsigned long long   timestamp;
} ar_activity_event_t;

typedef struct ar_config {
    unsigned int   report_interval;
    ar_activity_event_t   activity_list[6];
} ar_config_t;

typedef struct ar_start_cmd{
    unsigned int                sub_cmd;
    ar_config_t             start_param;
}ar_start_cmd_t;

typedef struct ar_stop_cmd{
    unsigned int                sub_cmd;
    unsigned int       para;
}ar_stop_cmd_t;

typedef struct ar_data {
    ar_activity_event_t activity_list[48];
} ar_data_t;

typedef struct ar_data_cmd{
    pkt_header_t                hd;
    ar_data_t           data;
}ar_data_cmd_t;
#pragma pack()

typedef enum
{
    EVENT_NONE = 0,
    EVENT_ENTER = 1,
    EVENT_EXIT = 2,
    EVENT_BOTH = 3,
} EVENT_TYPE;

typedef enum
{
        AR_ACTIVITY_VEHICLE = 0,
        AR_ACTIVITY_RIDING,
        AR_ACTIVITY_WALK_SLOW,
        AR_ACTIVITY_RUN_FAST,
        AR_ACTIVITY_STATIONARY,
        AR_ACTIVITY_UNKNOWN,
} AR_ACTIVITY_TYPE;

extern int register_sensorhub_debug_operation(const char *func_name, sensor_debug_pfunc op);
extern int unregister_sensorhub_debug_operation(sensor_debug_pfunc op);
extern bool find_and_do_cmd(int tag, struct sensor_debug_search_info *tab, int size, int (*op)(struct sensor_debug_search_info *info));
extern struct device *get_sensor_device_by_name(const char *name);
extern void sensor_get_data(struct sensor_data *data);
#endif
