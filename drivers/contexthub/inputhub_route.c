/*
 *  drivers/misc/inputhub/inputhub_route.c
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen <inputhub@huawei.com>
 *
 */

#include <linux/types.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/freezer.h>
#include <linux/input.h>
#include <linux/i2c.h>
#include <linux/reboot.h>
#include "protocol.h"
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "rdr_sensorhub.h"
#include "sensor_info.h"
#include "sensor_debug.h"
#include "sensor_sys_info.h"
#include <linux/contexthub/motionhub.h>
#include <linux/contexthub/sensorhub.h>
#include <linux/suspend.h>
#include <linux/fb.h>
#include <linux/timer.h>
#include <linux/rtc.h>
#include <huawei_platform/log/log_exception.h>
#include <linux/wakelock.h>
#include <dsm/dsm_pub.h>

#define ROUTE_BUFFER_MAX_SIZE (1024)
#ifdef TIMESTAMP_SIZE
#undef TIMESTAMP_SIZE
#define TIMESTAMP_SIZE (8)
#endif
#define LENGTH_SIZE sizeof(unsigned int)
#define HEAD_SIZE (LENGTH_SIZE+TIMESTAMP_SIZE)
static int step_ref_cnt = 0;
typedef struct {
    int for_alignment;
    union {
        char effect_addr[sizeof(int)];
        int pkg_length;
    };
    int64_t timestamp;
} t_head;

struct type_record {
    const pkt_header_t *pkt_info;
    struct read_info *rd;
    struct completion resp_complete;
    struct mutex lock_mutex;
    spinlock_t lock_spin;
};

static struct type_record type_record;

sys_status_t iom3_sr_status = ST_WAKEUP;

static struct wake_lock wlock;
int iom3_timeout = 2000;

static struct mutex mutex_write_cmd;
static struct mutex mutex_write_adapter;
static wait_queue_head_t iom3_rec_wq;
int g_iom3_state = IOM3_ST_NORMAL;

static uint32_t valid_step_count = 0;
static uint32_t recovery_step_count = 0;

extern int hall_first_report(bool enable);
extern void dmd_log_report(int dmd_mark,const char * err_func,const char * err_msg);
extern struct dsm_client *shb_dclient;
extern unsigned int sensor_read_number[];
extern void rdr_system_error(u32 modid, u32 arg1, u32 arg2);
extern int iom3_power_state;
extern struct completion iom3_reboot;
extern struct CONFIG_ON_DDR *pConfigOnDDr;
//k3v5 report stairs level,record_count base on 1000
#define LEVEL_COUNT 1000
int inputhub_mcu_write_cmd_adapter(const void *buf, unsigned int length, struct read_info *rd);


struct iom3_log_work{
    void *log_p;
    struct delayed_work log_work;
};

struct inputhub_buffer_pos {
    char *pos;
    unsigned int buffer_size;
};

/*
 *Every route item can be used by one reader and one writer.
 */
struct inputhub_route_table {
    unsigned short port;
    struct inputhub_buffer_pos phead; //point to the head of buffer
    struct inputhub_buffer_pos pRead; //point to the read position of buffer
    struct inputhub_buffer_pos pWrite; //point to the write position of buffer
    wait_queue_head_t read_wait;//to block read when no data in buffer
    atomic_t data_ready;
    spinlock_t buffer_spin_lock;//for read write buffer
};

static struct inputhub_route_table  package_route_tbl[] =
{
    {ROUTE_SHB_PORT, {NULL,0},{NULL,0},{NULL,0}, __WAIT_QUEUE_HEAD_INITIALIZER(package_route_tbl[0].read_wait)},
    {ROUTE_MOTION_PORT, {NULL,0},{NULL,0},{NULL,0},__WAIT_QUEUE_HEAD_INITIALIZER(package_route_tbl[1].read_wait)},
};

struct sensors_cmd_map {
    int         hal_sensor_type;
    int         tag;
};

static const struct sensors_cmd_map sensors_cmd_map_tab[] = {
    {SENSORHUB_TYPE_ACCELEROMETER,                  TAG_ACCEL},
    {SENSORHUB_TYPE_LIGHT,                          TAG_ALS},
    {SENSORHUB_TYPE_PROXIMITY,                      TAG_PS},
    {SENSORHUB_TYPE_GYROSCOPE,                      TAG_GYRO},
    {SENSORHUB_TYPE_GRAVITY,                        TAG_GRAVITY},
    {SENSORHUB_TYPE_MAGNETIC,                       TAG_MAG},
    {SENSORHUB_TYPE_ROTATESCREEN,                   TAG_SCREEN_ROTATE},
    {SENSORHUB_TYPE_LINEARACCELERATE,               TAG_LINEAR_ACCEL},
    {SENSORHUB_TYPE_ORIENTATION,                    TAG_ORIENTATION},
    {SENSORHUB_TYPE_ROTATEVECTOR,                   TAG_ROTATION_VECTORS},
    {SENSORHUB_TYPE_PRESSURE,                       TAG_PRESSURE},
    {SENSORHUB_TYPE_TEMPERATURE,                    TAG_TEMP},
    {SENSORHUB_TYPE_RELATIVE_HUMIDITY,              TAG_HUMIDITY},
    {SENSORHUB_TYPE_AMBIENT_TEMPERATURE,            TAG_AMBIENT_TEMP},
    {SENSORHUB_TYPE_MCU_LABC,                       TAG_LABC},
    {SENSORHUB_TYPE_HALL,                           TAG_HALL},
    {SENSORHUB_TYPE_MAGNETIC_FIELD_UNCALIBRATED,    TAG_MAG_UNCALIBRATED},
    {SENSORHUB_TYPE_GAME_ROTATION_VECTOR,           TAG_GAME_RV},
    {SENSORHUB_TYPE_GYROSCOPE_UNCALIBRATED,         TAG_GYRO_UNCALIBRATED},
    {SENSORHUB_TYPE_SIGNIFICANT_MOTION,             TAG_SIGNIFICANT_MOTION},
    {SENSORHUB_TYPE_STEP_DETECTOR,                  TAG_STEP_DETECTOR},
    {SENSORHUB_TYPE_STEP_COUNTER,                   TAG_STEP_COUNTER},
    {SENSORHUB_TYPE_GEOMAGNETIC_ROTATION_VECTOR,    TAG_GEOMAGNETIC_RV},
    {SENSORHUB_TYPE_HANDPRESS,                      TAG_HANDPRESS},
    {SENSORHUB_TYPE_CAP_PROX,                       TAG_CAP_PROX}
};

static uint8_t tag_to_hal_sensor_type[TAG_SENSOR_END];
static uint8_t hal_sensor_type_to_tag[SENSORHUB_TYPE_END];
static void init_hash_tables(void)
{
    int i;
    for (i = 0; i < sizeof(sensors_cmd_map_tab) / sizeof(sensors_cmd_map_tab[0]); ++i) {
        tag_to_hal_sensor_type[sensors_cmd_map_tab[i].tag] = sensors_cmd_map_tab[i].hal_sensor_type;
        hal_sensor_type_to_tag[sensors_cmd_map_tab[i].hal_sensor_type] = sensors_cmd_map_tab[i].tag;
    }
}

static spinlock_t ref_cnt_lock;
static inline bool really_do_enable_disable(int *ref_cnt, bool enable)
{
    bool ret = false;
    unsigned long flags = 0;
    spin_lock_irqsave(&ref_cnt_lock, flags);
    ret = (0 == (enable ? (*ref_cnt)++ : --*ref_cnt));
    spin_unlock_irqrestore(&ref_cnt_lock, flags);
    return ret;
}

static void get_time_stamp(char* timestamp_buf,  unsigned int len)
{
   struct timeval tv;
   struct rtc_time tm;
   if(NULL == timestamp_buf)
   {
       pr_err("timestamp is NULL\n");
       return;
   }
   memset(&tv, 0, sizeof(struct timeval));
   memset(&tm, 0, sizeof(struct rtc_time));
   do_gettimeofday(&tv);
   tv.tv_sec -= sys_tz.tz_minuteswest * 60; /* Ò»·ÖÖÓ=60Ãë */
   rtc_time_to_tm(tv.tv_sec, &tm);
   snprintf(timestamp_buf,len,"%04d%02d%02d%02d%02d%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static int inputhub_route_item(unsigned short port, struct inputhub_route_table **route_item)
{
    int i;
    for (i = 0; i < sizeof(package_route_tbl) / sizeof(package_route_tbl[0]); ++i) {
        if (port == package_route_tbl[i].port) {
            *route_item = &package_route_tbl[i];
            return 0;
        }
    }

    hwlog_err("unknown port: %d in %s.\n", port, __func__);
    dmd_log_report(DSM_SHB_ERR_MAIN_INIT, __func__, "unknown port\n");
    return -EINVAL;

}

int inputhub_route_open(unsigned short port)
{
    int ret;
    char *pos;
    struct inputhub_route_table *route_item;

    hwlog_info("%s\n", __func__);
    ret = inputhub_route_item(port, &route_item);
    if (ret < 0) {
        return -EINVAL;
    }

    if (route_item->phead.pos) {
        hwlog_err("port:%d was already opened in %s.\n", port, __func__);
        return -EINVAL;
    }

    pos = kzalloc(ROUTE_BUFFER_MAX_SIZE, GFP_KERNEL);
    if (!pos) {
        return -ENOMEM;
    }
    route_item->phead.pos = pos;
    route_item->pWrite.pos = pos;
    route_item->pRead.pos = pos;
    route_item->phead.buffer_size = ROUTE_BUFFER_MAX_SIZE;
    route_item->pWrite.buffer_size = ROUTE_BUFFER_MAX_SIZE;
    route_item->pRead.buffer_size = 0;

    return 0;
}
EXPORT_SYMBOL_GPL(inputhub_route_open);

void inputhub_route_close(unsigned short port)
{
    int ret;
    struct inputhub_route_table *route_item;

    hwlog_info( "%s\n", __func__);
    ret = inputhub_route_item(port, &route_item);
    if (ret < 0) {
        return ;
    }

    if (route_item->phead.pos) {
        kfree(route_item->phead.pos);
    }
    route_item->phead.pos =NULL;
    route_item->pWrite.pos =NULL;
    route_item->pRead.pos =NULL;
}
EXPORT_SYMBOL_GPL(inputhub_route_close);

static inline bool data_ready(struct inputhub_route_table *route_item, struct inputhub_buffer_pos *reader)
{
    unsigned long flags = 0;
    spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
    *reader = route_item->pRead;
    spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
    return reader->buffer_size > 0;
}

ssize_t inputhub_route_read(unsigned short port, char __user *buf, size_t count)
{
    struct inputhub_route_table *route_item;
    struct inputhub_buffer_pos reader;
    char *buffer_end;
    int full_pkg_length;
    int tail_half_len;
    unsigned long flags = 0;

    if (inputhub_route_item(port, &route_item) != 0) {
        hwlog_err("inputhub_route_item failed in %s\n", __func__);
        return 0;
    }

    buffer_end = route_item->phead.pos + route_item->phead.buffer_size;

    if (wait_event_interruptible(route_item->read_wait, data_ready(route_item, &reader)) != 0) {//woke up by signal
        return 0;
    }

    if (reader.buffer_size > ROUTE_BUFFER_MAX_SIZE) {
        hwlog_err("error reader.buffer_size = %d in port %d!\n", (int)reader.buffer_size, (int)port);
        dmd_log_report(DSM_SHB_ERR_READ, __func__, "error reader.buffer_size in port\n");
        goto clean_buffer;
    }

    if (buffer_end - reader.pos >= LENGTH_SIZE) {
        full_pkg_length = *((int *)reader.pos);
        reader.pos += LENGTH_SIZE;
        if (reader.pos == buffer_end) {
            reader.pos = route_item->phead.pos;
        }
    } else {
        tail_half_len = buffer_end - reader.pos;
        memcpy(&full_pkg_length, reader.pos, tail_half_len);
        memcpy((char *)&full_pkg_length + tail_half_len, route_item->phead.pos, LENGTH_SIZE - tail_half_len);
        reader.pos = route_item->phead.pos + (LENGTH_SIZE - tail_half_len);
    }

    if (full_pkg_length + LENGTH_SIZE > reader.buffer_size || full_pkg_length > count) {
        hwlog_err("full_pkg_length = %d is too large in port %d!\n", full_pkg_length, (int)port);
        dmd_log_report(DSM_SHB_ERR_READ, __func__, "full_pkg_length is too large in port\n");
        goto clean_buffer;
    }

    if (buffer_end - reader.pos >= full_pkg_length) {
        if (0 == copy_to_user(buf, reader.pos, full_pkg_length)) {
            reader.pos += full_pkg_length;
            if (reader.pos == buffer_end) {
                reader.pos = route_item->phead.pos;
            }
        } else {
            hwlog_err( "copy to user failed\n");
            dmd_log_report(DSM_SHB_ERR_READ, __func__, "copy to user failed\n");
            return 0;
        }
    } else {
        tail_half_len = buffer_end - reader.pos;
        if ((0 == copy_to_user(buf, reader.pos, tail_half_len)) &&
            (0 == copy_to_user(buf + tail_half_len, route_item->phead.pos, (full_pkg_length - tail_half_len)))) {
            reader.pos = route_item->phead.pos + (full_pkg_length - tail_half_len);
        } else {
            hwlog_err( "copy to user failed\n");
            dmd_log_report(DSM_SHB_ERR_READ, __func__, "copy to user failed\n");
            return 0;
        }
    }
    spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
    route_item->pRead.pos = reader.pos;
    route_item->pRead.buffer_size -= (full_pkg_length + LENGTH_SIZE);
    route_item->pWrite.buffer_size += (full_pkg_length + LENGTH_SIZE);
    spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);

    return full_pkg_length;

clean_buffer:
    hwlog_err( "now we will clear the receive buffer in port %d!\n", (int)port);
    spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
    route_item->pRead.pos = route_item->pWrite.pos;
    route_item->pWrite.buffer_size = ROUTE_BUFFER_MAX_SIZE;
    route_item->pRead.buffer_size = 0;
    spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
    return 0;
}
EXPORT_SYMBOL_GPL(inputhub_route_read);

static int64_t getTimestamp(void) {
    struct timespec ts;

    ktime_get_ts(&ts);
    //timevalToNano
    return ts.tv_sec*1000000000LL + ts.tv_nsec;
}

static inline void write_to_fifo(struct inputhub_buffer_pos *pwriter, char *const buffer_begin, char *const buffer_end, char *buf, int count)
{
    int cur_to_tail_len = buffer_end - pwriter->pos;

    if (cur_to_tail_len >= count) {
        memcpy(pwriter->pos, buf, count);
        pwriter->pos += count;
        if (buffer_end == pwriter->pos) {
            pwriter->pos = buffer_begin;
        }
    } else {
        memcpy(pwriter->pos, buf, cur_to_tail_len);
        memcpy(buffer_begin, buf + cur_to_tail_len, count - cur_to_tail_len);
        pwriter->pos = buffer_begin + (count - cur_to_tail_len);
    }
}

t_ap_sensor_ops_record all_ap_sensor_operations[TAG_SENSOR_END] =
{
#ifdef CONFIG_HUAWEI_HALL_INPUTHUB
    [TAG_HALL] =
    {
        .work_on_ap = true,
        .ops = {.enable = hall_first_report},
    },
#endif
};

int register_ap_sensor_operations(int tag, sensor_operation_t *ops)
{
    if (!(TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END)) {
        hwlog_err("tag %d range error in %s\n", tag, __func__);
        return -EINVAL;
    }

    if (!all_ap_sensor_operations[tag].work_on_ap) {
        memcpy(&all_ap_sensor_operations[tag].ops, ops, sizeof(sensor_operation_t));
        all_ap_sensor_operations[tag].work_on_ap = true;
    } else {
        hwlog_warn("tag %d has registered already in %s\n", tag, __func__);
    }

    return 0;
}

int unregister_ap_sensor_operations(int tag)
{
    if (!(TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END)) {
        hwlog_err("tag %d range error in %s\n", tag, __func__);
        return -EINVAL;
    }
    memset(&all_ap_sensor_operations[tag], 0, sizeof(all_ap_sensor_operations[tag]));
    return 0;
}

int report_sensor_event(int tag, int value[], int length)
{
    struct sensor_data event;

    if ((!(TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END)) || (length > sizeof(event.value))) {
        hwlog_err("para error (tag : %d), (length : %d) in %s\n", tag, length, __func__);
        return -EINVAL;
    }

    event.type = tag_to_hal_sensor_type[tag];
    event.length = length;
    memcpy(&event.value, value, length);
    sensor_get_data(&event);
    return inputhub_route_write(ROUTE_SHB_PORT, (char *)&event, event.length + OFFSET_OF_END_MEM(struct sensor_data, length));
}

int ap_hall_report(int value)
{
    return report_sensor_event(TAG_HALL, &value, sizeof(value));
}

bool ap_sensor_enable(int tag, bool enable)
{
    bool work_on_ap = all_ap_sensor_operations[tag].work_on_ap;

    if (work_on_ap) {
        if (all_ap_sensor_operations[tag].ops.enable) {
            all_ap_sensor_operations[tag].ops.enable(enable);
        }
    }

    return work_on_ap;
}

bool ap_sensor_setdelay(int tag, int ms)
{
    bool work_on_ap = all_ap_sensor_operations[tag].work_on_ap;

    if (work_on_ap) {
        if (all_ap_sensor_operations[tag].ops.setdelay) {
            all_ap_sensor_operations[tag].ops.setdelay(ms);
        }
    }

    return work_on_ap;
}

ssize_t inputhub_route_write(unsigned short port, char  *buf, size_t count)
{
    struct inputhub_route_table *route_item;
    struct inputhub_buffer_pos writer;
    char *buffer_begin, *buffer_end;
    t_head header;
    unsigned long flags = 0;

    if (inputhub_route_item(port, &route_item) != 0) {
        hwlog_err("inputhub_route_item failed in %s port = %d!\n", __func__, (int)port);
        return 0;
    }

    header.timestamp = getTimestamp();
    spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
    writer = route_item->pWrite;

    if (writer.buffer_size < count + HEAD_SIZE) {
        spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
        return 0;
    }

    buffer_begin = route_item->phead.pos;
    buffer_end = route_item->phead.pos + route_item->phead.buffer_size;
    header.pkg_length = count + sizeof(int64_t);
    write_to_fifo(&writer, buffer_begin, buffer_end, header.effect_addr, HEAD_SIZE);
    write_to_fifo(&writer, buffer_begin, buffer_end, buf, count);

    route_item->pWrite.pos = writer.pos;
    route_item->pWrite.buffer_size -= (count + HEAD_SIZE);
    route_item->pRead.buffer_size += (count + HEAD_SIZE);
    spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
    atomic_set(&route_item->data_ready, 1);
    wake_up_interruptible(&route_item->read_wait);

    return (count + HEAD_SIZE);
}
EXPORT_SYMBOL_GPL(inputhub_route_write);

struct ipc_debug
{
    int event_cnt[TAG_END];
    int pack_error_cnt;
};
static struct ipc_debug ipc_debug_info;
static void inline clean_ipc_debug_info(void)
{
    memset(&ipc_debug_info, 0, sizeof(ipc_debug_info));
}
static void inline print_ipc_debug_info(void)
{
    int i;
    for (i = TAG_BEGIN; i < TAG_END; ++i) {
        if (ipc_debug_info.event_cnt[i]) {
            hwlog_info("event_cnt[%d]: %d\n", i, ipc_debug_info.event_cnt[i]);
        }
    }
    if (ipc_debug_info.pack_error_cnt) {
        hwlog_err("pack_err_cnt: %d\n", ipc_debug_info.pack_error_cnt);
    }
}

/**begin**/
#define MAX_SEND_LEN (32)
struct link_package {
    int partial_order;
    char link_buffer[MAX_PKT_LENGTH_AP];
    int total_pkg_len;
    int offset;
};
const pkt_header_t *pack(const char *buf, unsigned int length)
{
    const pkt_header_t *head = (const pkt_header_t *)buf;
    static struct link_package linker = {-1};//init partial_order to -1 to aviod lost first pkt

    //try to judge which pkt it is
    if ((TAG_BEGIN <= head->tag && head->tag < TAG_END) && (head->length <= (MAX_PKT_LENGTH_AP - sizeof(pkt_header_t)))) {
        linker.total_pkg_len = head->length + OFFSET_OF_END_MEM(pkt_header_t, length);
        if (linker.total_pkg_len > (int)length) {//need link other partial packages
            linker.partial_order = head->partial_order;//init partial_order
            if (length <= sizeof(linker.link_buffer)) {
                memcpy(linker.link_buffer, buf, length);//save first partial package
                linker.offset = length;
            } else {
                goto error;
            }
            goto receive_next;//receive next partial package
        } else {
            return head;//full pkt
        }
    } else if (TAG_END == head->tag) {//check if partial_order effective
        pkt_part_header_t *partial = (pkt_part_header_t *)buf;
        if (partial->partial_order == (uint8_t)(linker.partial_order + 1)) {//type must keep same with partial->partial_order, because integer promote
            int partial_pkt_data_length = length - sizeof(pkt_part_header_t);
            if (linker.offset + partial_pkt_data_length <= sizeof(linker.link_buffer)) {
                ++linker.partial_order;
                memcpy(linker.link_buffer + linker.offset, buf + sizeof(pkt_part_header_t), partial_pkt_data_length);
                linker.offset += partial_pkt_data_length;
                if (linker.offset >= linker.total_pkg_len) {//link finished
                    return (pkt_header_t *)linker.link_buffer;
                } else {
                    goto receive_next;//receive next partial package
                }
            }
        }
    }

error://clear linker info when error
    ++ipc_debug_info.pack_error_cnt;
    linker.partial_order = -1;
    linker.total_pkg_len = 0;
    linker.offset = 0;
receive_next:
    return NULL;
}

int unpack(const void *buf, unsigned int length)
{
    int ret = 0;
    static int partial_order = 0;

    ((pkt_header_t *)buf)->partial_order = partial_order++;//inc partial_order in header
    if (length <= MAX_SEND_LEN) {
        return inputhub_mcu_send((const char *)buf, length);
    } else {
        char send_partial_buf[MAX_SEND_LEN];
        int send_cnt = 0;

        //send head
        if ((ret = inputhub_mcu_send((const char *)buf, MAX_SEND_LEN)) != 0) {
            return ret;
        }

        ((pkt_part_header_t *)send_partial_buf)->tag = TAG_END;
        for (send_cnt = MAX_SEND_LEN; send_cnt < (int)length; send_cnt += (MAX_SEND_LEN - sizeof(pkt_part_header_t))) {
            ((pkt_part_header_t *)send_partial_buf)->partial_order = partial_order++;//inc partial_order in partial pkt
            memcpy(send_partial_buf + sizeof(pkt_part_header_t), (const char *)buf + send_cnt, MAX_SEND_LEN - sizeof(pkt_part_header_t));
            if ((ret = inputhub_mcu_send(send_partial_buf, MAX_SEND_LEN)) != 0) {
                return ret;
            }
        }
    }

    return 0;
}
/**end**/

struct mcu_event_wait_list
{
	spinlock_t slock;
	struct list_head head;
} mcu_event_wait_list;

static void init_mcu_event_wait_list(void)
{
	INIT_LIST_HEAD(&mcu_event_wait_list.head);
	spin_lock_init(&mcu_event_wait_list.slock);
}

void init_wait_node_add_list(struct mcu_event_waiter *waiter, t_match match, void *out_data, int out_data_len, void *priv)
{
	unsigned long flags = 0;

	waiter->match = match;
	init_completion(&waiter->complete);
	waiter->out_data = out_data;
	waiter->out_data_len = out_data_len;
	waiter->priv = priv;

	spin_lock_irqsave(&mcu_event_wait_list.slock, flags);
	list_add(&waiter->entry, &mcu_event_wait_list.head);
	spin_unlock_irqrestore(&mcu_event_wait_list.slock, flags);
}

void list_del_mcu_event_waiter(struct mcu_event_waiter *self)
{
	unsigned long flags = 0;
	spin_lock_irqsave(&mcu_event_wait_list.slock, flags);
	list_del(&self->entry);
	spin_unlock_irqrestore(&mcu_event_wait_list.slock, flags);
}

static void wake_up_mcu_event_waiter(const pkt_header_t *head)
{
	unsigned long flags = 0;
	struct mcu_event_waiter *pos, *n;

	spin_lock_irqsave(&mcu_event_wait_list.slock, flags);
	list_for_each_entry_safe(pos, n, &mcu_event_wait_list.head, entry) {
		if (pos->match && pos->match(pos->priv, head)) {
			if (pos->out_data != NULL) {
				memcpy(pos->out_data, head, pos->out_data_len);
			}
			complete(&pos->complete);
			//to support diffrent task wait for same event, here we don't break;
		}
	}
	spin_unlock_irqrestore(&mcu_event_wait_list.slock, flags);
}

int inputhub_mcu_write_cmd_nolock(const void *buf, unsigned int length)
{
	int ret = 0;
	pkt_header_t *pkt = (pkt_header_t *)buf;
	((pkt_header_t *)buf) ->resp = RESP;
	if (!WAIT_FOR_MCU_RESP_AFTER_SEND(buf,
										unpack(buf, length),
										2000)) {
		hwlog_err("wait for tag:%s:%d\tcmd:%d resp timeout in %s\n", obj_tag_str[pkt->tag], pkt->tag, pkt->cmd, __func__);
		ret = -1;
	}

	return ret;
}

char* obj_tag_str[] = {
	[TAG_ACCEL] = "TAG_ACCEL",
	[TAG_GYRO] = "TAG_GYRO",
	[TAG_MAG] = "TAG_MAG",
	[TAG_ALS] = "TAG_ALS" ,
	[TAG_PS] = "TAG_PS" ,
	[TAG_SCREEN_ROTATE] = "TAG_SCREEN_ROTATE",
	[TAG_LINEAR_ACCEL] = "TAG_LINEAR_ACCEL",
	[TAG_GRAVITY] = "TAG_GRAVITY",
	[TAG_ORIENTATION] = "TAG_ORIENTATION",
	[TAG_ROTATION_VECTORS] = "TAG_ROTATION_VECTORS" ,
	[TAG_PRESSURE] = "TAG_PRESSURE",
	[TAG_TEMP] = "TAG_TEMP",
	[TAG_HUMIDITY] = "TAG_HUMIDITY",
	[TAG_AMBIENT_TEMP] = "TAG_AMBIENT_TEMP",
	[TAG_LABC] = "TAG_LABC",
	[TAG_HALL] = "TAG_HALL",
	[TAG_MAG_UNCALIBRATED] = "TAG_MAG_UNCALIBRATED",
	[TAG_GAME_RV] = "TAG_GAME_RV",
	[TAG_GYRO_UNCALIBRATED] = "TAG_GYRO_UNCALIBRATED",
	[TAG_SIGNIFICANT_MOTION] = "TAG_SIGNIFICANT_MOTION",
	[TAG_STEP_DETECTOR] = "TAG_STEP_DETECTOR",
	[TAG_STEP_COUNTER] = "TAG_STEP_COUNTER",
	[TAG_GEOMAGNETIC_RV] = "TAG_GEOMAGNETIC_RV",
	[TAG_HANDPRESS] = "TAG_HANDPRESS",
	[TAG_CAP_PROX] = "TAG_CAP_PROX",
	[TAG_TP] = "TAG_TP",
	[TAG_SPI] = "TAG_SPI",
	[TAG_I2C] = "TAG_I2C",
	[TAG_RGBLIGHT] = "TAG_RGBLIGHT",
	[TAG_BUTTONLIGHT] = "TAG_BUTTONLIGHT",
	[TAG_BACKLIGHT] = "TAG_BACKLIGHT",
	[TAG_VIBRATOR] = "TAG_VIBRATOR",
	[TAG_SYS] = "TAG_SYS",
	[TAG_LOG] = "TAG_LOG",
	[TAG_MOTION] = "TAG_MOTION",
	[TAG_CURRENT] = "TAG_CURRENT",
	[TAG_FAULT] = "TAG_FAULT",
	[TAG_END] = "TAG_END",
};
static int inputhub_sensor_enable_internal_nolock(int tag, bool enable, close_param_t *param)
{
    if (NULL == param) {
        hwlog_err("NULL pointer param in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "NULL pointer param\n");
        return -EINVAL;
    }

    if (ap_sensor_enable(tag, enable)) {
        return 0;
    }

    if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
        if (enable) {
            pkt_header_t pkt = {
                .tag = tag,
                .cmd = CMD_CMN_OPEN_REQ,
                .resp = NO_RESP,
                .length = 0
            };

            hwlog_info("open sensor %s!\n", obj_tag_str[tag]);
            return inputhub_mcu_write_cmd_nolock(&pkt, sizeof(pkt));
        } else {
            pkt_cmn_close_req_t pkt;
            memset(&pkt, 0, sizeof(pkt));
            pkt.hd.tag = tag;
            pkt.hd.cmd = CMD_CMN_CLOSE_REQ;
            pkt.hd.resp = NO_RESP;
            pkt.hd.length = sizeof(close_param_t);
            memcpy(&pkt.close_param, param, sizeof(pkt.close_param));

            hwlog_info("close sensor %s!\n", obj_tag_str[tag]);
            return inputhub_mcu_write_cmd_nolock(&pkt, sizeof(pkt));
        }
    } else {
        hwlog_err("unknown sensor type in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "unknown sensor type\n");
        return -EINVAL;
    }
}
static inline int send_app_config_cmd(int tag, void *app_config, bool use_lock)
{
    pkt_cmn_interval_req_t i_pkt;

    i_pkt.hd.tag = tag;
    i_pkt.hd.cmd = CMD_CMN_CONFIG_REQ;
    i_pkt.hd.resp = NO_RESP;
    i_pkt.hd.length = sizeof(i_pkt.app_config);
    memcpy(i_pkt.app_config, app_config, sizeof(i_pkt.app_config));

    if (use_lock) {
        return inputhub_mcu_write_cmd_adapter(&i_pkt, sizeof(i_pkt), NULL);
    } else {
        return inputhub_mcu_write_cmd_nolock(&i_pkt, sizeof(i_pkt));
    }
}
static int inputhub_sensor_setdelay_internal_nolock(int tag, open_param_t *param)
{
    if (NULL == param) {
        hwlog_err("NULL pointer param in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "NULL pointer param\n");
        return -EINVAL;
    }

    if (ap_sensor_setdelay(tag, param->period)) {
        return 0;
    }

    if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
        pkt_cmn_interval_req_t pkt;
        memset(&pkt, 0, sizeof(pkt));
        pkt.hd.tag = tag;
        pkt.hd.cmd = CMD_CMN_INTERVAL_REQ;
        pkt.hd.resp = NO_RESP;
        pkt.hd.length = sizeof(open_param_t);
        memcpy(&pkt.param, param, sizeof(pkt.param));
        hwlog_info("set sensor %s delay %d ms!\n", obj_tag_str[pkt.hd.tag], param->period);
        return inputhub_mcu_write_cmd_nolock(&pkt, sizeof(pkt));
    } else {
        hwlog_err("unknown sensor type in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "unknown sensor type\n");
        return -EINVAL;
    }
}

static bool motion_status[MOTION_TYPE_END];
static int motion_ref_cnt;
static void update_motion_info(obj_cmd_t cmd, motion_type_t type)
{
    if (!(MOTION_TYPE_START <= type && type < MOTION_TYPE_END)) {
        return;
    }

    switch (cmd) {
        case CMD_CMN_OPEN_REQ:
            motion_status[type] = true;
            break;

        case CMD_CMN_CLOSE_REQ:
            motion_status[type] = false;
            break;

        default:
            hwlog_err("unknown cmd type in %s\n", __func__);
            dmd_log_report(DSM_SHB_ERR_CMD, __func__, "unknown cmd type\n");
            break;
    }
}


extern int send_motion_cmd_internal(int tag, obj_cmd_t cmd, motion_type_t type, bool use_lock);
static int extend_step_counter_process_nolock(bool enable)
{
    close_param_t extend_close_param;
    memset(&extend_close_param, 0, sizeof(extend_close_param));
    extend_close_param.reserved[0] = TYPE_EXTEND;
    uint8_t app_config[] = {enable, TYPE_EXTEND};
    //close step counter
    if (!enable) {
        send_app_config_cmd(TAG_STEP_COUNTER, app_config, false);
    }
    hwlog_info("%s extend_step_counte!\n", enable ? "open" : "close");
    if (really_do_enable_disable(&step_ref_cnt, enable)) {
        inputhub_sensor_enable_internal_nolock(TAG_STEP_COUNTER, enable, &extend_close_param);
    }
    if (enable) {
        open_param_t extend_open_param = {
            .period = 20,//default delay_ms
            .batch_count = 1,
            .mode = AUTO_MODE,
            .reserved[0] = TYPE_EXTEND
        };
        inputhub_sensor_setdelay_internal_nolock(TAG_STEP_COUNTER, &extend_open_param);
        return send_app_config_cmd(TAG_STEP_COUNTER, app_config, false);
    }
    return 0;
}
static void enable_motions_when_recovery_iom3(void)
{
    motion_type_t type;
    //save step count when iom3 recovery
    recovery_step_count = valid_step_count;
    motion_ref_cnt = 0;//to send open motion cmd when open first type
    for (type = MOTION_TYPE_START; type < MOTION_TYPE_END; ++type) {
        if (motion_status[type]) {
            hwlog_info("motion state %d in %s\n", type, __func__);
            send_motion_cmd_internal(TAG_MOTION, CMD_CMN_OPEN_REQ, type, false);
        }
    }
}

static void disable_motions_when_sysreboot(void)
{
    motion_type_t type;
    for (type = MOTION_TYPE_START; type < MOTION_TYPE_END; ++type) {
        if (motion_status[type]) {
            hwlog_info("motion state %d in %s\n", type, __func__);
            send_motion_cmd_internal(TAG_MOTION, CMD_CMN_CLOSE_REQ, type, false);
        }
    }
}

void operations_when_recovery_iom3(void)
{
    hwlog_info("operations_when_recovery_iom3!\n");
    //reset sensor calibrate when first
    reset_calibrate_when_recovery_iom3();

    //recovery sensor
    enable_sensors_when_recovery_iom3();
    msleep(100);

    //recovery motion
    enable_motions_when_recovery_iom3();
}

static bool is_extend_step_counter_cmd(const pkt_header_t *pkt)
{
    bool ret = false;

    if (pkt->tag != TAG_STEP_COUNTER) {
        return false;
    }

    switch (pkt->cmd) {
        case CMD_CMN_OPEN_REQ:
            //could not judge which type step counter in open protocol
            break;

        case CMD_CMN_CLOSE_REQ:
            ret = (TYPE_EXTEND == ((pkt_cmn_close_req_t *)pkt)->close_param.reserved[0]);
            break;

        case CMD_CMN_INTERVAL_REQ:
            ret = (TYPE_EXTEND == ((pkt_cmn_interval_req_t *)pkt)->param.reserved[0]);
            break;

        default:
            break;
    }

    return ret;
}

int inputhub_sensor_enable_nolock(int tag, bool enable)
{
    close_param_t default_close_prama;
    memset(&default_close_prama, 0, sizeof(default_close_prama));
    default_close_prama.reserved[0] = TYPE_STANDARD;//for step counter
    return inputhub_sensor_enable_internal_nolock(tag, enable, &default_close_prama);
}

int inputhub_sensor_setdelay_nolock(int tag, int delay_ms)
{
    open_param_t default_open_param = {
        .period = delay_ms,
        .batch_count = 1,
        .mode = AUTO_MODE,
        .reserved[0] = TYPE_STANDARD//for step counter only
    };
    return inputhub_sensor_setdelay_internal_nolock(tag, &default_open_param);
}

static uint16_t tranid = 0;
int inputhub_mcu_write_cmd(const void *buf, unsigned int length)
{
#ifdef CONFIG_IOM3_RECOVERY
    bool is_in_recovery = false;
#endif

    int ret = 0;

    if (length > MAX_PKT_LENGTH) {
        hwlog_err("length = %d is too large in %s\n", (int)length, __func__);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "length is too large\n");
        return -EINVAL;
    }

    mutex_lock(&mutex_write_cmd);
#ifdef CONFIG_IOM3_RECOVERY
    if(g_iom3_state == IOM3_ST_NORMAL){//false - send direct
    }else if(g_iom3_state == IOM3_ST_RECOVERY){//true - only update
	is_in_recovery = true;
    }else if(g_iom3_state == IOM3_ST_REPEAT){//IOM3_ST_REPEAT...BLOCK IN HERE, WAIT FOR REPEAT COMPLETE
	hwlog_err("wait for iom3 recovery complete\n");
	mutex_unlock(&mutex_write_cmd);
	wait_event(iom3_rec_wq, (g_iom3_state == IOM3_ST_NORMAL));
	hwlog_err("wakeup for iom3 recovery complete\n");
	mutex_lock(&mutex_write_cmd);
    }else{
	hwlog_err("unknown iom3 state %d\n", g_iom3_state);
    }
    if (true == is_in_recovery){
        mutex_unlock(&mutex_write_cmd);
        goto update_info;
    }
#endif

    ((pkt_header_t *)buf)->tranid = tranid++;
    ret = unpack(buf, length);
    mutex_unlock(&mutex_write_cmd);

update_info:
    if ((TAG_SENSOR_BEGIN <= ((pkt_header_t *)buf)->tag && ((pkt_header_t *)buf)->tag < TAG_SENSOR_END)) {
        if (!is_extend_step_counter_cmd(((const pkt_header_t *)buf))) {
            update_sensor_info(((const pkt_header_t *)buf));
        }
    }

    if(ret) {
#ifdef CONFIG_HISI_BB
	rdr_system_error(SENSORHUB_MODID, 0, 0);
#elif defined CONFIG_IOM3_RECOVERY
	if(false == is_in_recovery)
	iom3_need_recovery();
#else
	restart_iom3();
#endif
    }

    return 0;
}

struct motions_cmd_map {
    int         mhb_ioctl_app_cmd;
    int         motion_type;
    int         tag;
    obj_cmd_t cmd;
};
static const struct motions_cmd_map motions_cmd_map_tab[] = {
    {MHB_IOCTL_MOTION_START, -1,  TAG_MOTION, CMD_CMN_OPEN_REQ},
    {MHB_IOCTL_MOTION_STOP,   -1,  TAG_MOTION, CMD_CMN_CLOSE_REQ},
    {MHB_IOCTL_MOTION_ATTR_START,-1, TAG_MOTION, CMD_MOTION_ATTR_ENABLE_REQ},
    {MHB_IOCTL_MOTION_ATTR_STOP,  -1, TAG_MOTION, CMD_MOTION_ATTR_DISABLE_REQ},
    {MHB_IOCTL_MOTION_INTERVAL_SET, -1, TAG_MOTION, CMD_MOTION_INTERVAL_REQ},
};

static bool is_motion_data_report(const pkt_header_t *head)
{
    //all sensors report data with command CMD_PRIVATE
    return (head->tag == TAG_MOTION) && (CMD_MOTION_REPORT_REQ== head->cmd);
}

static int inputhub_sensor_enable_internal(int tag, bool enable, close_param_t *param)
{
	if (NULL == param) {
		hwlog_err("NULL pointer param in %s\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CMD, __func__, "NULL pointer param\n");
		return -EINVAL;
	}

	if (ap_sensor_enable(tag, enable)) {
		return 0;
	}

	if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
		if (enable) {
			pkt_header_t pkt = (pkt_header_t){
				.tag = tag,
				.cmd = CMD_CMN_OPEN_REQ,
				.resp = NO_RESP,
				.length = 0
			};

			hwlog_info("open sensor %s (tag:%d)!\n", obj_tag_str[tag] ? obj_tag_str[tag] : "TAG_UNKNOWN", tag);
			return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
		} else {
			pkt_cmn_close_req_t pkt;
			memset(&pkt, 0, sizeof(pkt));
			pkt.hd.tag = tag;
			pkt.hd.cmd = CMD_CMN_CLOSE_REQ;
			pkt.hd.resp = NO_RESP;
			pkt.hd.length = sizeof(close_param_t);
			memcpy(&pkt.close_param, param, sizeof(pkt.close_param));

			hwlog_info("close sensor %s (tag:%d)!\n", obj_tag_str[tag] ? obj_tag_str[tag] : "TAG_UNKNOWN", tag);
			return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
		}
	} else {
		hwlog_err("unknown sensor type in %s\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CMD, __func__, "unknown sensor type\n");
		return -EINVAL;
	}
}

static int inputhub_sensor_setdelay_internal(int tag, open_param_t *param)
{
	pkt_cmn_interval_req_t pkt;

	if (NULL == param) {
		hwlog_err("NULL pointer param in %s\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CMD, __func__, "NULL pointer param\n");
		return -EINVAL;
	}

	if (ap_sensor_setdelay(tag, param->period)) {
		return 0;
	}

	if (tag == TAG_LABC) {
		int labc_data[3];
		labc_data[0] = -1;
		labc_data[1] = -1;
		labc_data[2] = -1;
		report_sensor_event(TAG_LABC, labc_data, sizeof(labc_data));
	}

	if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
		memset(&pkt, 0, sizeof(pkt));
		pkt.hd.tag = tag;
		pkt.hd.cmd = CMD_CMN_INTERVAL_REQ;
		pkt.hd.resp = NO_RESP;
		pkt.hd.length = sizeof(open_param_t);
		memcpy(&pkt.param, param, sizeof(pkt.param));
		hwlog_info("set sensor %s (tag:%d) delay %d ms!\n", obj_tag_str[tag] ? obj_tag_str[tag] : "TAG_UNKNOWN", tag, param->period);
		return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
	} else {
		hwlog_err("unknown sensor type in %s\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CMD, __func__, "unknown sensor type\n");
		return -EINVAL;
	}
}

static int extend_step_counter_process(bool enable)
{
    close_param_t extend_close_param;
    memset(&extend_close_param, 0, sizeof(extend_close_param));
    extend_close_param.reserved[0] = TYPE_EXTEND;
    uint8_t app_config[] = {enable, TYPE_EXTEND};
    hwlog_info("%s extend_step_counte!\n", enable ? "open" : "close");
    //close step counter
    if (!enable) {
        send_app_config_cmd(TAG_STEP_COUNTER, app_config, true);
    }
    if (really_do_enable_disable(&step_ref_cnt, enable)) {
        inputhub_sensor_enable_internal(TAG_STEP_COUNTER, enable, &extend_close_param);
    }
    if (enable) {
        open_param_t extend_open_param = {
            .period = 20,//default delay_ms
            .batch_count = 1,
            .mode = AUTO_MODE,
            .reserved[0] = TYPE_EXTEND
        };

        inputhub_sensor_setdelay_internal(TAG_STEP_COUNTER, &extend_open_param);
        return send_app_config_cmd(TAG_STEP_COUNTER, app_config, true);
    }
    return 0;
}

char * motion_type_str[] = {
	[MOTION_TYPE_START] = "start",
	[MOTION_TYPE_PICKUP] = "pickup",
	[MOTION_TYPE_FLIP] = "flip",
	[MOTION_TYPE_PROXIMITY] = "proximity",
	[MOTION_TYPE_SHAKE] = "shake",
	[MOTION_TYPE_TAP] = "tap",
	[MOTION_TYPE_TILT_LR] = "tilt_lr",
	[MOTION_TYPE_ROTATION] = "rotation",
	[MOTION_TYPE_POCKET] = "pocket",
	[MOTION_TYPE_ACTIVITY] = "activity",
	[MOTION_TYPE_TAKE_OFF] = "take_off",
	[MOTION_TYPE_EXTEND_STEP_COUNTER] = "ext_step_counter",
	[MOTION_TYPE_END] = "end",
};

int send_motion_cmd_internal(int tag, obj_cmd_t cmd, motion_type_t type, bool use_lock)
{
    pkt_header_t hpkt;
    pkt_cmn_interval_req_t i_pkt;
    pkt_cmn_close_req_t c_pkt;
    uint8_t app_config[] = {type, cmd};
    memset(&i_pkt, 0, sizeof(i_pkt));
    memset(&c_pkt, 0, sizeof(c_pkt));
    update_motion_info(cmd, type);

    if (MOTIONHUB_TYPE_HW_STEP_COUNTER == type) {
        if (CMD_CMN_OPEN_REQ == cmd || CMD_CMN_CLOSE_REQ == cmd) {
            if (use_lock) {
                return extend_step_counter_process(CMD_CMN_OPEN_REQ == cmd);
            } else {
                return extend_step_counter_process_nolock(CMD_CMN_OPEN_REQ == cmd);
            }
        }
    }

    if (CMD_CMN_OPEN_REQ == cmd) {
        //send open motion cmd when open first sub type
        if (really_do_enable_disable(&motion_ref_cnt, true)) {
            hpkt.tag = tag;
            hpkt.cmd = cmd;
            hpkt.resp = NO_RESP;
            hpkt.length = 0;
            if (use_lock) {
                inputhub_mcu_write_cmd_adapter(&hpkt, sizeof(hpkt), NULL);
            } else {
                inputhub_mcu_write_cmd_nolock(&hpkt, sizeof(hpkt));
            }

            i_pkt.hd.tag = tag;
            i_pkt.hd.cmd = CMD_CMN_INTERVAL_REQ;
            i_pkt.hd.resp = NO_RESP;
            i_pkt.hd.length = sizeof(i_pkt.param);
           // i_pkt.param.reserved[0] = type;

            if (likely((type > MOTION_TYPE_START)&&(type < MOTION_TYPE_END))){
                hwlog_info("send_motion_cmd cmd:%d motion: %s !", cmd, motion_type_str[type]);
            }else{
                hwlog_info("send_motion_cmd cmd:%d motion: %d !", cmd, type);
            }
            if (use_lock) {
                inputhub_mcu_write_cmd_adapter(&i_pkt, sizeof(i_pkt), NULL);
            } else {
                inputhub_mcu_write_cmd_nolock(&i_pkt, sizeof(i_pkt));
            }
        }
        //send config cmd to open motion type
        send_app_config_cmd(TAG_MOTION, app_config, use_lock);

    } else if ( CMD_CMN_CLOSE_REQ == cmd) {
        //send config cmd to close motion type
        send_app_config_cmd(TAG_MOTION, app_config, use_lock);

        //send close motion cmd when all sub type closed
        if (really_do_enable_disable(&motion_ref_cnt, false)) {
            c_pkt.hd.tag = tag;
            c_pkt.hd.cmd = cmd;
            c_pkt.hd.resp = NO_RESP;
            c_pkt.hd.length = sizeof(c_pkt.close_param);
            //c_pkt.close_param.reserved[0] = type;

            if (likely((type > MOTION_TYPE_START)&&(type < MOTION_TYPE_END))){
                hwlog_info("send_motion_cmd cmd:%d motion: %s !", cmd, motion_type_str[type]);
            }else{
                hwlog_info("send_motion_cmd cmd:%d motion: %d !", cmd, type);
            }
            if (use_lock) {
                inputhub_mcu_write_cmd_adapter(&c_pkt, sizeof(c_pkt), NULL);
            } else {
                inputhub_mcu_write_cmd_nolock(&c_pkt, sizeof(c_pkt));
            }
        }
    } else if (CMD_MOTION_ATTR_ENABLE_REQ == cmd ||CMD_MOTION_ATTR_DISABLE_REQ == cmd) {
        hwlog_err("send_motion_cmd cmd:%d!", cmd);
    } else if (CMD_MOTION_INTERVAL_REQ == cmd) {
        hwlog_err("send_motion_cmd cmd:%d!", cmd);
    } else {
        hwlog_err("send_motion_cmd unknown cmd!\n");
        return -EINVAL;
    }

    return 0;
}

int send_motion_cmd(unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    int argvalue = 0;
    int i;

    for (i = 0; i < sizeof(motions_cmd_map_tab) / sizeof(motions_cmd_map_tab[0]); ++i) {
        if (motions_cmd_map_tab[i].mhb_ioctl_app_cmd == cmd) {
            break;
        }
    }

    if (sizeof(motions_cmd_map_tab) / sizeof(motions_cmd_map_tab[0]) == i) {
        hwlog_err("send_motion_cmd unknown cmd %d in parse_motion_cmd!\n", cmd);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "send_motion_cmd unknown cmd in parse_motion_cmd!\n");
        return -EFAULT;
    }

    if (copy_from_user(&argvalue, argp, sizeof(argvalue))) {
        return -EFAULT;
    }

    return send_motion_cmd_internal(motions_cmd_map_tab[i].tag, motions_cmd_map_tab[i].cmd, argvalue, true);
}

int send_apr_log(void)
{
    char cmd[256];
    char time_buf[16];
    int ret = 0;

    get_time_stamp(time_buf,16);
    snprintf(cmd, 256, "%s%s%s",
        "archive -i /data/android_logs/kmsgcat-log -i /data/android_logs/kmsgcat-log.1 -i /data/android_logs/applogcat-log "
                 "-i /data/android_logs/applogcat-log.1 -i /data/rdr/dump_00.bin -i /data/rdr/dump_01.bin -i /data/rdr/dump_02.bin -o ",
                 time_buf, "_sensorhubErr -z zip");
    ret = log_to_exception("sensorhub", cmd);
    if(ret < 0 )
        hwlog_err("logexception sysfs err.\n");
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "logexception sysfs err\n");
    return ret;
}

int inputhub_sensor_enable(int tag, bool enable)
{
    close_param_t default_close_prama;
    memset(&default_close_prama, 0, sizeof(default_close_prama));
    default_close_prama.reserved[0] = TYPE_STANDARD;//for step counter
    if (tag == TAG_STEP_COUNTER) {
        hwlog_info("TAG_STEP_COUNTER %d, enabe:d% in %s!\n", tag, enable,__func__);
        if (!enable) {
            uint8_t app_config[] = {enable, TYPE_STANDARD};
            send_app_config_cmd(TAG_STEP_COUNTER, app_config, true);
            if(really_do_enable_disable(&step_ref_cnt, enable))
                return inputhub_sensor_enable_internal(tag, enable, &default_close_prama);
        } else {
            hwlog_info(" TAG_STEP_COUNTER %d, enabe:d% in %s!\n", tag, enable,__func__);
            if (really_do_enable_disable(&step_ref_cnt, enable)) {
                return inputhub_sensor_enable_internal(tag, enable, &default_close_prama);
            }
        }
   }
   else
      return inputhub_sensor_enable_internal(tag, enable, &default_close_prama);
}

int inputhub_sensor_setdelay(int tag, int delay_ms)
{
    open_param_t default_open_param = {
        .period = delay_ms,
        .batch_count = 1,
        .mode = AUTO_MODE,
        .reserved[0] = TYPE_STANDARD//for step counter only
    };
    return inputhub_sensor_setdelay_internal(tag, &default_open_param);
}

static int send_sensor_cmd(unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    int tag = 0;
    struct ioctl_para para;

    if (copy_from_user(&para, argp, sizeof(para))) {
        return -EFAULT;
    }

    if (!(SENSORHUB_TYPE_BEGIN <= para.shbtype && para.shbtype < SENSORHUB_TYPE_END)) {
        hwlog_err("error shbtype %d in %s\n", para.shbtype, __func__);
        return -EINVAL;
    }

    tag = hal_sensor_type_to_tag[para.shbtype];
    switch (cmd) {
    case SHB_IOCTL_APP_ENABLE_SENSOR:
    case SHB_IOCTL_APP_DISABLE_SENSOR:
        return inputhub_sensor_enable(tag, SHB_IOCTL_APP_ENABLE_SENSOR == cmd);
        break;

    case SHB_IOCTL_APP_DELAY_SENSOR:
        if (tag == TAG_STEP_COUNTER) {
            inputhub_sensor_setdelay(tag, para.delay_ms);
            uint8_t app_config[] = {1, TYPE_STANDARD};
            return send_app_config_cmd(TAG_STEP_COUNTER, app_config, true);
        } else {
           return inputhub_sensor_setdelay(tag, para.delay_ms);
        }

        break;

    default:
        hwlog_err("unknown shb_hal_cmd %d in %s!\n", cmd, __func__);
        return -EINVAL;
    }

    return 0;
}

static bool cmd_match(int req, int resp)
{
    return (req + 1) == resp;
}

/*use lock for all command to avoid conflict*/
int inputhub_mcu_write_cmd_adapter(const void *buf, unsigned int length, struct read_info *rd)
{
	int ret = 0;
	unsigned long flags = 0;
	int retry_count = 2;

	mutex_lock(&mutex_write_adapter);

	if (NULL == rd) {
		ret = inputhub_mcu_write_cmd(buf, length);
	} else {
		mutex_lock(&type_record.lock_mutex);
		spin_lock_irqsave(&type_record.lock_spin, flags);
		type_record.pkt_info = ((pkt_header_t *)buf);
		type_record.rd = rd;
		spin_unlock_irqrestore(&type_record.lock_spin, flags);
		while(retry_count--){//send retry 3 times
			//send data to mcu
			INIT_COMPLETION(type_record.resp_complete);
			if (inputhub_mcu_write_cmd(buf, length)){
				hwlog_err("send cmd to mcu failed in %s, retry %d\n", __func__, retry_count);
			}else if (!wait_for_completion_timeout(&type_record.resp_complete, msecs_to_jiffies(iom3_timeout))) {
				hwlog_err("wait for response timeout in %s, retry %d. tag %d cmd %d\n", __func__, retry_count,((pkt_header_t*)buf)->tag, ((pkt_header_t*)buf)->cmd);
				if (retry_count == 0) {
			#ifdef CONFIG_HISI_BB
					rdr_system_error(SENSORHUB_MODID, 0, 0);
			#elif defined CONFIG_IOM3_RECOVERY
        				iom3_need_recovery();
			#else
					restart_iom3();
			#endif
				}
				if(!dsm_client_ocuppy(shb_dclient)){
					dsm_client_record(shb_dclient, "Command tag - %d, cmd - %d\n", ((pkt_header_t*)buf)->tag, ((pkt_header_t*)buf)->cmd);
					dsm_client_notify(shb_dclient, DSM_SHB_ERR_IPC_TIMEOUT);
				}
			}else{
				ret = 0;//send success & response success
				break;
			}

			msleep(5000);//send or response fail, recovery working, wait 5 sec & retry
		}

		//clear infor
		spin_lock_irqsave(&type_record.lock_spin, flags);
		type_record.pkt_info = NULL;
		type_record.rd = NULL;
		spin_unlock_irqrestore(&type_record.lock_spin, flags);
		mutex_unlock(&type_record.lock_mutex);
	}

	mutex_unlock(&mutex_write_adapter);

	return ret;
}

int write_customize_cmd(const struct write_info *wr, struct read_info *rd)
{
    char buf[MAX_PKT_LENGTH];

    if (NULL == wr) {
        hwlog_err("NULL pointer in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "NULL pointer\n");
        return -EINVAL;
    }
    //[TAG_BEGIN, TAG_END)
    if (wr->tag < TAG_BEGIN || wr->tag >= TAG_END) {
        hwlog_err("tag = %d error in %s\n", wr->tag, __func__);
		dmd_log_report(DSM_SHB_ERR_CMD, __func__, "tag error\n");
        return -EINVAL;
    }
    if (wr->wr_len + sizeof(pkt_header_t) > MAX_PKT_LENGTH) {
        hwlog_err("-----------> wr_len = %d is too large in %s\n", wr->wr_len, __func__);
        dmd_log_report(DSM_SHB_ERR_CMD, __func__, "-------> write length is too large\n");
        return -EINVAL;
    }
    memset(&buf, 0, sizeof(buf));
    ((pkt_header_t *)buf)->tag = wr->tag;
    ((pkt_header_t *)buf)->cmd = wr->cmd;
    ((pkt_header_t *)buf)->resp = ((rd != NULL) ? (RESP) : (NO_RESP));
    ((pkt_header_t *)buf)->length = wr->wr_len;
    if (wr->wr_buf != NULL) {
        memcpy(buf + sizeof(pkt_header_t), wr->wr_buf, wr->wr_len);
    }

    return inputhub_mcu_write_cmd_adapter(buf, sizeof(pkt_header_t) + wr->wr_len, rd);
}

static bool is_sensor_data_report(const pkt_header_t *head)
{
    //all sensors report data with command CMD_PRIVATE
    return (TAG_SENSOR_BEGIN <= head->tag && head->tag < TAG_SENSOR_END) && (CMD_PRIVATE == head->cmd);
}

static bool is_requirement_resp(const pkt_header_t *head)
{
    return (0 == (head->cmd & 1));//even cmds are resp cmd
}

static int report_resp_data(const pkt_header_resp_t *head)
{
    int ret = 0;
    unsigned long flags = 0;

    spin_lock_irqsave(&type_record.lock_spin, flags);
    if (type_record.rd != NULL && type_record.pkt_info != NULL//check record info
        && (cmd_match(type_record.pkt_info->cmd, head->cmd))
        && (type_record.pkt_info->tranid == head->tranid)) {//rcv resp from mcu
        if (head->length <= (MAX_PKT_LENGTH + sizeof(head->errno))) {//data length ok
            type_record.rd->errno = head->errno;//fill errno to app
            type_record.rd->data_length = (head->length - sizeof(head->errno));//fill data_length to app, data_length means data lenght below
            memcpy(type_record.rd->data, (char *)head + sizeof(pkt_header_resp_t), type_record.rd->data_length);//fill resp data to app
        } else {//resp data too large
            type_record.rd->errno = -EINVAL;
            type_record.rd->data_length = 0;
            hwlog_err("data too large from mcu in %s\n", __func__);
            dmd_log_report(DSM_SHB_ERR_IOM3_OTHER, __func__, "data too large from mcu\n");
        }
        complete(&type_record.resp_complete);
    }
    spin_unlock_irqrestore(&type_record.lock_spin, flags);

    return ret;
}

struct mcu_notifier_work
{
    struct work_struct worker;
    void *data;
};

struct mcu_notifier_node
{
    int tag;
    int cmd;
    int (*notify)(const pkt_header_t *data);
    struct list_head entry;
};

struct mcu_notifier
{
    struct list_head head;
    spinlock_t lock;
    struct workqueue_struct *mcu_notifier_wq;
};

static struct mcu_notifier mcu_notifier = {LIST_HEAD_INIT(mcu_notifier.head)};
static void init_mcu_notifier_list(void)
{
    INIT_LIST_HEAD(&mcu_notifier.head);
    spin_lock_init(&mcu_notifier.lock);
    mcu_notifier.mcu_notifier_wq = create_singlethread_workqueue("mcu_event_notifier");
}

static void mcu_notifier_handler(struct work_struct *work)
{
    //find data according work
    struct mcu_notifier_work *p = container_of(work, struct mcu_notifier_work, worker);

    //search mcu_notifier, call all call_backs
    struct mcu_notifier_node *pos, *n;
    list_for_each_entry_safe(pos, n, &mcu_notifier.head, entry) {
        if ((pos->tag == ((const pkt_header_t *)p->data)->tag) && (pos->cmd == ((const pkt_header_t *)p->data)->cmd)) {
            if (pos->notify != NULL) {
                pos->notify((const pkt_header_t *)p->data);
            }
        }
    }

    kfree(p->data);
    kfree(p);
}

static const void *avoid_coverity_p_work;
static const void *avoid_coverity_p_void;
static void mcu_notifier_queue_work(const pkt_header_t *head)
{
    struct mcu_notifier_work *notifier_work = kmalloc(sizeof(struct mcu_notifier_work), GFP_ATOMIC);
    if (NULL == notifier_work) {
        return;
    }
    notifier_work->data = kmalloc(head->length + sizeof(pkt_header_t), GFP_ATOMIC);
    if (NULL == notifier_work->data) {
        kfree(notifier_work);
        return;
    }

    memcpy(notifier_work->data, head, sizeof(pkt_header_t) + head->length);
    INIT_WORK(&notifier_work->worker, mcu_notifier_handler);
    queue_work(mcu_notifier.mcu_notifier_wq, &notifier_work->worker);

    /**begin: save alloc ptr, just to solve coverity warning**/
    avoid_coverity_p_work = notifier_work;
    avoid_coverity_p_void = notifier_work->data;
    /**end: save alloc ptr, just to solve coverity warning**/
}

static bool is_mcu_notifier(const pkt_header_t *head)
{
    struct mcu_notifier_node *pos, *n;
    list_for_each_entry_safe(pos, n, &mcu_notifier.head, entry) {
        if ((pos->tag == head->tag) && (pos->cmd == head->cmd)) {
            return true;
        }
    }

    return false;
}

int register_mcu_event_notifier(int tag, int cmd, int (*notify)(const pkt_header_t *head))
{
    struct mcu_notifier_node *pnode, *n;
    int ret = 0;
    unsigned long flags = 0;

    if ((!(TAG_BEGIN <= tag && tag < TAG_END)) || (NULL == notify)) {
        return -EINVAL;
    }

    spin_lock_irqsave(&mcu_notifier.lock, flags);
    //avoid regist more than once
    list_for_each_entry_safe(pnode, n, &mcu_notifier.head, entry) {
        if ((tag == pnode->tag) && (cmd == pnode->cmd) && (notify == pnode->notify)) {
            hwlog_warn("tag = %d, cmd = %d, notify = %pf has already registed in %s\n!", tag, cmd, notify, __func__);
            goto out;//return when already registed
        }
    }

    //make mcu_notifier_node
    pnode = kmalloc(sizeof(struct mcu_notifier_node), GFP_ATOMIC);
    if (NULL == pnode) {
        ret = -ENOMEM;
        goto out;
    }
    pnode->tag = tag;
    pnode->cmd = cmd;
    pnode->notify = notify;

    //add to list
    list_add(&pnode->entry, &mcu_notifier.head);
out:
    spin_unlock_irqrestore(&mcu_notifier.lock, flags);
    /**begin: save alloc ptr, just to solve coverity warning**/
    avoid_coverity_p_void = pnode;
    /**end: save alloc ptr, just to solve coverity warning**/

    return ret;
}

int unregister_mcu_event_notifier(int tag, int cmd, int (*notify)(const pkt_header_t *head))
{
    struct mcu_notifier_node *pos, *n;
    unsigned long flags = 0;

    if ((!(TAG_BEGIN <= tag && tag < TAG_END)) || (NULL == notify)) {
        return -EINVAL;
    }

    spin_lock_irqsave(&mcu_notifier.lock, flags);
    list_for_each_entry_safe(pos, n, &mcu_notifier.head, entry) {
        if ((tag == pos->tag) && (cmd == pos->cmd) && (notify == pos->notify)) {
            list_del(&pos->entry);
            kfree(pos);
            break;
        }
    }
    spin_unlock_irqrestore(&mcu_notifier.lock, flags);

    return 0;
}

static void step_counter_data_process(pkt_step_counter_data_req_t *head)
{
    int standard_data_len = sizeof(head->step_count);
    if ((head->record_count > 0) && (head->record_count != LEVEL_COUNT)) {//extend step counter add air pressure sensor
        int extend_effect_len = head->hd.length - standard_data_len;//skip head and step_count
        char motion_data[extend_effect_len + 1];//reserve 1 byte for motion type
        motion_data[0] = MOTIONHUB_TYPE_HW_STEP_COUNTER;//add motion type
        memcpy(motion_data + 1, &head->begin_time, extend_effect_len);//the offset rely on sizeof enum motion_type_t of mcu, now it is 1, we suggest motion_type_t use uint8_t, because sizeof(enum) may diffrernt between AP and mcu;
        hwlog_info("write extend step counter data to motion event buffer, record_count = %d!\n", (head->record_count > LEVEL_COUNT)?(head->record_count - LEVEL_COUNT):(head->record_count));
        inputhub_route_write(ROUTE_MOTION_PORT, motion_data, extend_effect_len + 1);//report extend step counter date to motion HAL
    }
    valid_step_count = recovery_step_count + head->step_count;
    head->step_count = valid_step_count;

    hwlog_info("convert to standard step counter data to sensor event buffer, step_count = %d!\n", head->step_count);
    head->hd.length = standard_data_len;//avoid report extend data to sensor HAL, convert to standard step counter data, just report member step_count to sensor HAL
}

extern int stop_auto_accel;
int get_airpress_data = 0;
int get_temperature_data = 0;
int fobidden_comm = 0; /*once this flag set to 1, ap/iom3 will not transfer commd*/

int inputhub_route_recv_mcu_data(const char *buf, unsigned int length)
{
    const pkt_header_t *head = (const pkt_header_t *)buf;
    bool is_notifier = false;

    if (NULL == (head = pack(buf, length))) {
            return 0;//receive next partial package.
    }
    if (head->tag < TAG_BEGIN || head->tag >= TAG_END) {
        hwlog_err("---------------------->head value : tag=%#.2x, cmd=%#.2x, length=%#.2x in %s\n", head->tag, head->cmd, head->length, __func__);
        return -EINVAL;
    }
    ++ipc_debug_info.event_cnt[head->tag];

    wake_up_mcu_event_waiter(head);

    if (is_mcu_notifier(head)) {
        mcu_notifier_queue_work(head);
        is_notifier = true;
    }

    if (is_sensor_data_report(head)) {
        pkt_xyz_data_req_t *sensor_event = (pkt_xyz_data_req_t *)head;

        sensor_read_number[head->tag]++;
        if (TAG_STEP_COUNTER == head->tag) {//extend step counter date
            step_counter_data_process((pkt_step_counter_data_req_t *)head);
        }
        if (head->tag == TAG_PS && sensor_event->x != 0) {//recieve proximity far
            wake_lock_timeout(&wlock, HZ);
            hwlog_info("Kernel get far event!\n");
        } else if (head->tag == TAG_PS) {
            hwlog_info("Kernel get near event!!!!\n");
        }
        if (unlikely((stop_auto_accel)&&(head->tag == TAG_ACCEL))) {
            hwlog_info("%s not report data for dt\n", __func__);
            return 0;
        }
        if (head->tag == TAG_PRESSURE) {
            get_airpress_data = sensor_event->x;
            get_temperature_data = sensor_event->y;
        }

        return report_sensor_event(head->tag, (int *)((char *)head + sizeof(pkt_header_t)), head->length);
    } else if (is_requirement_resp(head)) {
        return report_resp_data((const pkt_header_resp_t *)head);
    } else if(is_motion_data_report(head)) {
        char *motion_data = (char *)head + sizeof(pkt_header_t);
        if(((int)motion_data[0]) == MOTIONHUB_TYPE_TAKE_OFF) {
            wake_lock_timeout(&wlock, HZ);
            hwlog_err("%s weaklock HZ motiontype = %d \n", __func__, motion_data[0]);
        }
        return inputhub_route_write(ROUTE_MOTION_PORT, motion_data, head->length);
    } else {
        if (!is_notifier) {
            hwlog_err("--------->tag = %d, cmd = %d is not implement!\n", head->tag, head->cmd);
            fobidden_comm = 1;
            return -EINVAL;
        }
    }

    return 0;
}

extern int flag_for_sensor_test;
// handle user command as quickly as possible.
int inputhub_route_cmd(unsigned short port, unsigned int cmd, unsigned long arg)
{
    switch (port) {
        case ROUTE_SHB_PORT:
        {
	     if(flag_for_sensor_test) {
                return 0;
            }
            return send_sensor_cmd(cmd, arg);
        }
        break;
        case ROUTE_MOTION_PORT:
        {
            if(flag_for_sensor_test) {
                return 0;
            }
            return send_motion_cmd(cmd, arg);
        }
        break;

        default:
            hwlog_err("unimplement port : %d in %s\n", port, __func__);
            dmd_log_report(DSM_SHB_ERR_CMD, __func__, "unimplement port\n");
            return -EINVAL;
            break;
    }
    return 0;
}
EXPORT_SYMBOL_GPL(inputhub_route_cmd);

static char *sys_status_t_str[] =
{
	[ST_SCREENON] = "ST_SCREENON",
	[ST_SCREENOFF] = "ST_SCREENOFF",
	[ST_SLEEP] = "ST_SLEEP",
	[ST_WAKEUP]="ST_WAKEUP",
};

int tell_ap_status_to_mcu(int ap_st)
{
	read_info_t	pkg_mcu;
	if ((ST_BEGIN <= ap_st) && (ap_st < ST_END)) {
		pkt_sys_statuschange_req_t pkt;
		pkt.hd.tag = TAG_SYS;
		pkt.hd.cmd = CMD_SYS_STATUSCHANGE_REQ;
		pkt.hd.resp = (ap_st == ST_SLEEP)?RESP:NO_RESP;
		pkt.hd.length = sizeof(pkt) - sizeof(pkt.hd);
		pkt.status = ap_st;

		if (likely((ap_st >= ST_SCREENON)&&(ap_st <= ST_WAKEUP))){
			hwlog_info("------------>tell mcu ap in status %s\n", sys_status_t_str[ap_st]);
			iom3_sr_status = ap_st;
		}else{
			hwlog_info("------------>tell mcu ap in status %d\n", ap_st);
		}
               	return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), (ap_st == ST_SLEEP)? (&pkg_mcu):NULL);
       } else {
               hwlog_err("error status %d in %s\n", ap_st, __func__);
               return -EINVAL;
       }
}

static int sensorhub_fb_notifier(struct notifier_block *nb,
                 unsigned long action, void *data)
{
	switch (action) {
	case FB_EVENT_BLANK://change finished
	{
		struct fb_event *event = data;
		int *blank = event->data;
		switch (*blank) {
		case FB_BLANK_UNBLANK:/*screen on */
			tell_ap_status_to_mcu(ST_SCREENON);
			break;

		case FB_BLANK_POWERDOWN:/* screen off*/
			tell_ap_status_to_mcu(ST_SCREENOFF);
			break;

		default:
			hwlog_err("unknown---> lcd unknown in %s\n", __func__);
			break;
		}
	break;
	}
	default:
		break;
	}

	return NOTIFY_OK;
}

int sensorhub_pm_suspend(struct device *dev)
{
    int ret = 0;
    hwlog_info("%s\n",__func__);
    if (iom3_sr_status != ST_SLEEP) {
        ret = tell_ap_status_to_mcu(ST_SLEEP);
        iom3_power_state = ST_SLEEP;
        clean_ipc_debug_info();
    }

    return ret;
}

int sensorhub_pm_resume(struct device *dev)
{
    hwlog_info("%s\n",__func__);
    print_ipc_debug_info();
    INIT_COMPLETION(iom3_reboot);
    barrier();
    tell_ap_status_to_mcu(ST_WAKEUP);
    if (!wait_for_completion_timeout(&iom3_reboot, msecs_to_jiffies(1000))) {
        hwlog_err("resume :wait for response timeout\n");
        rdr_system_error(SENSORHUB_MODID, 0, 0);
    }
    hwlog_info("%s done\n",__func__);
    if(pConfigOnDDr->WrongWakeupMsg.flag)
    {
        pConfigOnDDr->WrongWakeupMsg.flag = 0;
        hwlog_err("************ sensorhub has wrong wakeup mesg\n");
        hwlog_err("time %d\n",pConfigOnDDr->WrongWakeupMsg.time);
        hwlog_err("irqs [%x] [%x]\n",pConfigOnDDr->WrongWakeupMsg.irq0,pConfigOnDDr->WrongWakeupMsg.irq1);
        hwlog_err("recvfromapmsg [%x] [%x] [%x] [%x]\n",pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[0], pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[1],pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[2],pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[3]);        
        hwlog_err("recvfromlpmsg [%x] [%x] [%x] [%x]\n",pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[0], pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[1],pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[2],pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[3]);        
        hwlog_err("sendtoapmsg [%x] [%x] [%x] [%x]\n",pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[0], pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[1],pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[2],pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[3]);        
        hwlog_err("sendtolpmsg [%x] [%x] [%x] [%x]\n",pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[0], pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[1],pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[2],pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[3]);        
        hwlog_err("ap lpm3 tap tlpm3 %x %x %x %x\n", pConfigOnDDr->WrongWakeupMsg.recvfromapmsgmode, pConfigOnDDr->WrongWakeupMsg.recvfromlpmsgmode,pConfigOnDDr->WrongWakeupMsg.sendtoapmsgmode,pConfigOnDDr->WrongWakeupMsg.sendtolpmsgmode);
        hwlog_err("************ sensorhub has wrong wakeup mesg end\n");
        memset(&(pConfigOnDDr->WrongWakeupMsg),0, sizeof(wrong_wakeup_msg_t));
    }
    return 0;
}

static int sensorhub_pm_notify(struct notifier_block *nb,
					unsigned long mode, void *_unused)
{
	switch (mode) {
	case PM_SUSPEND_PREPARE:/*suspend */
		hwlog_info("suspend in %s\n", __func__);
		disable_sensors_when_suspend();
		break;

	case PM_POST_SUSPEND:/* resume*/
		hwlog_info("resume in %s\n", __func__);
		enable_sensors_when_resume();
		break;

	case PM_HIBERNATION_PREPARE:/* Going to hibernate */
	case PM_POST_HIBERNATION:/* Hibernation finished */
	case PM_RESTORE_PREPARE:/* Going to restore a saved image */
	case PM_POST_RESTORE:/* Restore failed */
	default:
		break;
	}

	return 0;
}

static struct notifier_block fb_notify = {
    .notifier_call = sensorhub_fb_notifier,
};

static int send_current_to_mcu(int current_now)
{
    pkt_current_data_req_t pkt;
    pkt.hd.tag = TAG_CURRENT;
    pkt.hd.cmd = CMD_CURRENT_DATA_REQ;
    pkt.hd.resp = 0;
    pkt.hd.length = sizeof(pkt.current_now);
    pkt.current_now = current_now;
    hwlog_debug("send current val = %d in %s\n", current_now, __func__);
    return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
}

static int mcu_get_current(const pkt_header_t *head)
{
    hwlog_info("iom3 request current in %s\n", __func__);
    return open_send_current(send_current_to_mcu);
}

static int mcu_unget_current(const pkt_header_t *head)
{
    hwlog_info("iom3 unrequest current in %s\n", __func__);
    return close_send_current();
}

extern void disable_sensors_when_reboot(void);
static int shb_reboot_notifier(struct notifier_block *nb, unsigned long foo, void *bar)
{
    /* prevent access the emmc now: */
    hwlog_info("shb:%s: 0x%lu +\n", __func__, foo);
    if(SYS_RESTART == foo) {
        disable_sensors_when_reboot();
        disable_motions_when_sysreboot();
    }
    hwlog_info("shb:%s: -\n", __func__);
    return 0;
}

static struct notifier_block reboot_notify = {
    .notifier_call = shb_reboot_notifier,
    .priority = -1,
};

#ifdef CONFIG_IOM3_RECOVERY
static int shb_recovery_notifier(struct notifier_block *nb, unsigned long foo, void *bar)
{
	/* prevent access the emmc now: */
	hwlog_info("%s (%lu) +\n", __func__, foo);
	mutex_lock(&mutex_write_cmd);
	switch(foo){
		case IOM3_RECOVERY_START:
		case IOM3_RECOVERY_MINISYS:
			g_iom3_state = IOM3_ST_RECOVERY;
			mutex_unlock(&mutex_write_cmd);
			break;
		case IOM3_RECOVERY_DOING:
			g_iom3_state = IOM3_ST_REPEAT;
			mutex_unlock(&mutex_write_cmd);
			break;
		case IOM3_RECOVERY_FAILED:
                     hwlog_err("%s -recovery failed\n", __func__);
		case IOM3_RECOVERY_IDLE:
			g_iom3_state = IOM3_ST_NORMAL;
			mutex_unlock(&mutex_write_cmd);
			wake_up_all(&iom3_rec_wq);
			break;
		default:
			hwlog_err("%s -unknow state %ld\n", __func__, foo);
			break;
	}
	hwlog_info("%s -\n", __func__);
	return 0;
}

static struct notifier_block recovery_notify = {
    .notifier_call = shb_recovery_notifier,
    .priority = -1,
};

extern int iom3_rec_sys_callback(const pkt_header_t *head);
extern int register_iom3_recovery_notifier(struct notifier_block *nb);
#endif
extern int mcu_sys_ready_callback(const pkt_header_t *head);
extern int mcu_reboot_callback(const pkt_header_t *head);
static void set_notifier(void)
{
    /**register mcu event notifier**/
    init_mcu_notifier_list();
    init_mcu_event_wait_list();
    register_mcu_event_notifier(TAG_SYS, CMD_SYS_STATUSCHANGE_REQ, mcu_sys_ready_callback);
    register_mcu_event_notifier(TAG_SYS, CMD_SYS_STATUSCHANGE_REQ, mcu_reboot_callback);
#ifdef CONFIG_IOM3_RECOVERY
    register_mcu_event_notifier(TAG_SYS, CMD_SYS_STATUSCHANGE_REQ, iom3_rec_sys_callback);
#endif
    register_mcu_event_notifier(TAG_CURRENT, CMD_CURRENT_GET_REQ, mcu_get_current);
    register_mcu_event_notifier(TAG_CURRENT, CMD_CURRENT_UNGET_REQ, mcu_unget_current);

    /**register to pm**/
    pm_notifier(sensorhub_pm_notify, 0);

    /**register to framebuffer**/
    if (fb_register_client(&fb_notify)) {
        hwlog_err("register fb client failed in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_MAIN_INIT, __func__, "register fb client failed\n");
    }

    /**register to reboot notifier**/
    if(register_reboot_notifier(&reboot_notify)){
        hwlog_err("register reboot notify failed in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_MAIN_INIT, __func__, "register reboot notify failed\n");
    }
#ifdef CONFIG_IOM3_RECOVERY
    init_waitqueue_head(&iom3_rec_wq);
    if(register_iom3_recovery_notifier(&recovery_notify)){
        hwlog_err("register recovery notify failed in %s\n", __func__);
        dmd_log_report(DSM_SHB_ERR_MAIN_INIT, __func__, "register recovery notify failed\n");
    }
#endif
}

static void init_locks(void)
{
    int i;
    for (i = 0; i < sizeof(package_route_tbl) / sizeof(package_route_tbl[0]); ++i) {
        spin_lock_init(&package_route_tbl[i].buffer_spin_lock);
    }
    mutex_init(&mutex_write_cmd);
    mutex_init(&mutex_write_adapter);
    init_completion(&type_record.resp_complete);
    mutex_init(&type_record.lock_mutex);
    spin_lock_init(&type_record.lock_spin);
    spin_lock_init(&ref_cnt_lock);
    /* Initialize wakelock*/
    wake_lock_init(&wlock, WAKE_LOCK_SUSPEND, "sensorhub");
}

int inputhub_route_init(void)
{
    init_locks();
    set_notifier();
    init_hash_tables();
    return 0;
}
EXPORT_SYMBOL_GPL(inputhub_route_init);

void close_all_ports(void)
{
    int i;
    for (i = 0; i < sizeof(package_route_tbl) / sizeof(package_route_tbl[0]); ++i) {
        inputhub_route_close(package_route_tbl[i].port);
    }
}

void inputhub_route_exit(void)
{
    //close all ports
    close_all_ports();
    wake_lock_destroy(&wlock);
}
EXPORT_SYMBOL_GPL(inputhub_route_exit);
