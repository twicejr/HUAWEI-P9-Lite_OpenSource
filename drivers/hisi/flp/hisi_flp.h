/*
 * hisi flp driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author: lijiangxiong <lijiangxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/*ioctrl cmd type*/
#define FLP_TAG_FLP         0
#define FLP_TAG_GPS         1
#define FLP_TAG_AR          2

#define FLP_IOCTL_CMD_MASK              (0xFFFF00FF)

#define FLP_IOCTL_TAG_MASK              (0xFFFFFF00)
#define FLP_IOCTL_TAG_FLP               (0x464C0000)
#define FLP_IOCTL_TAG_GPS               (0x464C0100)
#define FLP_IOCTL_TAG_AR                (0x464C0200)
#define FLP_IOCTL_TAG_COMMON            (0x464CFF00)

#define FLP_IOCTL_TYPE_MASK             (0xFFFF00F0)
#define FLP_IOCTL_TYPE_PDR              (0x464C0000)
#define FLP_IOCTL_TYPE_AR               (0x464C0010)
#define FLP_IOCTL_TYPE_COMMON           (0x464C00F0)

#define FLP_IOCTL_PDR_START(x)          (0x464C0000 + ((x) * 0x100) + 1)
#define FLP_IOCTL_PDR_STOP(x)           (0x464C0000 + ((x) * 0x100) + 2)
#define FLP_IOCTL_PDR_READ(x)           (0x464C0000 + ((x) * 0x100) + 3)
#define FLP_IOCTL_PDR_WRITE(x)          (0x464C0000 + ((x) * 0x100) + 4)
#define FLP_IOCTL_PDR_CONFIG(x)         (0x464C0000 + ((x) * 0x100) + 5)
#define FLP_IOCTL_PDR_UPDATE(x)         (0x464C0000 + ((x) * 0x100) + 6)
#define FLP_IOCTL_PDR_FLUSH(x)          (0x464C0000 + ((x) * 0x100) + 7)
#define FLP_IOCTL_PDR_STEP_CFG(x)       (0x464C0000 + ((x) * 0x100) + 8)

#define FLP_IOCTL_AR_START(x)           (0x464C0000 + ((x) * 0x100) + 0x11)
#define FLP_IOCTL_AR_STOP(x)            (0x464C0000 + ((x) * 0x100) + 0x12)
#define FLP_IOCTL_AR_READ(x)            (0x464C0000 + ((x) * 0x100) + 0x13)
#define FLP_IOCTL_AR_UPDATE(x)          (0x464C0000 + ((x) * 0x100) + 0x15)
#define FLP_IOCTL_AR_FLUSH(x)           (0x464C0000 + ((x) * 0x100) + 0x16)
#define FLP_IOCTL_AR_STATE(x)           (0x464C0000 + ((x) * 0x100) + 0x17)

/*common ioctrl*/
#define FLP_IOCTL_COMMON_GET_UTC        (0x464C0000 + 0xFFF1)
#define FLP_IOCTL_COMMON_SLEEP          (0x464C0000 + 0xFFF2)
#define FLP_IOCTL_COMMON_AWAKE_RET      (0x464C0000 + 0xFFF3)
#define FLP_IOCTL_COMMON_SETPID         (0x464C0000 + 0xFFF4)
#define FLP_IOCTL_COMMON_CLOSE_SERVICE  (0x464C0000 + 0xFFF5)

enum{
    AR_STATE_IN_VEHICLE = 0,
    AR_STATE_ON_BICYCLE,
    AR_STATE_WALKING,
    AR_STATE_RUNNING,
    AR_STATE_STILL,
    AR_STATE_BUTT,
};
enum {
    AR_STATE_ENTER = 1,
    AR_STATE_EXIT,
};

typedef struct flp_pdr_data {
    unsigned long       msec ;
    unsigned int        step_count;
    int                 relative_position_x;
    int                 relative_position_y;
    short               velocity_x;
    short               velocity_y;
    unsigned int        migration_distance;
    unsigned int        absolute_altitude;
    unsigned short      absolute_bearing;
    unsigned short      reliability_flag;
}  __packed flp_pdr_data_t  ;

typedef struct compensate_data {
    unsigned int        compensate_step;
    int                 compensate_position_x;
    int                 compensate_position_y;
    unsigned int        compensate_distance;
} compensate_data_t ;

typedef struct  step_report {
    int data[12] ;
} step_report_t;

typedef struct buf_info {
    char            *buf;
    unsigned long   len;
} buf_info_t;

typedef struct pdr_start_config {
    unsigned int   report_interval;
    unsigned int   report_precise;
    unsigned int   report_count;
    unsigned int   report_times;   /*plan to remove */
} pdr_start_config_t;

/*AR struct*/
typedef struct ar_activity_event {
    unsigned int        event_type;         /*0:disable*/
    unsigned int        activity;
    unsigned long       msec ;
}  __packed ar_activity_event_t ;

typedef struct ar_start_config {
    unsigned int            report_interval;
    ar_activity_event_t     activity_list[6];
} ar_start_config_t;

/********************************************
            define flp netlink
********************************************/
#define FLP_GENL_NAME                   "TASKFLP"
#define TASKFLP_GENL_VERSION            0x01

enum {
    FLP_GENL_ATTR_UNSPEC,
    FLP_GENL_ATTR_EVENT,
    __FLP_GENL_ATTR_MAX,
};
#define FLP_GENL_ATTR_MAX (__FLP_GENL_ATTR_MAX - 1)

enum {
    FLP_GENL_CMD_UNSPEC,
    FLP_GENL_CMD_PDR_DATA,
    FLP_GENL_CMD_AR_DATA,
    FLP_GENL_CMD_PDR_UNRELIABLE,
    FLP_GENL_CMD_NOTIFY_TIMEROUT,
    FLP_GENL_CMD_AWAKE_RET,
    __FLP_GENL_CMD_MAX,
};
#define FLP_GENL_CMD_MAX (__FLP_GENL_CMD_MAX - 1)

static struct genl_family flp_genl_family = {
    .id         = GENL_ID_GENERATE,
    .name       = FLP_GENL_NAME,
    .version    = TASKFLP_GENL_VERSION,
    .maxattr    = FLP_GENL_ATTR_MAX,
};

