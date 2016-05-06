/* bastet_traffic_flow.c
 *
 * Bastet Traffic Flow Control.
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

#include <linux/file.h>
#include <linux/netfilter/xt_qtaguid.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <net/sock.h>
#include <huawei_platform/power/bastet/bastet.h>
#include <huawei_platform/power/bastet/bastet_utils.h>

#include "xt_qtaguid_internal.h"

#define BST_FLOW_UPDATE_INTERVAL		(120 * HZ)		/* traffic flow update interval */
#define BST_FLOW_WAIT_TIMEOUT			(50)			/* traffic flow wait timeout */

/* declare these functions to call the system update flow function */
extern void bastet_update_if_tag_stat(const char *ifname, uid_t uid, const struct sock *sk,
									enum ifs_tx_rx direction, int proto, int bytes);
extern int bastet_update_total_bytes(const char *dev_name, int proto,
									unsigned long tx_bytes, unsigned long rx_bytes);

/* declare and define traffic flow parameter */
static wait_queue_head_t bastet_flow_queue;
static int bastet_flow_wait = 0;
static spinlock_t stat_lock;
static unsigned long last_time = 0;
static bool is_waiting = false;

#pragma pack(1)
struct bst_uid_filter_buf {
	__s32 uid_num;
	__u8 data[0];
};

struct bst_uid_info {
	__u32 uid_min;
	__u32 uid_max;
	__u8 invert;
};
#pragma pack()

struct bst_uid_list_head {
	struct list_head header;
	__s32 uid_num;
};

struct bst_uid_list_node {
	struct list_head list;
	struct bst_uid_info info;
};

struct bst_uid_list_head uid_list_head = {
	.uid_num = 0,
};

/*
 * transfer ifsproto to ipproto
 */
static int ifsproto_to_ipproto(int32_t protocol)
{
	switch(protocol) {
	case IFS_TCP:
		return IPPROTO_TCP;
	case IFS_UDP:
		return IPPROTO_UDP;
	case IFS_PROTO_OTHER:
		BASTET_LOGE("other protocol");
		return -EINVAL;
	default:
		BASTET_LOGE("protocol not found");
		return -EINVAL;
	}
}

/*
 * transfer ipproto to ifsproto
 */
static int ipproto_to_ifsproto(int32_t protocol)
{
	switch(protocol) {
	case IPPROTO_TCP:
		return IFS_TCP;
	case IPPROTO_UDP:
		return IFS_UDP;
	default:
		BASTET_LOGE("other protocol");
		return IFS_PROTO_OTHER;
	}
}

/*
 * call flow update interface to adjust APP flow
 */
static void handle_traffic_flow_update(char *name, struct sock *sk, int proto, uid_t uid,
										unsigned long tx_bytes, unsigned long rx_bytes)
{
	if (NULL == name) {
		BASTET_LOGE("app flow name error");
		return;
	}

	bastet_update_if_tag_stat(name, uid, sk, IFS_TX, proto, tx_bytes);
	bastet_update_if_tag_stat(name, uid, sk, IFS_RX, proto, rx_bytes);
}

/*
 * if there is no sock, it can find uid and adjust traffic flow by generic,
 * handle_traffic_flow_update for one flow,
 * and bastet_update_total_bytes for total flow
 */
static int adjust_traffic_flow_generic(struct bst_traffic_flow_prop *flow_p)
{
	int uid, proto, protocol;
	unsigned long tx_bytes;
	unsigned long rx_bytes;

	if (NULL == flow_p) {
		BASTET_LOGE("flow prop null pointer error!");
		return -EINVAL;
	}

	tx_bytes = flow_p->tx;
	rx_bytes = flow_p->rx;
	protocol = flow_p->protocol;
	uid = flow_p->uid;

	proto = ifsproto_to_ipproto(protocol);
	if (proto < 0) {
		BASTET_LOGE("protocol not found error!");
		return -EINVAL;
	}

	/* adjust APP traffic flow */
	if (is_uid_valid(uid)) {
		handle_traffic_flow_update(cur_netdev_name, NULL,
									proto, uid, tx_bytes, rx_bytes);
	} else {
		BASTET_LOGE("uid error!");
		return -EINVAL;
	}

	/* adjust total traffic flow */
	if (bastet_update_total_bytes(cur_netdev_name, protocol, tx_bytes, rx_bytes)) {
		BASTET_LOGE("bastet_update_total_bytes error");
		return -EINVAL;
	}

	return 0;
}

/*
 * if there is sock, it can adjust traffic flow by sock,
 * handle_traffic_flow_update for one flow,
 * and bastet_update_total_bytes for total flow
 */
int adjust_traffic_flow_by_sock(struct sock *sk, unsigned long tx, unsigned long rx)
{
	uid_t uid = 0;
	int proto = 0;
	const struct file *filp;
	struct socket *skt = NULL;

	if (NULL == sk) {
		BASTET_LOGE("null sock error");
		return -EINVAL;
	}

	skt = sk->sk_socket;
	proto = ipproto_to_ifsproto((int)(sk->sk_protocol));
	if (NULL != skt) {
		filp = skt->file;
		if (NULL != filp) {
			uid = filp->f_cred->uid;
		}
	}

	/* adjust APP traffic flow */
	handle_traffic_flow_update(cur_netdev_name, sk, sk->sk_protocol, uid, tx, rx);
	/* adjust total traffic flow */
	if (bastet_update_total_bytes(cur_netdev_name, proto, tx, rx)) {
		BASTET_LOGE("bastet_update_total_bytes error");
		return -EINVAL;
	}

	return 0;
}

static void bastet_clean_up_uid_list(void)
{
	struct bst_uid_list_node *pos = NULL;
	struct bst_uid_list_node *n = NULL;

	list_for_each_entry_safe(pos, n, &uid_list_head.header, list) {
		list_del(&pos->list);
		kfree(pos);
	}
	uid_list_head.uid_num = 0;
}

static void bastet_pack_uid_info(struct bst_uid_filter_buf *buf)
{
	struct bst_uid_list_node *pos = NULL;
	size_t off = sizeof(struct bst_uid_info);
	size_t offset = 0;

	if (IS_ERR_OR_NULL(buf)) {
		return;
	}

	list_for_each_entry(pos, &uid_list_head.header, list) {
		memcpy(buf->data + offset, &pos->info, off);
		offset += off;
	}
}

static void bastet_search_match(struct ipt_entry *ipt_e)
{
	struct xt_entry_match *ematch = NULL;
	struct xt_qtaguid_match_info *info = NULL;
	struct bst_uid_list_node *node = NULL;

	if (IS_ERR_OR_NULL(ipt_e)) {
		return;
	}

	xt_ematch_foreach(ematch, ipt_e) {
		/*(xt_qtaguid.c)match name must be owner and revision must be 1*/
		if ((strcmp(ematch->u.kernel.match->name, "owner") == 0)
			&& (ematch->u.kernel.match->revision == 1)) {
			info = (struct xt_qtaguid_match_info *)ematch->data;
			if (is_uid_valid(info->uid_min) && is_uid_valid(info->uid_max)) {
				node = (struct bst_uid_list_node *)kmalloc(sizeof(struct bst_uid_list_node), GFP_ATOMIC);
				if (!IS_ERR_OR_NULL(node)) {
					node->info.uid_min = info->uid_min;
					node->info.uid_max = info->uid_max;
					node->info.invert = info->invert;
					list_add_tail(&node->list, &uid_list_head.header);
					uid_list_head.uid_num++;
				}
			}
		}
	}
}

static void bastet_search_entry(struct xt_table_info *newinfo)
{
	void *loc_cpu_entry = NULL;
	struct ipt_entry *ipt_e = NULL;
	struct xt_entry_target *e_t = NULL;

	if (IS_ERR_OR_NULL(newinfo)) {
		return;
	}

	loc_cpu_entry = newinfo->entries[raw_smp_processor_id()];
	xt_entry_foreach(ipt_e, loc_cpu_entry, newinfo->size) {
		e_t = ipt_get_target(ipt_e);
		/*target must be REJECT*/
		if (strcmp(e_t->u.kernel.target->name, "REJECT") == 0) {
			bastet_search_match(ipt_e);
		}
	}
}

unsigned char *bastet_save_uid_info(const char *table_name, struct xt_table_info *newinfo, int *buf_len)
{
	struct bst_uid_filter_buf *buf = NULL;
	int uid_buf_len = 0;

	if (!is_bastet_enabled()) {
		return NULL;
	}

	if (IS_ERR_OR_NULL(table_name) || strcmp(table_name, "filter") != 0 || IS_ERR_OR_NULL(newinfo)) {
		return NULL;
	}

	bastet_search_entry(newinfo);
	uid_buf_len = sizeof(struct bst_uid_filter_buf) + uid_list_head.uid_num * sizeof(struct bst_uid_info);
	buf = (struct bst_uid_filter_buf *)kmalloc(uid_buf_len, GFP_ATOMIC);
	if (IS_ERR_OR_NULL(buf)) {
		goto err;
	}
	buf->uid_num = uid_list_head.uid_num;
	*buf_len = uid_buf_len;
	bastet_pack_uid_info(buf);
err:
	bastet_clean_up_uid_list();

	return (unsigned char *)buf;
}

void bastet_indicate_uid_info(unsigned char *buf, int buf_len)
{
	if (!is_bastet_enabled()) {
		return;
	}

	if (IS_ERR_OR_NULL(buf)) {
		return;
	}

	post_indicate_packet(BST_IND_NETFILTER_SYNC_UID, buf, buf_len);
	kfree(buf);
}

/*
 * indicate traffic flow request and wait event interrupt,
 * two minute once
 */
void bastet_wait_traffic_flow(void)
{
	unsigned long delta = 0;
	unsigned long irq_flags;

	if (!is_bastet_enabled()) {
		return;
	}
	spin_lock_irqsave(&stat_lock, irq_flags);
	delta = jiffies - last_time;
	if (delta < BST_FLOW_UPDATE_INTERVAL) {
		spin_unlock_irqrestore(&stat_lock, irq_flags);
		return;
	}
	last_time = jiffies;
	is_waiting = true;
	spin_unlock_irqrestore(&stat_lock, irq_flags);

	if (post_indicate_packet(BST_IND_TRAFFIC_FLOW_REQ, NULL, 0)) {
		BASTET_LOGE("post_indicate_packet failed!");
		return;
	}

	wait_event_interruptible_timeout(bastet_flow_queue, bastet_flow_wait, msecs_to_jiffies(BST_FLOW_WAIT_TIMEOUT));
	bastet_flow_wait = 0;
}

/*
 * wake up traffic flow interrupt
 */
void bastet_wake_up_traffic_flow(void)
{
	unsigned long irq_flags;

	if (is_waiting) {
		bastet_flow_wait = 1;
		wake_up_interruptible(&bastet_flow_queue);
		spin_lock_irqsave(&stat_lock, irq_flags);
		is_waiting = false;
		spin_unlock_irqrestore(&stat_lock, irq_flags);
	}
}

/*
 * decompression traffic flow package and wake up interrupt
 */
int adjust_traffic_flow_by_pkg(uint8_t *buf, int cnt)
{
	int err, i;
	struct socket *skt = NULL;
	struct sock *sk = NULL;
	struct bst_traffic_flow_prop *ptr = (struct bst_traffic_flow_prop *)buf;

	if (NULL == buf || 0 == cnt) {
		bastet_wake_up_traffic_flow();
		return 0;
	}

	/* decompression package, and adjust traffic flow by sock or generic */
	for (i = 0; i < cnt; i++) {
		skt = sockfd_lookup_by_fd_pid(ptr->fd, ptr->pid, &err);
		if (NULL != skt) {
			sk = skt->sk;
			if (NULL != sk) {
				sock_hold(sk);
				adjust_traffic_flow_by_sock(sk, ptr->tx, ptr->rx);
				sock_put(sk);
			}
			sockfd_put(skt);
		} else {
			adjust_traffic_flow_generic(ptr);
		}
		ptr++;
	}

	bastet_wake_up_traffic_flow();

	return 0;
}

/*
 * init traffic flow wait queue, spinlock and uid list
 */
void bastet_traffic_flow_init(void)
{
	init_waitqueue_head(&bastet_flow_queue);
	spin_lock_init(&stat_lock);
	INIT_LIST_HEAD(&uid_list_head.header);
}
