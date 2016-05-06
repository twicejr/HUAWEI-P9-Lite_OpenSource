/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
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

#ifndef __HI6250_LOG_H__
#define __HI6250_LOG_H__


#define DEBUG_LEVEL 0
#define INFO_LEVEL  1


#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 1
#endif

#ifndef INFO_LEVEL
#define INFO_LEVEL  1
#endif

#ifndef LOG_TAG
#define LOG_TAG "hi6250snd"
#endif

#if DEBUG_LEVEL
#define logd(fmt, ...) pr_info(LOG_TAG"[D]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logd(fmt, ...)
#endif

#if INFO_LEVEL
#define logi(fmt, ...) pr_info(LOG_TAG"[I]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logi(fmt, ...)
#endif

#define logw(fmt, ...) \
do {\
    pr_warn(LOG_TAG"[W]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
}while(0);

#define loge(fmt, ...) \
do {\
    pr_err(LOG_TAG"[E]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
}while(0);

#define IN_FUNCTION   logd("In\n");
#define OUT_FUNCTION  logd("Out\n");

#endif

