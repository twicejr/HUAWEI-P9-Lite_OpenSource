/*
 * Copyright (c) Huawei Technologies Co., Ltd. 1998-2014. All rights reserved.
 *
 * File name: bastet_dev.h
 * Description: Provide kernel device information for bastet.
 * Author: Pengyu  ID: 00188486
 * Version: 0.1
 * Date: 2014/06/21
 *
 */

#ifndef _BASTET_DEV_H
#define _BASTET_DEV_H

#include <linux/ioctl.h>
#include "bastet_fastgrab.h"

#define BASTET_DEV_NAME					"/dev/bastet"

#define BST_IOC_MAGIC					'k'
#define BST_IOC_SOCK_SYNC_START			_IOW(BST_IOC_MAGIC,  1, struct bst_set_sock_sync_delay)
#define BST_IOC_SOCK_SYNC_STOP			_IOW(BST_IOC_MAGIC,  2, struct bst_sock_id)
#define BST_IOC_SOCK_SYNC_SET			_IOW(BST_IOC_MAGIC,  3, struct bst_set_sock_sync_prop)
#define BST_IOC_SOCK_COMM_GET			_IOWR(BST_IOC_MAGIC, 4, struct bst_get_sock_comm_prop)
#define BST_IOC_SOCK_CLOSE_SET			_IOW(BST_IOC_MAGIC,  5, struct bst_sock_comm_prop)
#define BST_IOC_SOCK_STATE_GET			_IOWR(BST_IOC_MAGIC, 6, struct bst_get_bastet_sock_state)
#define BST_IOC_APPLY_LOCAL_PORT		_IOR(BST_IOC_MAGIC,  7, uint16_t)
#define BST_IOC_RELEASE_LOCAL_PORT		_IOW(BST_IOC_MAGIC,  8, uint16_t)
#define BST_IOC_SET_TRAFFIC_FLOW		_IOW(BST_IOC_MAGIC,  9, struct bst_traffic_flow_prop)
#define BST_IOC_GET_TIMESTAMP_INFO		_IOR(BST_IOC_MAGIC, 10, struct bst_timestamp_info)
#define BST_IOC_SET_NET_DEV_NAME		_IOW(BST_IOC_MAGIC, 11, struct bst_net_dev_name)
#ifdef CONFIG_HUAWEI_BASTET_COMM
#define BST_IOC_GET_MODEM_RAB_ID		_IOR(BST_IOC_MAGIC, 12, struct bst_modem_rab_id)
#endif
#define BST_IOC_SOCK_RECONN_SET			_IOW(BST_IOC_MAGIC, 13, struct bst_get_sock_comm_prop)
#define BST_IOC_SOCK_RECONN_FAIL		_IOW(BST_IOC_MAGIC, 14, struct bst_sock_comm_prop)
#define BST_IOC_SET_RECONN_PROXYID		_IOW(BST_IOC_MAGIC, 15, struct reconn_id)
#define BST_IOC_SYNC_PROP_START			_IOW(BST_IOC_MAGIC, 16, struct bst_set_sock_sync_prop)
#define BST_IOC_SYNC_PROP_STOP			_IOW(BST_IOC_MAGIC, 17, struct bst_sock_comm_prop)
#define BST_IOC_PROXY_AVAILABLE			_IOW(BST_IOC_MAGIC, 18, int32_t)
#define BST_IOC_BUF_AVAILABLE			_IOW(BST_IOC_MAGIC, 19, int32_t)
#define BST_IOC_PRIO_SEND_SUC			_IOW(BST_IOC_MAGIC, 20, int32_t)
#define BST_IOC_SOCK_SYNC_PREPARE		_IOW(BST_IOC_MAGIC, 21, struct bst_set_sock_sync_delay)
#define BST_IOC_GET_FD_BY_ADDR			_IOWR(BST_IOC_MAGIC, 22, struct addr_to_fd)
#define BST_IOC_GET_CMDLINE				_IOWR(BST_IOC_MAGIC, 23, struct get_cmdline)
#define BST_IOC_SYNC_HOLD_TIME			_IOW(BST_IOC_MAGIC, 24, struct bst_set_sock_sync_delay)
#define BST_IOC_NET_DEV_RESET			_IOW(BST_IOC_MAGIC, 25, int32_t)
#define BST_IOC_UID_PROP_MONITOR		_IOW(BST_IOC_MAGIC, 26, struct app_monitor_prop)
#define BST_IOC_SET_HRTAPP_ACTIVITY		_IOW(BST_IOC_MAGIC, 27, int32_t)
#define BST_IOC_FAST_GRAB_INFO			_IOW(BST_IOC_MAGIC, 28, fastgrab_info)
#define BST_IOC_SET_PROC_INFO			_IOWR(BST_IOC_MAGIC, 29, struct set_process_info)
#define BST_IOC_SET_SPECIAL_UID			_IOW(BST_IOC_MAGIC, 30, int32_t)
#define BST_IOC_NF_CONTROL				_IOW(BST_IOC_MAGIC, 31, bool)
typedef enum {
	BST_SOCK_NOT_USED = 0,
	BST_SOCK_INVALID,
	BST_SOCK_UPDATING,
	BST_SOCK_VALID,
	BST_SOCK_NOT_CREATED,
} bst_sock_state;

typedef enum {
	BST_IND_INVALID = 0,
	BST_IND_HISICOM,
	BST_IND_SOCK_SYNC_REQ,
	BST_IND_SOCK_SYNC_PROP,
	BST_IND_SOCK_CLOSED,
	BST_IND_MODEM_RESET,
	BST_IND_NETFILTER_SYNC_UID,
	BST_IND_TRAFFIC_FLOW_REQ,
	BST_IND_PRIORITY_DATA,
	BST_IND_SOCK_DISCONNECT,
	BST_IND_SOCK_TIMEDOUT,
	BST_IND_SOCK_EST,
	BST_IND_SOCK_RENEW_CLOSE,
	BST_IND_SOCK_NORMAL_CLOSE,
	BST_IND_SOCK_ERR_CLOSE,
	BST_IND_PRIO_SOCK_CLOSE,
	BST_IND_SCREEN_STATE,
	BST_IND_UID_SOCK_PROP,
	BST_IND_TRIGGER_THAW,
	BST_IND_SOCK_STATE_CHANGED,
	BST_IND_PRIORITY_UID,
	BST_IND_FG_KEY_MSG,
	BST_IND_FG_UID_SOCK_CHG,
} bst_ind_type;

typedef enum {
	CMD_CHECK_UID_SOCK,
	CMD_ADD_UID,
	CMD_DEL_UID,
} monitor_cmd;
typedef enum {
    CMD_ADD_PROC_INFO,
    CMD_DEL_PROC_INFO,
    CMD_DEL_ALL_INFO,
} bastet_filter_cmd;
struct bst_device_ind {
	uint32_t cons;
	bst_ind_type type;
	uint32_t len;
	uint8_t value[0];
};

struct bst_sock_id {
	int fd;
	pid_t pid;
};

struct bst_sock_sync_prop {
	uint32_t seq;
	uint32_t rcv_nxt;
	uint32_t snd_wnd;
	uint32_t ts_recent;
	uint32_t mss;
	uint32_t tx;
	uint32_t rx;
	uint16_t snd_wscale;
	uint16_t rcv_wscale;
	uint32_t ts_current;
	uint32_t ts_recent_tick;
};

struct bst_sock_comm_prop {
	uint32_t local_ip;
	uint32_t remote_ip;
	uint16_t local_port;
	uint16_t remote_port;
};

struct bst_get_sock_comm_prop {
	struct bst_sock_id guide;
	struct bst_sock_comm_prop comm_prop;
};

struct bst_set_sock_sync_delay {
	struct bst_sock_id guide;
	uint32_t hold_time;
	int32_t proxy_id;
};

struct bst_close_sock_prop {
	struct bst_sock_comm_prop comm_prop;
	int32_t proxy_id;
};

struct bst_set_sock_sync_prop {
	struct bst_sock_comm_prop guide;
	struct bst_sock_sync_prop sync_prop;
};

struct bst_ind_sock_sync_prop {
	struct bst_sock_id guide;
	struct bst_sock_sync_prop sync_prop;
};

struct bst_ind_priority_prop {
	struct bst_sock_id guide;
	struct bst_sock_comm_prop comm_prop;
	struct bst_sock_sync_prop sync_prop;
	uint8_t priority;
	uint8_t sync_state;
	uint8_t seq_type;
	uint8_t pkt_type;
	uint32_t len;
	uint8_t data[0];
};

struct bst_get_bastet_sock_state {
	struct bst_sock_id guide;
	uint32_t sync_state;
};

struct bst_traffic_flow_prop {
	int fd;
	pid_t pid;
	uid_t uid;
	int protocol;
	uint32_t tx;
	uint32_t rx;
};

struct bst_traffic_flow_pkg {
	uint32_t cnt;
	uint8_t value[0];
};

struct bst_timestamp_info {
	uint32_t time_now;
	uint32_t time_freq;
};

struct bst_net_dev_name {
	char iface[IFNAMSIZ];
};

#ifdef CONFIG_HUAWEI_BASTET_COMM
struct bst_modem_rab_id {
	uint16_t modem_id;
	uint16_t rab_id;
};
#endif

struct addr_to_fd {
	int fd;
	pid_t pid;
	uint32_t remote_ip;
	uint16_t remote_port;
};

#define MAX_PID_NAME_LEN		100
struct get_cmdline {
	pid_t pid;
	char name[MAX_PID_NAME_LEN];
};

struct reconn_id {
	struct bst_sock_id guide;
	int32_t proxy_id;
	bool auto_connect;
};

struct app_monitor_prop {
	monitor_cmd cmd;
	int32_t uid;
	int32_t tid_count;
	int32_t tids[0];
};

struct bst_monitor_ind_prop {
	int32_t uid;
	struct bst_sock_id sock_id;
	struct bst_sock_comm_prop comm;
};
struct set_process_info {
	bastet_filter_cmd cmd;
	int32_t uid;
	int32_t pid;
};
#define BST_MAX_WRITE_PAYLOAD			(2048)
#define BST_MAX_READ_PAYLOAD			(BST_MAX_WRITE_PAYLOAD + sizeof(bst_device_ind))

#endif /* _BASTET_DEV_H */
