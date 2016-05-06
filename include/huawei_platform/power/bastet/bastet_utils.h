/* bastet.h
 *
 * Bastet Head File.
 *
 * Copyright (C) 2014 Huawei Device Co.,Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _BASTET_UTILS_H
#define _BASTET_UTILS_H

#include "bastet_dev.h"

#define BASTET_LOG_TAG					"Bastet"

#define BASTET_DEBUG					0
#define BASTET_INFO						1

#define BASTET_LOGD(fmt, ...) \
	do { \
		if (BASTET_DEBUG) { \
			printk(KERN_DEBUG "["BASTET_LOG_TAG"] %s: "fmt"\n", __func__, ##__VA_ARGS__); \
		} \
	} while (0)

#define BASTET_LOGI(fmt, ...) \
	do { \
		if (BASTET_INFO) { \
			printk(KERN_INFO "["BASTET_LOG_TAG"] %s: "fmt"\n", __func__, ##__VA_ARGS__); \
		} \
	} while (0)

#define BASTET_LOGE(fmt, ...) \
	do { \
		printk(KERN_ERR "["BASTET_LOG_TAG"] %s: "fmt"\n", __func__, ##__VA_ARGS__); \
	} while (0)

extern char cur_netdev_name[IFNAMSIZ];

struct socket *sockfd_lookup_by_fd_pid(int fd, pid_t pid, int *err);
struct sock *get_sock_by_fd_pid(int fd, pid_t pid);
int bastet_get_comm_prop(struct sock *sk, struct bst_sock_comm_prop *prop);
void bastet_get_sock_prop(struct sock *sk, struct bst_sock_sync_prop *prop);
struct sock *get_sock_by_comm_prop(struct bst_sock_comm_prop* guide);
void bastet_wakelock_acquire(void);
void bastet_wakelock_acquire_timeout(long timeout);
void bastet_wakelock_release(void);
int post_indicate_packet(bst_ind_type ind_type, void *info, u32 len);
void ind_hisi_com(void *info, u32 len);
bool is_uid_valid(__u32 uid);
bool get_bastet_of_status(void);
bool is_bastet_enabled(void);
bool is_proxy_available(void);
bool is_buffer_available(void);
bool is_channel_available(void);
bool is_cp_reset(void);
bool is_sock_foreground(struct sock *sk);
int bind_local_ports(u16 *local_port);
int unbind_local_ports(u16 local_port);
int get_bastet_sock_state(struct sock *sk);
int get_fd_by_addr(struct addr_to_fd *guide);
int get_pid_cmdline(struct get_cmdline *cmdline);

#endif  /* _BASTET_UTILS_H */
