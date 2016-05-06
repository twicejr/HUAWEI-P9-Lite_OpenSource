/*
 * Copyright (c) Huawei Technologies Co., Ltd. 1998-2014. All rights reserved.
 *
 * File name: hw_packetmonitor.c
 * Description: This file used to monitor packet info.
 * Author: gavin.yangsong@huawei.com
 * Version: 0.1
 * Date: 2014/07/17
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/file.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv6.h>
#include <linux/hw_kstate.h>
#include <linux/spinlock.h>
#include <linux/rbtree.h>
#include <linux/ktime.h>
#include <linux/time.h>
#include <linux/list.h>
#include <linux/types.h>
#include <net/sock.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/inet_hashtables.h>
#include <net/inet6_hashtables.h>

MODULE_LICENSE("Dual BSD/GPL");

/*lock uid tree operation*/
static rwlock_t uid_rwlock;

static struct rb_root uid_tree_root;

/*monitor state control variable*/
static atomic_t monitor_state_of_in;
static atomic_t monitor_state_of_out;

extern struct inet_hashinfo tcp_hashinfo;

#define DIR_LOCAL_IN			0
#define DIR_LOCAL_OUT			1

#define START_MONITOR			1
#define STOP_MONITOR			0

#define IP_VERSION_V4 			4
#define IP_VERSION_V6 			6
#define V4_V6_ADDR_SIZE_DIFF 	(sizeof(struct in6_addr) - sizeof(__be32))

#define ERROR_UID 				0
#define UID_MIN_BOUNDARY        10000
#define NONE 					0

typedef enum {
	ADD_SINGLE_UID = 0,
	DEL_SINGLE_UID,
	START_MONITOR_SINGLE_UID,
	STOP_MONITOR_SINGLE_UID,
	START_MONITOR_ALL_UID,
	STOP_MONITOR_ALL_UID,
	START_MONITOR_LOCAL_IN,
	STOP_MONITOR_LOCAL_IN,
	START_MONITOR_LOCAL_OUT,
	STOP_MONITOR_LOCAL_OUT,
	DEL_ALL_UID,
	CONNECTION_REQUEST
} MONITOR_ORDER;

#pragma pack(1)
typedef struct {
	union {
		struct iphdr *v4;
		struct ipv6hdr *v6;
	}ip_hdr;
	struct tcphdr *tcp_hdr;
} PROTOCOL_HDR;

typedef struct {
	union {
		struct {
			__be32 daddr;
			__be32 saddr;
		}v4;
		struct {
			struct in6_addr daddr;
			struct in6_addr saddr;
		}v6;
	}ip;
	struct {
		__be16 dport;
		__be16 sport;
	}port;
} IPPORT;

typedef struct {
	u32 tv_sec;
	u32 tv_usec;
} PACKET_TIME;

typedef struct {
	u32 			offset;
	PACKET_TIME 	time;
} TRIGGER_TIME;

typedef struct {
	struct list_head 	list;
	TRIGGER_TIME 		trgr_time;
} TIME_LIST_NODE;

typedef struct {
	kuid_t uid;
	u32 data_len;
} UID_MATCH_INFO;

typedef struct {
	struct rb_node 	uid_node;
	UID_MATCH_INFO 	uid_info;
	u8 				mnt_state;
	struct list_head 	time_header;
} UID_TREE_NODE;

/*command received*/
typedef struct {
	u8 				cmd;
	UID_MATCH_INFO 	uid_info;
	TRIGGER_TIME 	trgr_time;
} MONITOR_CMD;

typedef struct {
	u16	protocol:4,
		dir:1,
		syn:1,
		ack:1,
		fin:1,
		none:8;
} SKB_STATE;

typedef union {
	struct {
		__be32 raddr;
	}v4;
	struct {
		struct in6_addr raddr;
	}v6;
} SKB_RADDR;

typedef struct {
	UID_MATCH_INFO 	uid_info;
	PACKET_TIME 	pkt_time;
} SKB_MATCH_INFO;

/*struct to send up*/
typedef struct {
	SKB_MATCH_INFO 	skb_info;
	SKB_STATE 		skb_state;
	SKB_RADDR 		skb_raddr;
} MONITOR_INFO;
#pragma pack()

/*
 * Function: free_ptr
 * Description: kfree a pointer and set it NULL
 * Input:	@p - pointer to kfree
 * Output:
 * Return:	void
*/
static inline void free_ptr(void *p)
{
	if (!IS_ERR_OR_NULL(p)) {
		kfree(p);
		p = NULL;
	}
}

/*
 * Function: is_time_valid
 * Description: check the trigger time valid or not,
 *				by compare it to the day time
 * Input:	@trgr_time - trigger time to compare
 *			@day_time - time of day
 * Output:
 * Return:	false -- invalid
 *			true -- valid
*/
static bool is_time_valid(TRIGGER_TIME *trgr_time, PACKET_TIME *day_time)
{
	__kernel_time_t t_rboundary = trgr_time->time.tv_sec + trgr_time->offset;
	return day_time->tv_sec >= t_rboundary ? false : true;
}

/*
 * Function: search_uid
 * Description: search uid from the uid tree
 * Input:	@uid - uid to search
 * Output:
 * Return:	NULL -- non-existent
 *			corresponding UID_TREE_NODE struct pointer -- existent
*/
static UID_TREE_NODE *search_uid(kuid_t uid)
{
	struct rb_node *node = uid_tree_root.rb_node;
	UID_TREE_NODE *ut_node = NULL;

	while (!IS_ERR_OR_NULL(node)) {
		ut_node = container_of(node, UID_TREE_NODE, uid_node);
		if (uid < ut_node->uid_info.uid) {
			node = node->rb_left;
		} else if (uid > ut_node->uid_info.uid) {
			node = node->rb_right;
		} else {
			return ut_node;
		}
	}
	return NULL;
}

/*
 * Function: update_trigger_time
 * Description: update trigger time list by deleting the time that
 *				has passed day time from uid
 * Input:	@time_header - time list head pointer
 *			@day_time - time of day
 * Output:
 * Return:	void
*/
static void update_trigger_time(struct list_head *time_header, PACKET_TIME *day_time)
{
	TIME_LIST_NODE *tl_node = NULL;
	TIME_LIST_NODE *n = NULL;

	list_for_each_entry_safe(tl_node, n, time_header, list) {
		if (!is_time_valid(&tl_node->trgr_time, day_time)) {
			list_del(&tl_node->list);
			free_ptr(tl_node);
		}
	}
}

/*
 * Function: is_time_existent
 * Description: check time list whether the trigger time exists
 * input:	@time_header - time list head pointer
 *			@trgr_time - trigger time to match
 * return:	false -- non-existent
 *			true -- existent
*/
static bool is_time_existent(struct list_head *time_header, TRIGGER_TIME *trgr_time)
{
	TIME_LIST_NODE *tl_node = NULL;

	list_for_each_entry(tl_node, time_header, list) {
		if (0 == memcmp(&tl_node->trgr_time, trgr_time, sizeof(TRIGGER_TIME))) {
			return true;
		}
	}
	return false;
}

/*
 * Function: add_trigger_time
 * Description: add trigger time to the time list
 * Input:	@time_header - time list head pointer
 *			@trgr_time - time to add
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int add_trigger_time(struct list_head *time_header, TRIGGER_TIME *trgr_time)
{
	TIME_LIST_NODE *tl_node = NULL;

	if (!is_time_existent(time_header, trgr_time)) {
		/*time not exists, kmalloc new time node*/
		tl_node = (TIME_LIST_NODE*)kmalloc(sizeof(TIME_LIST_NODE), GFP_ATOMIC);
		if (IS_ERR_OR_NULL(tl_node)) {
			pr_err("hw_packetmonitor %s: malloc failed!\n", __func__);
			return -1;
		}
		memset(tl_node, 0, sizeof(TIME_LIST_NODE));
		memcpy(&tl_node->trgr_time, trgr_time, sizeof(TRIGGER_TIME));

		/*add time node*/
		list_add_tail(&tl_node->list, time_header);
	}
	return 0;
}

/*
 * Function: add_uid_tree_node
 * Description: add a uid tree node
 * Input:	@uid_info - info that will be added to the node
 * Output:
 * Return:	NULL -- failed
 *			corresponding UID_TREE_NODE struct pointer -- successed
*/
static UID_TREE_NODE *add_uid_tree_node(UID_MATCH_INFO *uid_info)
{
	UID_TREE_NODE *ut_node = NULL;
	UID_TREE_NODE *tmp_node = NULL;
	struct rb_node **tmp = &(uid_tree_root.rb_node);
	struct rb_node *parent = NULL;

	/*kmalloc new uid tree node*/
	ut_node = (UID_TREE_NODE*)kmalloc(sizeof(UID_TREE_NODE), GFP_ATOMIC);
	if (IS_ERR_OR_NULL(ut_node)) {
		pr_err("hw_packetmonitor %s: malloc failed!\n", __func__);
		return NULL;
	}
	memset(ut_node, 0, sizeof(UID_TREE_NODE));
	memcpy(&ut_node->uid_info, uid_info, sizeof(UID_MATCH_INFO));
	ut_node->mnt_state = START_MONITOR;
	INIT_LIST_HEAD(&ut_node->time_header);

	/*find added position*/
	while (!IS_ERR_OR_NULL(*tmp)) {
		parent = *tmp;
		tmp_node = container_of(parent, UID_TREE_NODE, uid_node);
		if (ut_node->uid_info.uid < tmp_node->uid_info.uid) {
			tmp = &((*tmp)->rb_left);
 		} else if (ut_node->uid_info.uid > tmp_node->uid_info.uid) {
			tmp = &((*tmp)->rb_right);
		} else {
			pr_err("hw_packetmonitor %s: can't find add position!\n", __func__);
			free_ptr(ut_node);
			return NULL;
		}
	}

	/*add uid tree node*/
	rb_link_node(&ut_node->uid_node, parent, tmp);
	rb_insert_color(&ut_node->uid_node, &uid_tree_root);
	return ut_node;
}

/*
 * Function: add_uid
 * Description: get add-uid command, if uid exists, directly add
 *				trigger time, or add uid tree node first
 * Input:	@mnt_cmd - source info
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int add_uid(MONITOR_CMD *mnt_cmd)
{
	UID_TREE_NODE *ut_node = NULL;
	struct timeval tv;
	PACKET_TIME time;
	int ret = -1;

	write_lock_bh(&uid_rwlock);
	ut_node = search_uid(mnt_cmd->uid_info.uid);
	if (IS_ERR_OR_NULL(ut_node)) {
		/*uid not exists*/
		ut_node = add_uid_tree_node(&mnt_cmd->uid_info);
		if (IS_ERR_OR_NULL(ut_node)) {
			pr_err("hw_packetmonitor %s: add uid tree node failed!\n", __func__);
			goto err;
		}
	}

	/*uid exists*/
	do_gettimeofday(&tv);
	time.tv_sec = (u32)tv.tv_sec;
	time.tv_usec = (u32)tv.tv_usec;
	update_trigger_time(&ut_node->time_header, &time);
	if (is_time_valid(&mnt_cmd->trgr_time, &time)) {
		/*time is valid*/
		if (add_trigger_time(&ut_node->time_header, &mnt_cmd->trgr_time) < 0) {
			pr_err("hw_packetmonitor %s: add trigger time failed!\n", __func__);
			goto err;
		}
	}
	ret = 0;
err:
	write_unlock_bh(&uid_rwlock);
	return ret;
}

/*
 * Function: del_uid_tree_node
 * Description: delete a uid tree node from uid tree,
 *				including the corresponding time list
 * Input:	@ut_node - uid tree node to delete
 * Output:
 * Return:	void
*/
static void del_uid_tree_node(UID_TREE_NODE *ut_node)
{
	TIME_LIST_NODE *t_pos = NULL;
	TIME_LIST_NODE *t_n = NULL;

	/*delete time list*/
	list_for_each_entry_safe(t_pos, t_n, &ut_node->time_header, list) {
		list_del(&t_pos->list);
		free_ptr(t_pos);
	}

	/*delete uid tree node*/
	rb_erase(&ut_node->uid_node, &uid_tree_root);
	free_ptr(ut_node);
}

/*
 * Function: del_uid
 * Description: get del-uid command, delete all info of a uid
 *				from the tree
 * Input:	@uid - uid to delete
 * Output:
 * Return:	void
*/
static void del_uid(kuid_t uid)
{
	UID_TREE_NODE *ut_node = NULL;

	write_lock_bh(&uid_rwlock);
	ut_node = search_uid(uid);
	if (!IS_ERR_OR_NULL(ut_node)) {
		/*uid exists*/
		del_uid_tree_node(ut_node);
	}
	write_unlock_bh(&uid_rwlock);
}

/*
 * Function: clean_up_uid_tree
 * Description: clean up the uid tree
 * Input:
 * Output:
 * Return:	void
*/
static void clean_up_uid_tree(void)
{
	struct rb_node *node = NULL;
	UID_TREE_NODE *pos = NULL;

	/*find smallest uid*/
	node = rb_first(&uid_tree_root);
	write_lock_bh(&uid_rwlock);
	while (!IS_ERR_OR_NULL(node)) {
		pos = rb_entry(node, UID_TREE_NODE, uid_node);

		/*delete uid*/
		if (!IS_ERR_OR_NULL(pos)) {
			del_uid_tree_node(pos);
		}
		node = rb_first(&uid_tree_root);
	}
	write_unlock_bh(&uid_rwlock);
}

/*
 * Function: get_skb_protocol_hdr
 * Description: get protocol head address including
 *				IP and TCP from sk_buff
 * Input:	@skb - source buffer
 *			@ip_version - IP version, ipv4 or ipv6
 * Output:	@pro_hdr - PROTOCOL_HDR struct to save the hdr
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int get_skb_protocol_hdr(struct sk_buff *skb, u8 ip_version, PROTOCOL_HDR *pro_hdr)
{
	struct iphdr _ipv4h;
	struct ipv6hdr _ipv6h;
	struct tcphdr _tcph;
	int offset = 0;
	u8 nexthdr = 0;
	__be16 frag_off;

	offset = skb_network_offset(skb);
	switch (ip_version) {
		case IP_VERSION_V4:
			pro_hdr->ip_hdr.v4 = skb_header_pointer(skb, offset, sizeof(_ipv4h), &_ipv4h);
			if (!IS_ERR_OR_NULL(pro_hdr->ip_hdr.v4)) {
				if (IPPROTO_TCP == pro_hdr->ip_hdr.v4->protocol) {
					pro_hdr->tcp_hdr = skb_header_pointer(skb, offset + ip_hdrlen(skb), sizeof(_tcph), &_tcph);
					if (!IS_ERR_OR_NULL(pro_hdr->tcp_hdr)) {
						return 0;
					}
				}
			}
			break;
		case IP_VERSION_V6:
			pro_hdr->ip_hdr.v6 = skb_header_pointer(skb, offset, sizeof(_ipv6h), &_ipv6h);
			if (!IS_ERR_OR_NULL(pro_hdr->ip_hdr.v6)) {
				nexthdr = pro_hdr->ip_hdr.v6->nexthdr;
				offset += sizeof(struct ipv6hdr);
				offset = ipv6_skip_exthdr(skb, offset, &nexthdr, &frag_off);
				if (IPPROTO_TCP == nexthdr) {
					pro_hdr->tcp_hdr = skb_header_pointer(skb, offset, sizeof(_tcph), &_tcph);
					if (!IS_ERR_OR_NULL(pro_hdr->tcp_hdr)) {
						return 0;
					}
				}
			}
			break;
		default:
			return -1;
	}
	return -1;
}

/*
 * Function: get_skb_ipport
 * Description: get IP and port from sk_buff
 * Input:	@skb - source buffer
 *			@ip_version - IP version, ipv4 or ipv6
 * Output:	@ipport - IPPORT struct to save IP and port
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int get_skb_ipport(struct sk_buff *skb, u8 ip_version, IPPORT *ipport)
{
	PROTOCOL_HDR pro_hdr;

	if (get_skb_protocol_hdr(skb, ip_version, &pro_hdr) < 0) {
		return -1;
	}

	switch (ip_version) {
		case IP_VERSION_V4:
			ipport->ip.v4.daddr = pro_hdr.ip_hdr.v4->daddr;
			ipport->ip.v4.saddr = pro_hdr.ip_hdr.v4->saddr;
			break;
		case IP_VERSION_V6:
			ipport->ip.v6.saddr = pro_hdr.ip_hdr.v6->saddr;
			ipport->ip.v6.daddr = pro_hdr.ip_hdr.v6->daddr;
			break;
		default:
			return -1;
	}
	ipport->port.dport = pro_hdr.tcp_hdr->dest;
	ipport->port.sport = pro_hdr.tcp_hdr->source;
	return 0;
}

/*
 * Function: get_skb_packet_time
 * Description: get the packet time from sk_buff if exists,
 *				or get the day time instead
 * Input:	@skb - source buffer
 * Output:	@pkt_time - PACKET_TIME struct to save the time
 * Return:	void
*/
static void get_skb_packet_time(struct sk_buff *skb, PACKET_TIME *pkt_time)
{
	struct timeval tv;

	tv = ktime_to_timeval(skb->tstamp);

	/*in some sk_buff, time may be zero*/
	if (0 == tv.tv_sec) {
		do_gettimeofday(&tv);
	}
	pkt_time->tv_sec = (u32)tv.tv_sec;
	pkt_time->tv_usec = (u32)tv.tv_usec;
}

/*
 * Function: get_skb_info
 * Description: get monitor info from sk_buff including SKB_STATE(state info)
 *				and SKB_SADDR(server IP)
 * Input:	@skb - source buffer
 *			@ip_version - ip version, ipv4 or ipv6
 *			@dir - skb transmission direction, in or out
 * Output:	@mnt_info - MONITOR_INFO struct to save the info
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int get_skb_info(struct sk_buff *skb, u8 ip_version, int dir, MONITOR_INFO *mnt_info)
{
	PROTOCOL_HDR pro_hdr;

	if (get_skb_protocol_hdr(skb, ip_version, &pro_hdr) < 0) {
		return -1;
	}

	switch (ip_version) {
		case IP_VERSION_V4:
			if (DIR_LOCAL_IN == dir) {
				mnt_info->skb_raddr.v4.raddr = pro_hdr.ip_hdr.v4->saddr;
			} else if (DIR_LOCAL_OUT == dir) {
				mnt_info->skb_raddr.v4.raddr = pro_hdr.ip_hdr.v4->daddr;
			} else {
				return -1;
			}
			mnt_info->skb_state.protocol = IP_VERSION_V4 & 0x04;
			break;
		case IP_VERSION_V6:
			if (DIR_LOCAL_IN == dir) {
				mnt_info->skb_raddr.v6.raddr = pro_hdr.ip_hdr.v6->saddr;
			} else if (DIR_LOCAL_OUT == dir) {
				mnt_info->skb_raddr.v6.raddr = pro_hdr.ip_hdr.v6->daddr;
			} else {
				return -1;
			}
			mnt_info->skb_state.protocol = IP_VERSION_V6 & 0x06;
			break;
		default:
			return -1;
	}
	mnt_info->skb_state.dir = dir & 0x01;
	mnt_info->skb_state.syn = pro_hdr.tcp_hdr->syn;
	mnt_info->skb_state.ack = pro_hdr.tcp_hdr->ack;
	mnt_info->skb_state.fin = pro_hdr.tcp_hdr->fin;
	mnt_info->skb_state.none = NONE;
	return 0;
}

/*
 * Function: get_tcp_sk
 * Description: get sock struct from protocol stack with IP and port
 * Input:	@skb - source buffer
 *			@ipport - IP and port to match
 *			@ip_version - ip version, ipv4 or ipv6
 *			@dir - skb transmission direction, in or out
 * Output:
 * Return:	NULL -- failed
 *			corresponding sock struct pointer -- successed
*/
static struct sock *get_tcp_sk(struct sk_buff *skb, IPPORT *ipport, u8 ip_version, int dir)
{
	struct sock *sk = NULL;
	__be32 v4_localaddr;
	__be32 v4_remoteaddr;
	struct in6_addr v6_localaddr;
	struct in6_addr v6_remoteaddr;
	__be16 localport;
	__be16 remoteport;

	switch (ip_version) {
		case IP_VERSION_V4:
			if (DIR_LOCAL_IN == dir) {
				v4_localaddr = ipport->ip.v4.daddr;
				v4_remoteaddr = ipport->ip.v4.saddr;
				localport = ipport->port.dport;
				remoteport = ipport->port.sport;
			} else if (DIR_LOCAL_OUT == dir) {
				v4_localaddr = ipport->ip.v4.saddr;
				v4_remoteaddr = ipport->ip.v4.daddr;
				localport = ipport->port.sport;
				remoteport = ipport->port.dport;
			} else {
				return NULL;
			}
			sk = inet_lookup(dev_net(skb_dst(skb)->dev), &tcp_hashinfo,
								v4_remoteaddr, remoteport,
								v4_localaddr, localport, inet_iif(skb));
			break;
		case IP_VERSION_V6:
			if (DIR_LOCAL_IN == dir) {
				v6_localaddr = ipport->ip.v6.daddr;
				v6_remoteaddr = ipport->ip.v6.saddr;
				localport = ipport->port.dport;
				remoteport = ipport->port.sport;
			} else if (DIR_LOCAL_OUT == dir) {
				v6_localaddr = ipport->ip.v6.saddr;
				v6_remoteaddr = ipport->ip.v6.daddr;
				localport = ipport->port.sport;
				remoteport = ipport->port.dport;
			} else {
				return NULL;
			}
			sk = inet6_lookup(dev_net(skb_dst(skb)->dev), &tcp_hashinfo,
								&v6_remoteaddr, remoteport,
								&v6_localaddr, ntohs(localport), inet_iif(skb));
			break;
		default:
			return NULL;
	}
	return sk;
}

/*
 * Function: get_i_uid
 * Description: get uid from inode struct by calling kernel
 *				function sock_i_uid()
 * Input:	@sk - source sock struct pointer
 * Output:
 * Return:	ERROR_UID -- failed
 *			uid -- successed
*/
static kuid_t get_i_uid(struct sock *sk)
{
	if ((TCP_ESTABLISHED == sk->sk_state) || (TCP_LISTEN == sk->sk_state)) {
		return sock_i_uid(sk);
	}
	return ERROR_UID;
}

/*
 * Function: get_f_uid
 * Description: get uid from sock struct in sk_buff
 * Input:	@sk - source sock struct pointer
 * Output:
 * Return:	ERROR_UID -- failed
 *			uid -- successed
*/
static kuid_t get_f_uid(struct sock *sk)
{
	if (IS_ERR_OR_NULL(sk->sk_socket)) {
		return ERROR_UID;
	} else if (IS_ERR_OR_NULL(sk->sk_socket->file)) {
		return ERROR_UID;
	} else if (IS_ERR_OR_NULL(sk->sk_socket->file->f_cred)) {
		return ERROR_UID;
	} else {
		return sk->sk_socket->file->f_cred->uid;
	}
}

/*
 * Function: get_skb_uid
 * Description: get uid from sk_buff, if sock in it exists,
 *				call get_f_uid(), or call get_i_uid()
 * Input:	@skb - source buffer
 *			@ip_version - ip version, ipv4 or ipv6
 *			@dir - skb transmission direction, in or out
 * Output:
 * Return:	ERROR_UID -- failed
 *			uid -- successed
*/
static kuid_t get_skb_uid(struct sk_buff *skb, u8 ip_version, int dir)
{
	struct sock *sk = NULL;
	IPPORT ipport;
	kuid_t uid = 0;

	if (!IS_ERR_OR_NULL(skb->sk) && DIR_LOCAL_OUT == dir) {
		/*sock in sk_buff exists*/
		uid = get_f_uid(skb->sk);
	} else {
		/*sock in sk_buff not exists*/
		if (get_skb_ipport(skb, ip_version, &ipport) < 0) {
			return ERROR_UID;
		}

		/*get sock from TCP layer*/
		sk = get_tcp_sk(skb, &ipport, ip_version, dir);
		if (IS_ERR_OR_NULL(sk)) {
			return ERROR_UID;
		}

		/*get uid from inode according to sock*/
		uid = get_i_uid(sk);
		sock_put(sk);
	}
	return uid;
}

/*
 * Function: is_time_match
 * Description: check time list whether packet time exists
 * Input:	@time_header - time list head pointer
 *			@pkt_time - packet time to match
 * Output:
 * Return:	false -- non-existent
 *			true -- existent
*/
static bool is_time_match(struct list_head *time_header, PACKET_TIME *pkt_time)
{
	TIME_LIST_NODE *tl_node = NULL;

	list_for_each_entry(tl_node, time_header, list) {
		if (pkt_time->tv_sec >= (tl_node->trgr_time.time.tv_sec - tl_node->trgr_time.offset)
			&& pkt_time->tv_sec <= (tl_node->trgr_time.time.tv_sec + tl_node->trgr_time.offset)) {
			return true;
		}
	}
	return false;
}

/*
 * Function: match_uid
 * Description: check uid tree whether sk_buff is wanted by matching
 *				uid, monitor state, data_len and packet time
 * Input:	@skb - source buffer
 *			@skb_info - info to match
 * Output:
 * Return:	false -- not matched
 *			true -- matched
*/
static bool match_uid(struct sk_buff *skb, SKB_MATCH_INFO *skb_info)
{
	UID_TREE_NODE *ut_node = NULL;
	bool ret = false;

	read_lock_bh(&uid_rwlock);
	ut_node = search_uid(skb_info->uid_info.uid);
	if (IS_ERR_OR_NULL(ut_node)) {
		/*uid not exists*/
		goto not_match;
	}

	/*uid exists*/
	/*find if monitored*/
	if (STOP_MONITOR == ut_node->mnt_state) {
		goto not_match;
	}

	/*find if skb len smaller than wanted len*/
	if (skb->len >= ut_node->uid_info.data_len) {
		goto not_match;
	}
	skb_info->uid_info.data_len = skb->len;

	/*find if skb time wanted*/
	get_skb_packet_time(skb, &skb_info->pkt_time);
	if (!is_time_match(&ut_node->time_header, &skb_info->pkt_time)) {
		goto not_match;
	}
	ret = true;
not_match:
	read_unlock_bh(&uid_rwlock);
	return ret;
}

/*
 * Function: pack_monitor_info
 * Description: pack monitor info into a char buffer
 * Input:	@mnt_info - source info
 *			@ip_version - IP version, ipv4 or ipv6
 * Output:	@buf - buffer to save the info
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int pack_monitor_info(MONITOR_INFO *mnt_info, u8 ip_version, char *buf)
{
	int info_len = 0;

	switch (ip_version) {
		case IP_VERSION_V4:
			info_len = sizeof(MONITOR_INFO) - V4_V6_ADDR_SIZE_DIFF;
			break;
		case IP_VERSION_V6:
			info_len = sizeof(MONITOR_INFO);
			break;
		default:
			return -1;
	}
	memcpy(buf, mnt_info, info_len);
	return info_len;
}

/*
 * Function: send_up_monitor_info
 * Description: send up monitor info to user
 * Input:	@mnt_info - info to send up
 *			@ip_version - IP version, ipv4 or ipv6
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int send_up_monitor_info(MONITOR_INFO *mnt_info, u8 ip_version)
{
	char *buffer = NULL;
	size_t info_len = 0;
	int buf_len = 0;
	int ret = -1;

	buf_len = sizeof(MONITOR_INFO);
	buffer = (char*)kmalloc(buf_len, GFP_ATOMIC);
	if (IS_ERR_OR_NULL(buffer)) {
		pr_err("hw_packetmonitor %s: malloc failed!\n", __func__);
		goto err;
	}
	memset(buffer, 0, buf_len);

	info_len = pack_monitor_info(mnt_info, ip_version, buffer);
	if (info_len < 0) {
		pr_err("hw_packetmonitor %s: pack monitor info failed!\n", __func__);
		goto out;
	}

	/*send up info to user*/
	ret = kstate(CHANNEL_ID_LOCAL_CLIENT, PACKET_TAG_MONITOR_INFO, buffer, info_len);
	if (ret < 0) {
		pr_err("hw_packetmonitor %s: kstate monitor info failed!\n", __func__);
		goto out;
	}
	ret = 0;
out:
	free_ptr(buffer);
err:
	return ret;
}

/*
 * Function: request_answer
 * Description: answer to user for a connection request
 * Input:
 * Output:
 * Return:	void
*/
static void request_answer(void)
{
	MONITOR_INFO mnt_info;
	int info_len = sizeof(MONITOR_INFO);

	memset(&mnt_info, 0, info_len);
	mnt_info.skb_state.protocol = IP_VERSION_V4 & 0x04;
	send_up_monitor_info(&mnt_info, IP_VERSION_V4);
}

/*
 * Function: update_monitor_state
 * Description: update monitor state of uid
 * Input:	@uid - uid to match
 *			@state - monitor state, start or stop
 * Output:
 * Return:	@void
*/
static void update_monitor_state(kuid_t uid, u8 state)
{
	UID_TREE_NODE *pnode = NULL;

	write_lock_bh(&uid_rwlock);
	pnode = search_uid(uid);
	if (!IS_ERR_OR_NULL(pnode)) {
		/*uid exists*/
		pnode->mnt_state = state;
	}
	write_unlock_bh(&uid_rwlock);
}

/*
 * Function: netfilter_monitor_func
 * Description: monitor main function, all monitor hook
 *				functions will call this
 * Input:	@skb - source buffer
 *			@ip_version - IP version, ipv4 or ipv6
 *			@dir - skb transmission direction, in or out
 * Output:
 * Return:	void
*/
static inline void netfilter_monitor_func(struct sk_buff *skb, u8 ip_version, int dir)
{
	MONITOR_INFO mnt_info;

	mnt_info.skb_info.uid_info.uid = get_skb_uid(skb, ip_version, dir);
	if (mnt_info.skb_info.uid_info.uid >= UID_MIN_BOUNDARY) {
		/*uid is valid*/
		if (match_uid(skb, &mnt_info.skb_info)) {
			/*uid is wanted*/
			if (0 == get_skb_info(skb, ip_version, dir, &mnt_info)) {
				/*get useful info successed*/
				if (send_up_monitor_info(&mnt_info, ip_version) < 0) {
					/*send up info failed*/
					pr_err("hw_packetmonitor %s %u %d: send up failed!\n", __func__, ip_version, dir);
				}
			}
		}
	}
}

/*
 * Function: hook_kstate_cb
 * Description: kstate call back function to get command,
 *				then do the right operation
 * Input:	@src - source module tag
 *			@tag - packet tag received
 *			@data - buffer received
 *			@len - buffer length received
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int hook_kstate_cb(CHANNEL_ID src, PACKET_TAG tag, const char *data, size_t len)
{
	MONITOR_CMD mnt_cmd;

	if (len != sizeof(MONITOR_CMD)) {
		pr_err("hw_packetmonitor %s: buffer len invalid!\n", __func__);
		return -1;
	}
	memcpy(&mnt_cmd, data, sizeof(MONITOR_CMD));

	switch (mnt_cmd.cmd) {
		case ADD_SINGLE_UID:
			if (add_uid(&mnt_cmd) < 0) {
				return -1;
			}
			break;
		case DEL_SINGLE_UID:
			del_uid(mnt_cmd.uid_info.uid);
			break;
		case START_MONITOR_SINGLE_UID:
			update_monitor_state(mnt_cmd.uid_info.uid, START_MONITOR);
			break;
		case STOP_MONITOR_SINGLE_UID:
			update_monitor_state(mnt_cmd.uid_info.uid, STOP_MONITOR);
			break;
		case START_MONITOR_ALL_UID:
			atomic_set(&monitor_state_of_in, START_MONITOR);
			atomic_set(&monitor_state_of_out, START_MONITOR);
			break;
		case STOP_MONITOR_ALL_UID:
			atomic_set(&monitor_state_of_in, STOP_MONITOR);
			atomic_set(&monitor_state_of_out, STOP_MONITOR);
			break;
		case START_MONITOR_LOCAL_IN:
			atomic_set(&monitor_state_of_in, START_MONITOR);
			break;
		case STOP_MONITOR_LOCAL_IN:
			atomic_set(&monitor_state_of_in, STOP_MONITOR);
			break;
		case START_MONITOR_LOCAL_OUT:
			atomic_set(&monitor_state_of_out, START_MONITOR);
			break;
		case STOP_MONITOR_LOCAL_OUT:
			atomic_set(&monitor_state_of_out, STOP_MONITOR);
			break;
		case DEL_ALL_UID:
			clean_up_uid_tree();
			break;
		case CONNECTION_REQUEST:
			request_answer();
			break;
		default:
			return -1;
	}
	return 0;
}

/*
 * Function: hook_ipv4_local_in_cb
 * Description: netfilter hook call back function on ipv4 LOCAL_IN
 * Input:	@hooknum - hook position, here is NF_INET_LOCAL_IN
 *			@in - net_device info, available on in hook
 *			@out - net_device info, available on out hook
 *			@okfn - netfilter call back function
 * Output:
 * Return:	NF_ACCEPT -- we should all return this to make sure that
 *						 sk_buff continue to be transfered
*/
static unsigned int hook_ipv4_local_in_cb(unsigned int hooknum,
												struct sk_buff *skb,
												const struct net_device *in,
												const struct net_device *out,
												int (*okfn)(struct sk_buff*))
{
	if (START_MONITOR == atomic_read(&monitor_state_of_in)) {
		netfilter_monitor_func(skb, IP_VERSION_V4, DIR_LOCAL_IN);
	}
	return NF_ACCEPT;
}

/*
 * Function: hook_ipv4_local_out_cb
 * Description: netfilter hook call back function on ipv4 LOCAL_OUT
 * Input:	@hooknum - hook position, here is NF_INET_LOCAL_OUT
 *			@in - net_device info, available on in hook
 *			@out - net_device info, available on out hook
 *			@okfn - netfilter call back function
 * Output:
 * Return:	NF_ACCEPT -- we should all return this to make sure that
 *						 sk_buff continue to be transfered
*/
static unsigned int hook_ipv4_local_out_cb(unsigned int hooknum,
												struct sk_buff *skb,
												const struct net_device *in,
												const struct net_device *out,
												int (*okfn)(struct sk_buff*))
{
	if (START_MONITOR == atomic_read(&monitor_state_of_out)) {
		netfilter_monitor_func(skb, IP_VERSION_V4, DIR_LOCAL_OUT);
	}
	return NF_ACCEPT;
}

/*
 * Function: hook_ipv6_local_in_cb
 * Description: netfilter hook call back function on ipv6 LOCAL_IN
 * Input:	@hooknum - hook position, here is NF_INET_LOCAL_IN
 *			@in - net_device info, available on in hook
 *			@out - net_device info, available on out hook
 *			@okfn - netfilter call back function
 * Output:
 * Return:	NF_ACCEPT -- we should all return this to make sure that
 *						 sk_buff continue to be transfered
*/
static unsigned int hook_ipv6_local_in_cb(unsigned int hooknum,
												struct sk_buff *skb,
												const struct net_device *in,
												const struct net_device *out,
												int (*okfn)(struct sk_buff*))
{
	if (START_MONITOR == atomic_read(&monitor_state_of_in)) {
		netfilter_monitor_func(skb, IP_VERSION_V6, DIR_LOCAL_IN);
	}
	return NF_ACCEPT;
}

/*
 * Function: hook_ipv6_local_out_cb
 * Description: netfilter hook call back function on ipv6 LOCAL_OUT
 * Input:	@hooknum - hook position, here is NF_INET_LOCAL_OUT
 *			@in - net_device info, available on in hook
 *			@out - net_device info, available on out hook
 *			@okfn - netfilter call back function
 * Output:
 * Return:	NF_ACCEPT -- we should all return this to make sure that
 *						 sk_buff continue to be transfered
*/
static unsigned int hook_ipv6_local_out_cb(unsigned int hooknum,
												struct sk_buff *skb,
												const struct net_device *in,
												const struct net_device *out,
												int (*okfn)(struct sk_buff*))
{
	if (START_MONITOR == atomic_read(&monitor_state_of_out)) {
		netfilter_monitor_func(skb, IP_VERSION_V6, DIR_LOCAL_OUT);
	}
	return NF_ACCEPT;
}

static struct kstate_opt kstate_hook_opt = {
	.name 		= 	"hw_packetmonitor",
	.dst 		= 	CHANNEL_ID_LOCAL_SERVER,
	.tag 		= 	PACKET_TAG_MONITOR_CMD,
	.hook 		= 	hook_kstate_cb,
};

static struct nf_hook_ops ipv4_local_in_ops = {
	.hook 		= 	hook_ipv4_local_in_cb,
	.owner 		= 	THIS_MODULE,
	.pf 		= 	NFPROTO_IPV4,
	.hooknum 	= 	NF_INET_LOCAL_IN,
	.priority 	= 	NF_IP_PRI_FIRST,
};

static struct nf_hook_ops ipv4_local_out_ops = {
	.hook 		= 	hook_ipv4_local_out_cb,
	.owner 		= 	THIS_MODULE,
	.pf 		= 	NFPROTO_IPV4,
	.hooknum 	= 	NF_INET_LOCAL_OUT,
	.priority 	= 	NF_IP_PRI_FIRST,
};

static struct nf_hook_ops ipv6_local_in_ops = {
	.hook 		= 	hook_ipv6_local_in_cb,
	.owner 		= 	THIS_MODULE,
	.pf 		= 	NFPROTO_IPV6,
	.hooknum 	= 	NF_INET_LOCAL_IN,
	.priority 	= 	NF_IP6_PRI_FIRST,
};

static struct nf_hook_ops ipv6_local_out_ops = {
	.hook 		= 	hook_ipv6_local_out_cb,
	.owner 		= 	THIS_MODULE,
	.pf 		= 	NFPROTO_IPV6,
	.hooknum 	= 	NF_INET_LOCAL_OUT,
	.priority 	= 	NF_IP6_PRI_FIRST,
};

static int __init packet_monitor_init(void)
{
	atomic_set(&monitor_state_of_in, STOP_MONITOR);
	atomic_set(&monitor_state_of_out, STOP_MONITOR);

	rwlock_init (&uid_rwlock);

	uid_tree_root = RB_ROOT;

	if (kstate_register_hook(&kstate_hook_opt) < 0) {
		pr_err("hw_packetmonitor %s: register kstate failed!\n", __func__);
		goto register_kstate_err;
	}

	if (nf_register_hook(&ipv4_local_in_ops) < 0) {
		pr_err("hw_packetmonitor %s: register ipv4 in failed!\n", __func__);
		goto register_ipv4_local_in_err;
	}

	if (nf_register_hook(&ipv4_local_out_ops) < 0) {
		pr_err("hw_packetmonitor %s: register ipv4 out failed!\n", __func__);
		goto register_ipv4_local_out_err;
	}

	if (nf_register_hook(&ipv6_local_in_ops) < 0) {
		pr_err("hw_packetmonitor %s: register ipv6 in failed!\n", __func__);
		goto register_ipv6_local_in_err;
	}

	if (nf_register_hook(&ipv6_local_out_ops) < 0) {
		pr_err("hw_packetmonitor %s: register ipv6 out failed!\n", __func__);
		goto register_ipv6_local_out_err;
	}

	pr_info("hw_packetmonitor %s: inited!\n", __func__);
	return 0;

register_ipv6_local_out_err:
	nf_unregister_hook(&ipv6_local_in_ops);
register_ipv6_local_in_err:
	nf_unregister_hook(&ipv4_local_out_ops);
register_ipv4_local_out_err:
	nf_unregister_hook(&ipv4_local_in_ops);
register_ipv4_local_in_err:
	kstate_unregister_hook(&kstate_hook_opt);
register_kstate_err:
	return -1;
}

static void __exit packet_monitor_exit(void)
{
	nf_unregister_hook(&ipv6_local_out_ops);
	nf_unregister_hook(&ipv6_local_in_ops);
	nf_unregister_hook(&ipv4_local_out_ops);
	nf_unregister_hook(&ipv4_local_in_ops);

	kstate_unregister_hook(&kstate_hook_opt);

	clean_up_uid_tree();
}

late_initcall(packet_monitor_init);
module_exit(packet_monitor_exit);
