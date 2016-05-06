/*
 * Copyright (c) Huawei Technologies Co., Ltd. 1998-2014. All rights reserved.
 *
 * File name: hw_kcollect.h
 * Description: This file use to collect kernel state and report it.
 * Author: chenyouzhen@huawei.com
 * Version: 0.1
 * Date: 2014/07/21
 */

#ifndef _LINUX_KCOLLECT_H
#define _LINUX_KCOLLECT_H

#define KCOLLECT_BUFFER_SIZE 			( 256 )
#define KCOLLECT_CLOSE_ALL_MASK			( 0 )
#define KCOLLECT_FPS_MASK				( 1 << 0 )     // edc count
#define KCOLLECT_LOG_MASK				( 1 << 1 )     // reserve
#define KCOLLECT_SUSPEND_MASK			( 1 << 2 )     // suspend, resume, wake src
#define KCOLLECT_FREEZER_MASK			( 1 << 3 )
#define KCOLLECT_BINDERCALL_MASK		( 1 << 4 )
#define KCOLLECT_ALL_MASK				( 0x7fffffff )

int kcollect(int mask, const char *fmt, ...);
int hwkillinfo(int pid, int seg);
int hwbinderinfo(int callingpid, int calledpid);
#endif // _LINUX_KCOLLECT_H