/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  hisi_mutex_service.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef __MUTEX_SERVICE_H__
#define __MUTEX_SERVICE_H__
#include <hisi/drv_hisi_mutex_service.h>

#define REGISTER 0 /*注册*/
#define UN_REGISTER 1 /*停止*/
#define NOTIFY_PREEMPT 2 /*通知抢占*/

#define HISI_MUTEX_SERVICE_INIT (g_mutex_service_ready == 1)

#define LEN_OF_DATA_ARRAY ARRAY_SIZE(operation_data_array)
#define _HISI_MUTEX_OPERATION(id, name, time, pri, gid) \
		.operation_id = id, \
		.operation_name = name, \
		.timeout = time,\
		.priority = pri, \
		.mutex_group_id = gid,


/*存储业务数据的结构体*/
struct operation_data {
    enum hisi_mutex_service_id operation_id;
    char *operation_name;
    int timeout;
    enum hisi_mutex_service_priority priority;
    int mutex_group_id;
    int status;
    pPREEMPTFUNC callback;
    wait_queue_head_t write_wait;
    wait_queue_head_t read_wait;
    long now_sec;
};

static ssize_t hisi_app_service_start(struct device *pdev, struct device_attribute *attr, const char *buf, size_t size);
static ssize_t hisi_app_service_stop(struct device *pdev, struct device_attribute *attr, const char *buf, size_t size);
static ssize_t notify_preempt_to_app_mirror(struct device *pdev, struct device_attribute *attr, char *buf);
static ssize_t notify_preempt_to_app_wifidisplay(struct device *pdev, struct device_attribute *attr, char *buf);
static ssize_t notify_preempt_to_app_hmp(struct device *pdev, struct device_attribute *attr, char *buf);
static ssize_t notify_alive_to_app_mirror(struct device *pdev, struct device_attribute *attr, const char *buf, size_t size);
static ssize_t notify_alive_to_app_wifidisplay(struct device *pdev, struct device_attribute *attr, const char *buf, size_t size);
static ssize_t notify_alive_to_app_hmp(struct device *pdev, struct device_attribute *attr, const char *buf, size_t size);
static int mutex_service_probe(struct platform_device *pdev);
static int mutex_service_remove(struct platform_device *pdev);

#endif
