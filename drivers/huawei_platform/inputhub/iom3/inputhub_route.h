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

#define RGB_BUTTON_LIGHT_ON (0x00FFFFFF)
enum {TYPE_BUTTONLIGHT = 1, TYPE_LEDS, TYPE_VIBRATOR};
enum {//work mode
    WORK_OFF,
    WORK_ON, WORK_MS = WORK_ON,
    WORK_FLASH, WORK_PATTERN = WORK_FLASH
};

#define DEV_SENSORHUB_MAX_WRITE_SIZE    (128)//(OFFSET(pkg_from_devsensorhub, vibrator.pattern) + MAX_PATERN_SIZE * sizeof((((struct struct_tag *)0)->vibrator.pattern[0])))

struct pkg_from_devsensorhub{
    unsigned int type;//TYPE_BUTTONLIGHT, TYPE_LEDS, TYPE_VIBRATOR
    struct {//leds buttons vibrator
        unsigned int work_mode;
        union {
            struct {//pkg_buttons_leds
                unsigned int color_argb;
                unsigned int on_ms;
                unsigned int off_ms;
            };
            struct {//vibrate time_ms mode
                unsigned int vibrate_ms;
            };
            struct {//vibrate pattern mode
                unsigned int repeat_index;
                unsigned int pattern_size;
                unsigned int pattern[];
            };
        };
    };
};

enum
{
    LOG_LEVEL_FATAL=0,
    LOG_LEVEL_ERR=3,
    LOG_LEVEL_WARNING=4,
    LOG_LEVEL_INFO=6,
    LOG_LEVEL_DEBUG=7,
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

//called by sensorhub or tp modules.
extern int inputhub_route_open(unsigned short port);
extern void inputhub_route_close(unsigned short port);
extern ssize_t inputhub_route_read(unsigned short port, char __user *buf, size_t count);
extern int inputhub_route_cmd(unsigned short port, unsigned int cmd, unsigned long arg);

//called by inputhub_mcu module or test module.
extern int inputhub_route_init(void);
extern void inputhub_route_exit(void);
extern ssize_t inputhub_route_write(unsigned short port, char  *buf, size_t count);

extern int parse_write_cmds_from_devsensorhub(const struct pkg_from_devsensorhub *cmdbuf, size_t len);
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
extern int inputhub_sensor_setdelay_nolock(int tag, int delay_ms);
extern int inputhub_mcu_write_cmd_nolock(const void *buf, unsigned int length);
#ifdef CONFIG_INPUTHUB
extern int ap_hall_report(int value);
#else /* CONFIG_INPUTHUB = 0 */
static inline int ap_hall_report(int value)
{
    return 0;
}
#endif /* CONFIG_INPUTHUB */
#endif /* __LINUX_INPUTHUB_ROUTE_H__ */
