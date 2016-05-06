/******************************************************************************
 * Copyright:   Copyright (c) 2008. Hisilicon Technologies, CO., LTD.
 * Version:
 * Filename:    hilog.h
 * Description: HisiLog
 * History:
*******************************************************************************/

#ifndef __HISILOG_H
#define __HISILOG_H

#define HISI_1K	(1024)
#define HISI_1M	(1024 * 1024)

#define HISI_LOG_RES_BUFFER_BASE	0x3f800000

#define LOG_INFO_BUF_LEN		(4*HISI_1K)
#define UNFORGET_WRADDR_SIZE	(4*HISI_1K)
#define KERNEL_LOG_BUF_LEN		(2*HISI_1M)
#define EXCEPTION_LOG_BUF_LEN		(16*HISI_1K)
#define POWER_LOG_BUF_LEN	(64*HISI_1K)
#define JANK_LOG_BUF_LEN	(64*HISI_1K)


#define HISI_LOG_INFO_BASE	(HISI_LOG_RES_BUFFER_BASE)
#define HISI_KERNEL_LOG_BASE	(HISI_LOG_INFO_BASE+LOG_INFO_BUF_LEN)
#define HISI_EXCEPTION_LOG_BASE	(HISI_KERNEL_LOG_BASE+KERNEL_LOG_BUF_LEN)
#define HISI_POWER_LOG_BASE	(HISI_EXCEPTION_LOG_BASE+EXCEPTION_LOG_BUF_LEN)
#define HISI_JANK_LOG_BASE	 (HISI_POWER_LOG_BASE+POWER_LOG_BUF_LEN)


typedef struct {
	unsigned int waddr;
	unsigned int raddr;
} log_buffer_head;

#endif
