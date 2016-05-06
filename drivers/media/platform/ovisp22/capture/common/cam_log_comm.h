
/*
 *  Hisilicon K3 soc camera ISP log debug switch header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *	Author :
 *  Version:  1.2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef LOG_H_COMM_INCLUDED
#define LOG_H_COMM_INCLUDED

#include <linux/time.h>

#include "../../../../../videocom/mntn/video_mntn_kernel.h"


#ifndef DEBUG_DEBUG
#define DEBUG_DEBUG 0
#endif

#ifndef DEBUG_INFO
#define DEBUG_INFO  1
#endif

#ifndef DEBUG_WARN
#define DEBUG_WARN  1
#endif

#ifndef DEBUG_ERROR
#define DEBUG_ERROR 1
#endif

#ifndef DEBUG_TIME
#define DEBUG_TIME 1
#endif

#ifndef LOG_TAG
#define LOG_TAG ""
#endif

#if DEBUG_DEBUG
#define print_debug(fmt, ...) mntn_video_print(EN_ID_MNTN_CAM_COM_LOG_MODULE, EN_VIDEO_LOG_LEVLE_DEBUG, "[" LOG_TAG "]" "Debug:" fmt "\n", ##__VA_ARGS__)
#else
#define print_debug(fmt, ...)
#endif
#if DEBUG_INFO
#define print_info(fmt, ...)  mntn_video_print(EN_ID_MNTN_CAM_COM_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "[" LOG_TAG "]" "Info:" fmt "\n", ##__VA_ARGS__)
#else
#define print_info(fmt, ...)
#endif
#if DEBUG_WARN
#define print_warn(fmt, ...) mntn_video_print(EN_ID_MNTN_CAM_COM_LOG_MODULE, EN_VIDEO_LOG_LEVLE_WARNNING, "[" LOG_TAG "]" "Warnning:" fmt "\n", ##__VA_ARGS__)
#else
#define print_warn(fmt, ...)
#endif
#if DEBUG_ERROR
#define print_error(fmt, ...) mntn_video_print(EN_ID_MNTN_CAM_COM_LOG_MODULE, EN_VIDEO_LOG_LEVLE_ERROR, "[" LOG_TAG "]" "Error:" fmt "\n", ##__VA_ARGS__)
#else
#define print_error(fmt, ...)
#endif

#if DEBUG_TIME
#define print_time(str) { \
		struct timeval tv;	\
		do_gettimeofday(&tv);	\
		printk("[" LOG_TAG "]" "%s, ******TIME: (%d.%6d)******\n", str, (int)tv.tv_sec, (int)tv.tv_usec);\
	}
#endif
#define assert(x)							\
	do {									\
		if (!(x))							\
			printk("!!!!!ASSERT ERROR!!!!");	\
	} while (0)

#define print_ddr() { \
	u32 addr = IO_ADDRESS(0xfd005000); \
	print_info("++++++++++++++++++++++++++++++++++++++++++++++++++++++++"); \
	print_info("0x%0x:0x%08x", addr + 0x18, (*(volatile unsigned  *)(addr + 0x18))); \
	print_info("--------------------------------------------------------");\
	}
#endif /*LOG_H_INCLUDED */
/********************************* END ****************************************/
