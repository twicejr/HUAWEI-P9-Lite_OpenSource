/*
 *  drivers/misc/inputhub/inputhub_route.h
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen <inputhub@huawei.com>
 *
 */
#ifndef __LINUX_INPUTHUB_ROUTE_H__
#define __LINUX_INPUTHUB_ROUTE_H__
#include "protocol.h"

#include <huawei_platform/log/hw_log.h>

#define IOM3_ST_NORMAL			(0)
#define IOM3_ST_RECOVERY		(1)
#define IOM3_ST_REPEAT			(2)

#define HWLOG_TAG sensorhub
HWLOG_REGIST();

//#define OFFSET(struct_tag, member) ((int)&(((struct struct_tag *)0)->member))
//#define OFFSET_OF_END_MEM(struct_tag, member) (OFFSET(struct_tag, member) + sizeof((((struct struct_tag *)0)->member)))
//#define OFFSET_INTERVAL(struct_tag, member1, member2) (OFFSET_OF_END_MEM(struct_tag, member2) - OFFSET_OF_END_MEM(struct_tag, member1))

#define OFFSET(struct_t, member)                    offsetof(struct_t, member)
#define OFFSET_OF_END_MEM(struct_t, member)         ((unsigned long)(&(((struct_t *)0)->member) + 1))
#define OFFSET_INTERVAL(struct_t, member1, member2) (OFFSET_OF_END_MEM(struct_t, member2) - OFFSET_OF_END_MEM(struct_t, member1))


enum port{
    ROUTE_SHB_PORT = 0x01,
    ROUTE_MOTION_PORT = 0x02,
};


struct sensor_data {
    unsigned short type;
    unsigned short length;
    int value[16];//xyza...
};


typedef struct write_info
{
    int tag;
    int cmd;
    const void *wr_buf;//maybe NULL
    int wr_len;//maybe zero
}write_info_t;

typedef struct read_info
{
    int errno;
    int data_length;
    char data[MAX_PKT_LENGTH];
}read_info_t;

typedef struct sensor_operation
{
    int (*enable)(bool enable);
    int (*setdelay)(int ms);
} sensor_operation_t;

typedef struct ap_sensor_ops_record
{
    sensor_operation_t ops;
    bool work_on_ap;
} t_ap_sensor_ops_record;

typedef bool (*t_match)(void *priv, const pkt_header_t *pkt);
struct mcu_event_waiter
{
	struct completion complete;
	t_match match;
	void *out_data;
	int out_data_len;
	void *priv;
	struct list_head entry;
};

static inline bool match_tag_cmd(void *priv, const pkt_header_t *recv)
{
	pkt_header_t *send = (pkt_header_t *)priv;
	return (send->tag == recv->tag) && ((send->cmd + 1) == recv->cmd);
}

#define WAIT_FOR_MCU_RESP(trigger, match, wait_ms, out_data, out_data_len, priv) \
({\
	int __ret = 0;\
	struct mcu_event_waiter waiter;\
	init_wait_node_add_list(&waiter, match, out_data, out_data_len, (void *)priv);\
	INIT_COMPLETION(waiter.complete);\
	trigger;\
	__ret = wait_for_completion_timeout(&waiter.complete, msecs_to_jiffies(wait_ms));\
	list_del_mcu_event_waiter(&waiter);\
	__ret;\
})

#define WAIT_FOR_MCU_RESP_DATA_AFTER_SEND(send_pkt, trigger, wait_ms, out_data, out_data_len) \
WAIT_FOR_MCU_RESP(trigger, match_tag_cmd, wait_ms, out_data, out_data_len, send_pkt)

#define WAIT_FOR_MCU_RESP_AFTER_SEND(send_pkt, trigger, wait_ms) \
WAIT_FOR_MCU_RESP_DATA_AFTER_SEND(send_pkt, trigger, wait_ms, NULL, 0)

extern char* obj_tag_str[];

//called by sensorhub or tp modules.
extern int inputhub_route_open(unsigned short port);
extern void inputhub_route_close(unsigned short port);
extern ssize_t inputhub_route_read(unsigned short port, char __user *buf, size_t count);
extern int inputhub_route_cmd(unsigned short port, unsigned int cmd, unsigned long arg);

//called by inputhub_mcu module or test module.
extern int inputhub_route_init(void);
extern void inputhub_route_exit(void);
extern ssize_t inputhub_route_write(unsigned short port, char  *buf, size_t count);

extern int tell_ap_status_to_mcu(int ap_st);
extern int inputhub_route_recv_mcu_data(const char *buf, unsigned int length);

extern int sensorhub_init(void);
extern void sensorhub_exit(void);
extern int write_customize_cmd(const struct write_info *wr, struct read_info *rd);
extern int register_mcu_event_notifier(int tag, int cmd, int (*notify)(const pkt_header_t *head));
extern int unregister_mcu_event_notifier(int tag, int cmd, int (*notify)(const pkt_header_t *head));
extern int inputhub_sensor_enable(int tag, bool enable);
extern int inputhub_sensor_setdelay(int tag, int delay_ms);
extern int inputhub_sensor_enable_nolock(int tag, bool enable);
extern int inputhub_sensor_setdelay_nolock(int tag, int delay_ms, int batch_count);
extern int inputhub_mcu_write_cmd(const void *buf, unsigned int length);
extern int inputhub_mcu_write_cmd_nolock(const void *buf, unsigned int length);
extern int register_ap_sensor_operations(int tag, sensor_operation_t *ops);
extern int unregister_ap_sensor_operations(int tag);
extern bool ap_sensor_enable(int tag, bool enable);
extern bool ap_sensor_setdelay(int tag, int ms);
extern int report_sensor_event(int tag, int value[], int length);
extern void init_wait_node_add_list(struct mcu_event_waiter *waiter, t_match match, void *out_data, int out_data_len, void *priv);
extern void list_del_mcu_event_waiter(struct mcu_event_waiter *self);
#ifdef CONFIG_INPUTHUB
extern int ap_hall_report(int value);
#else /* CONFIG_INPUTHUB = 0 */
static inline int ap_hall_report(int value)
{
    return 0;
}
#endif /* CONFIG_INPUTHUB */
#endif /* __LINUX_INPUTHUB_ROUTE_H__ */
