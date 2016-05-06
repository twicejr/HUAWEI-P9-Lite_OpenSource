/* bastet_channel.c
 *
 * Bastet Tcp Priority Channel.
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

#include <linux/fdtable.h>
#include <linux/file.h>
#include <net/tcp.h>
#include <net/inet_sock.h>
#include <huawei_platform/power/bastet/bastet_utils.h>

#define BST_PRIO_NORM					0
#define BST_PRIO_HIGH					1
#define BST_PRIO_LPWR					2

#define MAX_PRIORITY_DATA_MEM			1500
#define MAX_PRIORITY_DATA_PKT			1330

#define WAIT_SOCK_PROP_TIMEOUT			(3 * HZ)

typedef enum
{
	FLAGS_PROP_NONE = 0,
	FLAGS_PROP_SEQ_ONLY,
	FLAGS_PROP_SEQ_TS,
	FLAGS_PROP_FULL
} flags_property;

typedef enum
{
	FLAGS_PKT_TYPE_NONE = 0,
	FLAGS_PKT_TYPE_HEAD,
	FLAGS_PKT_TYPE_TAIL,
	FLAGS_PKT_TYPE_SINGLE
} flags_pkt_type;

extern void bastet_sync_prop_cancel(struct sock *sk);
extern void set_channel_occupied(void);
extern void clear_channel_occupied(void);

static void bastet_get_link_id(struct sock *sk, struct bst_sock_id *guide)
{
	struct fdtable *fdt;
	struct socket *sock;
	unsigned int i = 0;
	int err;
	bool match = false;

	fdt = files_fdtable(current->files);
	for (i = 0; i <= fdt->max_fds; i++) {
		sock = sockfd_lookup(i, &err);
		if (!sock) {
			continue;
		}
		match = (sock->sk == sk);
		sockfd_put(sock);
		if (match) {
			break;
		}
	}
	guide->pid = current->pid;
	guide->fd = match ? i : 0;
}

static uint8_t bastet_get_prio_level(int32_t flags)
{
	uint8_t level;

	if (flags & MSG_HRT) {
		level = BST_PRIO_HIGH;
	} else if (flags & MSG_LPW) {
		level = BST_PRIO_LPWR;
	} else {
		level = BST_PRIO_NORM;
	}

	return level;
}

static uint8_t set_packet_type(uint32_t cur, uint32_t count, size_t size)
{
	uint8_t type = FLAGS_PKT_TYPE_NONE;

	if (count == 0 || size == MAX_PRIORITY_DATA_PKT) {
		type = FLAGS_PKT_TYPE_SINGLE;
	} else if (cur == 0) {
		type = FLAGS_PKT_TYPE_HEAD;
	} else if (cur == count) {
		type = FLAGS_PKT_TYPE_TAIL;
	} else {
		type = FLAGS_PKT_TYPE_NONE;
	}

	return type;
}

static int32_t bastet_send_priority_data(struct sock *sk, struct msghdr *msg,
					struct bst_ind_priority_prop *prop, bool wq_empty)
{
	struct iovec *iov = msg->msg_iov;
	size_t size = iov->iov_len;
	unsigned char __user *from = iov->iov_base;
	uint32_t count = 0;
	uint32_t len = 0;
	uint32_t i;
	int32_t ret = 0;

	count = size / MAX_PRIORITY_DATA_PKT;
	for (i = 0; i <= count; i++) {
		len = count > i ? MAX_PRIORITY_DATA_PKT : size % MAX_PRIORITY_DATA_PKT;
		if (len == 0) {
			break;
		}
		prop->pkt_type = set_packet_type(i, count, size);
		prop->sync_prop.seq = tcp_sk(sk)->write_seq + i * MAX_PRIORITY_DATA_PKT;
		prop->sync_prop.ts_current = tcp_time_stamp + tcp_sk(sk)->tsoffset;
		prop->len = len;
		if (i == 0) {
			if (wq_empty) {
				prop->seq_type = FLAGS_PROP_FULL;
			} else {
				prop->seq_type = FLAGS_PROP_SEQ_TS;
			}
		} else {
			prop->seq_type = FLAGS_PROP_NONE;
		}
		ret = copy_from_user(prop->data, from + i * MAX_PRIORITY_DATA_PKT, len);
		if (ret) {
			break;
		}
		post_indicate_packet(BST_IND_PRIORITY_DATA, prop, sizeof(struct bst_ind_priority_prop) + len);
		memset(prop->data, 0, len);
	}

	return ret;
}

static void bastet_send_wq_data(struct sock *sk, struct sk_buff *skb,
				struct bst_ind_priority_prop *prop, bool first_skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct tcp_skb_cb *tcb = TCP_SKB_CB(skb);
	uint32_t size = skb->len;
	uint32_t count = 0;
	uint32_t len = 0;
	uint32_t i;

	count = size / MAX_PRIORITY_DATA_PKT;
	for (i = 0; i <= count; i++) {
		len = count > i ? MAX_PRIORITY_DATA_PKT : size % MAX_PRIORITY_DATA_PKT;
		if (len == 0) {
			break;
		}
		prop->pkt_type = set_packet_type(i, count, size);
		prop->sync_prop.seq = TCP_SKB_CB(skb)->seq + i * MAX_PRIORITY_DATA_PKT;
		prop->sync_prop.ts_current = tcb->when + tp->tsoffset;
		prop->len = len;
		prop->seq_type = (first_skb && i == 0) ? FLAGS_PROP_FULL : FLAGS_PROP_SEQ_TS;
		memcpy(prop->data, skb->data, len);
		post_indicate_packet(BST_IND_PRIORITY_DATA, prop, sizeof(struct bst_ind_priority_prop) + len);
		memset(prop->data, 0, len);
	}
}

static void bastet_pick_wq(struct sock *sk, struct bst_ind_priority_prop *prop)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *skb;
	bool first = true;

	skb = tcp_write_queue_head(sk);
	while (skb) {
		bastet_send_wq_data(sk, skb, prop, first);
		if (first) {
			first = false;
		}
		tcp_unlink_write_queue(skb, sk);
		sk_wmem_free_skb(sk, skb);
		tp->scoreboard_skb_hint = NULL;
		if (skb == tp->retransmit_skb_hint)
			tp->retransmit_skb_hint = NULL;
		if (skb == tp->lost_skb_hint)
			tp->lost_skb_hint = NULL;
		skb = tcp_write_queue_head(sk);
	}
	tp->packets_out = 0;
	tp->retrans_out = 0;
	tp->fackets_out = 0;
	tp->sacked_out = 0;
	tp->lost_out = 0;
	tp->rcv_tstamp = tcp_time_stamp;
	sk->sk_send_head = NULL;

	tcp_rearm_rto(sk);
}

static void bastet_update_seq(struct sock *sk, size_t size, bool block)
{
	struct tcp_sock *tp = tcp_sk(sk);
	int ret = 0;

	if (block && sk->bastet) {
		sk->bastet->flag = false;
		ret = wait_event_interruptible_timeout(sk->bastet->wq, sk->bastet->flag, WAIT_SOCK_PROP_TIMEOUT);
		BASTET_LOGI("wait_event_interruptible_timeout ret=%d", ret);
	}
	tp->write_seq += size;
	tp->snd_nxt = tp->write_seq;
}

static int bastet_send_priority_msg_internal(struct sock *sk, struct msghdr *msg, size_t size)
{
	struct bst_ind_priority_prop *prop;
	struct bst_sock_id guide;
	struct bst_sock_sync_prop sync_prop;
	struct bst_sock_comm_prop comm_prop;
	int32_t flags = msg->msg_flags;
	uint8_t priority = 0;
	uint8_t sync_state = BST_SOCK_NOT_USED;
	bool empty = false;

	sk->prio_channel = true;
	bastet_get_link_id(sk, &guide);
	bastet_get_comm_prop(sk, &comm_prop);
	bastet_get_sock_prop(sk, &sync_prop);
	priority = bastet_get_prio_level(flags);
	sync_state = get_bastet_sock_state(sk);

	prop = kmalloc(MAX_PRIORITY_DATA_MEM, GFP_ATOMIC);
	if (prop == NULL) {
		BASTET_LOGE("failed to kmalloc");
		return 0;
	}
	memset(prop, 0, MAX_PRIORITY_DATA_MEM);
	prop->guide = guide;
	prop->comm_prop = comm_prop;
	prop->sync_prop = sync_prop;
	prop->priority = priority;
	prop->sync_state = sync_state;

	set_channel_occupied();
	empty = tcp_write_queue_empty(sk);
	if (!empty) {
		bastet_pick_wq(sk, prop);
	}
	if (bastet_send_priority_data(sk, msg, prop, empty)) {
		kfree(prop);
		clear_channel_occupied();
		return -EFAULT;
	}

	kfree(prop);
	switch (sync_state) {
	case BST_SOCK_VALID:
		// sock sync property is in AP, so cancel sync timer
		bastet_sync_prop_cancel(sk);
	case BST_SOCK_NOT_USED:
	case BST_SOCK_NOT_CREATED:
		bastet_update_seq(sk, size, false);
		break;
	case BST_SOCK_INVALID:
	case BST_SOCK_UPDATING:
		bastet_update_seq(sk, size, true);
		break;
	default:
		BASTET_LOGE("Unknown sync state: %d", sync_state);
		break;
	}

	return 1;
}

static bool bastet_check_prio_flag(struct sock *sk, struct msghdr *msg)
{
	if (msg->msg_flags & (MSG_HRT | MSG_LPW)) {
		if (msg->msg_flags & MSG_HRT) {
			// if uid is foreground, it means this uid had been identified as hrt uid.
			if (!is_sock_foreground(sk)) {
				/* if sk is not identified as prio_channel, it means it is the first time,
				 * indicate bastetd to identify it to hrt uid.
				 */
				if (!sk->prio_channel) {
					int uid = sock_i_uid(sk);
					BASTET_LOGI("BST_IND_PRIORITY_UID, uid=%d", uid);
					post_indicate_packet(BST_IND_PRIORITY_UID, &uid, sizeof(int32_t));
					// continue to send hrt data, no matter foreground or background
				} else {
					// it is prio_channel, but not in the foreground
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

int bastet_send_priority_msg(struct sock *sk, struct msghdr *msg, size_t size)
{
	if (!is_bastet_enabled()) {
		return 0;
	}
	if (!is_proxy_available()) {
		return 0;
	}
	if (!is_buffer_available()) {
		return 0;
	}
	if (!is_channel_available()) {
		return 0;
	}
	if (bastet_check_prio_flag(sk, msg)) {
		return bastet_send_priority_msg_internal(sk, msg, size);
	}
	return 0;
}
