/*
 *  drivers/misc/inputhub/inputhub_test.c
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen, yaodongdong <inputhub@huawei.com>
 *
 */
#if 0//excute in inputhub_route.c
#include <linux/types.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/freezer.h>
#include <linux/sensorhub.h>
#include <linux/input.h>
#include <linux/i2c.h>
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include <linux/kthread.h>//kthread_run
#include <linux/delay.h>//msleep
#include "protocol.h"
#include "inputhub_route.h"

struct sensors_cmd_hal {
    int cmd;
    int arg;
};

static const struct sensors_cmd_hal sensors_cmd_tab[] = {
    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_ACCELEROMETER},
    {SHB_IOCTL_APP_DELAY_ACCEL,                 66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_ACCELEROMETER},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_LIGHT},
    {SHB_IOCTL_APP_DELAY_LIGHT,                 66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_LIGHT},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_PROXIMITY},
    {SHB_IOCTL_APP_DELAY_PROXI,                 66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_PROXIMITY},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_GYROSCOPE},
    {SHB_IOCTL_APP_DELAY_GYRO,                  66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_GYROSCOPE},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_GRAVITY},
    {SHB_IOCTL_APP_DELAY_GRAVITY,               66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_GRAVITY},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_MAGNETIC},
    {SHB_IOCTL_APP_DELAY_MAGNETIC,              66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_MAGNETIC},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_ROTATESCREEN},
    {SHB_IOCTL_APP_DELAY_ROTATESCREEN,          66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_ROTATESCREEN},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_LINEARACCELERATE},
    {SHB_IOCTL_APP_DELAY_LINEARACCELERATE,      66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_LINEARACCELERATE},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_ORIENTATION},
    {SHB_IOCTL_APP_DELAY_ORIENTATION,           66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_ORIENTATION},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_ROTATEVECTOR},
    {SHB_IOCTL_APP_DELAY_ROTATEVECTOR,          66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_ROTATEVECTOR},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_PRESSURE},
    {SHB_IOCTL_APP_DELAY_PRESSURE,              66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_PRESSURE},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_TEMPERATURE},
    {SHB_IOCTL_APP_DELAY_TEMPERATURE,           66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_TEMPERATURE},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_RELATIVE_HUMIDITY},
    {SHB_IOCTL_APP_DELAY_RELATIVE_HUMIDITY,     66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_RELATIVE_HUMIDITY},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_AMBIENT_TEMPERATURE},
    {SHB_IOCTL_APP_DELAY_AMBIENT_TEMPERATURE,   66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_AMBIENT_TEMPERATURE},

    {SHB_IOCTL_APP_ENABLE_SENSOR,               SENSORHUB_TYPE_MCU_LABC},
    {SHB_IOCTL_APP_DELAY_MCU_LABC,              66},
    {SHB_IOCTL_APP_DISABLE_SENSOR,              SENSORHUB_TYPE_MCU_LABC},
};

void sensor_cmd_test(void)
{
    int i;
    for (i = 0; i < sizeof(sensors_cmd_tab) / sizeof(sensors_cmd_tab[0]); ++i) {
        if (inputhub_route_cmd(ROUTE_SHB_PORT, sensors_cmd_tab[i].cmd, sensors_cmd_tab[i].arg) != 0) {
            hwlog_err("cmd send error with cmd = %#.8x, arg = %d, in %s\n", sensors_cmd_tab[i].cmd, sensors_cmd_tab[i].arg, __func__);
        }
    }
}

void set_backlight_brightness_test(void)
{
    int brightness;
    for (brightness = 20; brightness < 256; ++brightness) {
        if (set_backlight_brightness(brightness) != 0) {
            hwlog_err("set backlight brightness error with brightness = %d, in %s\n", brightness, __func__);
        }
    }
}

static const struct pkg_from_devsensorhub pkg_from_devsensorhub_tab[] = {
    {.type = TYPE_BUTTONLIGHT, .work_mode = WORK_ON, .color_argb = RGB_BUTTON_LIGHT_ON},
    {.type = TYPE_LEDS, .work_mode = WORK_ON, .color_argb = 0x0000ff00},
    {.type = TYPE_VIBRATOR, .work_mode = WORK_MS, .vibrate_ms = 500},
};
void parse_write_cmds_from_devsensorhub_test(void)
{
    int i;
    for (i = 0; i < sizeof(pkg_from_devsensorhub_tab) / sizeof(pkg_from_devsensorhub_tab[0]); ++i) {
        if (parse_write_cmds_from_devsensorhub(&pkg_from_devsensorhub_tab[i], sizeof(struct pkg_from_devsensorhub)) != 0) {
            hwlog_err("parse write cmds from devsensorhu error with type = %d, in %s\n", pkg_from_devsensorhub_tab[i].type, __func__);
        }
    }
}

void tell_ap_status_to_mcu_test(void)
{
    int status;
    for (status = CMD_SYS_SCREENON_REQ; status <= CMD_SYS_POWERON_REQ; status += 2) {
        if (tell_ap_status_to_mcu(status) != 0) {
            hwlog_err("tell ap status to mcu error with status = %d, in %s\n", status, __func__);
        }
    }
}

int all_cmds_test(void *arg)
{
    sensor_cmd_test();
    set_backlight_brightness_test();
    parse_write_cmds_from_devsensorhub_test();
    tell_ap_status_to_mcu_test();

    return 0;
}

void init_all_cmds_init_run(void)
{
    kthread_run(all_cmds_test, NULL, "all_cmds_test");
}

//²âÊÔ»º³åÇø¶ÁÐ´´úÂë
int cnt_read = 0;
int cnt_write = 0;
#define TEST_CNT (100)
static pkt_xyz_data_req_t sensor_data_report_tab[] = {
    {.hd = {.tag = TAG_ACCEL,          .cmd = CMD_PRIVATE, .length = 0x10}},
    {.hd = {.tag = TAG_PS,             .cmd = CMD_PRIVATE, .length = 0x04}},
    {.hd = {.tag = TAG_MAG,            .cmd = CMD_PRIVATE, .length = 0x10}},
    {.hd = {.tag = TAG_LINEAR_ACCEL,   .cmd = CMD_PRIVATE, .length = 0x10}},
    {.hd = {.tag = TAG_ALS,            .cmd = CMD_PRIVATE, .length = 0x04}},
    {.hd = {.tag = TAG_GYRO,           .cmd = CMD_PRIVATE, .length = 0x10}},
    {.hd = {.tag = TAG_LABC,           .cmd = CMD_PRIVATE, .length = 0x04}},
};
int write_buffer(void *arg)
{
    int i = 0;
    int j = 0;
    while (i++ < 200) {
        msleep(1000);
    }
    while (cnt_write++ < TEST_CNT) {
        for (j = 0; j < sizeof(sensor_data_report_tab) / sizeof(sensor_data_report_tab[0]); ++j) {
            if (inputhub_route_recv_mcu_data((const char *)(&sensor_data_report_tab[j]), sensor_data_report_tab[j].hd.length + 8) != 0) {
                hwlog_err("write sensor data to fifo error in %s\n", __func__);
            }
            msleep(5);//200HZ
        }
    }
    return 0;
}

void init_write_buffer_run(void)
{
    kthread_run(write_buffer, NULL, "thread_write_buffer");
}

//close receive data from mcu when test
/*
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
    char data[];
}read_info_t;
*/

struct read_info my_read_info;
int my_send_func(void *arg)
{
    int i = 0;
    char buf[1] = {0};

    struct write_info send_tab[] = {
        {.tag = TAG_ACCEL, .cmd = CMD_ACCEL_SELFCALI_REQ, .wr_buf = buf, .wr_len = 0},
        {.tag = TAG_GYRO, .cmd = CMD_GYRO_SELFTEST_REQ, .wr_buf = buf, .wr_len = 0},
        {.tag = TAG_GYRO, .cmd = CMD_GYRO_PARAMET_REQ, .wr_buf = buf, .wr_len = 0},
    };
    struct write_info open_acc = {
        TAG_ACCEL, CMD_CMN_OPEN_REQ, NULL, 0
    };
    int delay = 10;//
    struct write_info setdelay_acc = {
        TAG_ACCEL, CMD_CMN_INTERVAL_REQ, &delay, 4
    };
    /*struct write_info close_acc = {
        TAG_ACCEL, CMD_CMN_CLOSE_REQ, NULL, 0
    };*/
    char xxx_buf[100];
    struct read_info *read__ = (struct read_info *)xxx_buf;
    arg = arg;
    msleep(1000);
    msleep(1000);
    msleep(1000);
    msleep(1000);
    msleep(1000);
    write_customize_cmd(&open_acc, NULL);//open acc
    write_customize_cmd(&setdelay_acc, NULL);//open acc
    while (true) {
        write_customize_cmd(&open_acc, read__);//open acc
        write_customize_cmd(&setdelay_acc, read__);//open acc
        write_customize_cmd(send_tab + i, &my_read_info);
        hwlog_info("errno = %d, data_length = %d\n", my_read_info.errno, my_read_info.data_length);
        if (sizeof(send_tab) / sizeof(send_tab[0]) == ++i) {
            i = 0;
        }
        msleep(1000);
        //write_customize_cmd(&close_acc, read__);//close acc
    }

    return 0;
}

void init_send_run(void)
{
    kthread_run(my_send_func, NULL, "thread_send1");
    kthread_run(my_send_func, NULL, "thread_send2");
    kthread_run(my_send_func, NULL, "thread_send3");
}

//to resp cmd without mcu
int my_recv_func(void *arg)
{
    int i = 0;
    pkt_header_resp_t recv_tab[] = {
        {.tag = TAG_ACCEL, .cmd = CMD_ACCEL_SELFCALI_RESP, .length = 12, .errno = 0},
        {.tag = TAG_GYRO, .cmd = CMD_GYRO_SELFTEST_RESP, .length = 20, .errno = 0},
        {.tag = TAG_GYRO, .cmd = CMD_GYRO_PARAMET_RESP, .length = 32, .errno = 0},
    };

    arg = arg;
    while (1) {
        //print_dbg("----->recv in %s\n", __func__);
        inputhub_route_recv_mcu_data((const char *)(&recv_tab[i]), recv_tab[i].length + sizeof(pkt_header_t));
        if (sizeof(recv_tab) / sizeof(recv_tab[0]) == ++i) {
            i = 0;
        }
        msleep(500);
    }

    return 0;
}

void init_recv_run(void)
{
    kthread_run(my_recv_func, NULL, "thread_recv");
}

//open acc sensor and read data from buffer
int my_read_buf_func(void *arg)
{
    #define READ_BUF_SIZE   256
    char read_buf[READ_BUF_SIZE];

    struct write_info open_acc = {
        TAG_ACCEL, CMD_CMN_OPEN_REQ, NULL, 0
    };
    int delay = 10;//
    struct write_info setdelay_acc = {
        TAG_ACCEL, CMD_CMN_INTERVAL_REQ, &delay, 4
    };
    msleep(1000);
    msleep(1000);
    msleep(1000);
    msleep(1000);
    msleep(1000);
    write_customize_cmd(&open_acc, NULL);//open acc
    write_customize_cmd(&setdelay_acc, NULL);//open acc

    arg = arg;
    while (true) {
        inputhub_route_read(ROUTE_SHB_PORT, read_buf, READ_BUF_SIZE);
    }
    return 0;
}

void init_read_buf_run(void)
{
    kthread_run(my_read_buf_func, NULL, "thread_read_buf");
}


#endif
