/******************************************************************************
 * Copyright:   Copyright (c) 2008. Hisilicon Technologies, CO., LTD.
 * Version:
 * Filename:    hilog.h
 * Description: K3Log
 * History:
*******************************************************************************/

#ifndef __K3LOG_H
#define __K3LOG_H

#include <linux/miscdevice.h>

#define HISI_1K	(1024)
#define HISI_1M	(1024 * 1024)

#define HISI_LOG_RES_BUFFER_BASE	hisi_reserved_dumplog_phymem

#define LOG_INFO_BUF_LEN	(4*HISI_1K)
#define KERNEL_LOG_BUF_LEN	(1 << CONFIG_LOG_BUF_SHIFT)
#define MAIN_LOG_BUF_LEN	(256*HISI_1K)
#define EVENTS_LOG_BUF_LEN	(256*HISI_1K)
#define RADIO_LOG_BUF_LEN	(256*HISI_1K)
#define SYSTEM_LOG_BUF_LEN	(256*HISI_1K)
#define POWER_LOG_BUF_LEN	(256*HISI_1K)

#define K3_LOG_INFO_BASE	(HISI_LOG_RES_BUFFER_BASE)
#define K3_KERNEL_LOG_BASE	(K3_LOG_INFO_BASE+LOG_INFO_BUF_LEN)
#define K3_MAIN_LOG_BASE	(K3_KERNEL_LOG_BASE+KERNEL_LOG_BUF_LEN)
#define K3_EVENTS_LOG_BASE	(K3_MAIN_LOG_BASE+MAIN_LOG_BUF_LEN)
#define K3_RADIO_LOG_BASE	(K3_EVENTS_LOG_BASE+EVENTS_LOG_BUF_LEN)
#define K3_SYSTEM_LOG_BASE	(K3_RADIO_LOG_BASE+RADIO_LOG_BUF_LEN)
#define K3_POWER_LOG_BASE	(K3_SYSTEM_LOG_BASE+SYSTEM_LOG_BUF_LEN)

/* seconds */
#define DUMP_LOG_TIME_OUT	(120)

#define KERNEL_LOG_FILE_LEN	(2*1024*1024)
#define MAIN_LOG_FILE_LEN	(2*1024*1024)
#define EVENTS_LOG_FILE_LEN	(1*1024*1024)
#define RADIO_LOG_FILE_LEN	(3*1024*1024)
#define SYSTEM_LOG_FILE_LEN	(1*1024*1024)

#define K3_LOG_DIR		"/data/dumplog/"
#define KERNEL_LOG_FILE_NAME	"/data/dumplog/kernel"
#define MAIN_LOG_FILE_NAME	"/data/dumplog/main"
#define EVENTS_LOG_FILE_NAME	"/data/dumplog/events"
#define RADIO_LOG_FILE_NAME	"/data/dumplog/radio"
#define SYSTEM_LOG_FILE_NAME	"/data/dumplog/system"

#define K3_SLEEP_TIME	(1000)
#define K3_LOOP_TIMES	(300)

typedef enum {
	LOG_KERNEL,
	LOG_MAIN,
	LOG_EVENTS,
	LOG_RADIO,
	LOG_SYSTEM,
	LOG_MAX,
} log_type;

typedef struct {
	unsigned long waddr;
	unsigned long raddr;
} log_buffer_head;

/* TBD: from drivers/staging/android/logger.c,
 * if android version changes, we should check it.
 */
struct logger_log {
	unsigned char 		*buffer;	/* the ring buffer itself */
	struct miscdevice	misc;	/* misc device representing the log */
	wait_queue_head_t	wq;	/* wait queue for readers */
	struct list_head	readers; /* this log's readers */
	struct mutex		mutex;	/* mutex protecting buffer */
	size_t			w_off;	/* current write head offset */
	size_t			head;	/* new readers start here */
	size_t			size;	/* size of the log */
#ifdef CONFIG_K3_LOG
	volatile log_buffer_head	*log_buf_info;
	volatile unsigned char		*rbuf;
#endif
};
#endif
