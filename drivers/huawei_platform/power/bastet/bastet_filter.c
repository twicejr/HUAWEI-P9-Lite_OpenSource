/* bastet_utils.c
 *
 * Provide Bastet filter.
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
#include <linux/list.h>
#include <uapi/linux/netfilter_ipv6.h>
#include <huawei_platform/power/bastet/bastet_utils.h>
#include <net/icmp.h> /*icmp_send*/
#include <uapi/linux/icmp.h> /*ICMP_NET_ANO ICMP_DEST_UNREACH*/

extern int get_uid_by_pid(struct set_process_info *info);

struct st_proc_info_node {
    struct set_process_info info;
    struct list_head list;
};

struct list_head g_white_list_head;
static spinlock_t proc_info_lock;
static int g_special_uid;
/**
 * Function: get_process_info_by_skb
 * Description: get uid and pid by skb
 * Input:skb
 * Output:
 * Return:
 * Date: 2015.12.24
 * Author: Zhang Kaige ID: 00220931
 */
static void get_process_info_by_skb(struct sk_buff *skb,
									struct set_process_info *info)
{
	if ( (NULL == skb) || (NULL == info) ) {
		BASTET_LOGE("invalid parameter");
		return;
	}

	if (NULL == skb->sk ) {
		BASTET_LOGE("skb->sk is NULL");
		return;
	}

	info->uid = sock_i_uid(skb->sk);
	info->pid = current->pid;
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

static unsigned int hook_local_out_cb(unsigned int hooknum,
												struct sk_buff *skb,
												const struct net_device *in,
												const struct net_device *out,
												int (*okfn)(struct sk_buff*))
{


	struct set_process_info info;
	struct list_head *pos;
	struct st_proc_info_node *tmp_node;
	bool found = false;

	info.pid = -1;
	info.uid = -1;
	get_process_info_by_skb(skb, &info);

	BASTET_LOGI("uid=%d,pid=%d", info.uid, info.pid);
	spin_lock_bh(&proc_info_lock);
	if (list_empty(&g_white_list_head)) {
		spin_unlock_bh(&proc_info_lock);
		BASTET_LOGE("ipv4 NF_DROP1");
		return NF_DROP;
	}
	list_for_each(pos, &g_white_list_head) {
		tmp_node = list_entry(pos, struct st_proc_info_node, list);
		BASTET_LOGI("list uid =%d,pid=%d", tmp_node->info.uid, tmp_node->info.pid);
		if (tmp_node->info.uid != info.uid) {
			continue;
		}
		if (tmp_node->info.uid != g_special_uid ) {
			BASTET_LOGI("uid=%d and not %d match success", info.uid, g_special_uid);
			found = true;
			break;
		} else {
			if (tmp_node->info.pid == info.pid) {
				BASTET_LOGI("uid=%d,pid=%d match success", info.uid, info.pid);
				found = true;
				break;
			}
		}
	}

	if (found) {
		BASTET_LOGE("ipv4 NF_ACCEPT");
		spin_unlock_bh(&proc_info_lock);
		return NF_ACCEPT; 
	} else {
		BASTET_LOGE("ipv4 NF_DROP2");
		if (skb->sk) {
			skb->sk->sk_err = icmp_err_convert[ICMP_NET_ANO].errno;
			skb->sk->sk_error_report(skb->sk);
		}
		spin_unlock_bh(&proc_info_lock);
		return NF_DROP;
	}
}

static struct nf_hook_ops ipv4_local_out_ops = {
	.hook 		= 	hook_local_out_cb,
	.owner 		= 	THIS_MODULE,
	.pf 		= 	NFPROTO_IPV4,
	.hooknum 	= 	NF_INET_LOCAL_OUT,
	.priority 	= 	NF_IP_PRI_FIRST,
};

static struct nf_hook_ops ipv6_local_out_ops = {
	.hook 		= 	hook_local_out_cb,
	.owner 		= 	THIS_MODULE,
	.pf 		= 	NFPROTO_IPV6,
	.hooknum 	= 	NF_INET_LOCAL_OUT,
	.priority 	= 	NF_IP6_PRI_FIRST,
};



static int add_proc_info_to_white_list(struct set_process_info *info)
{
	struct st_proc_info_node *new_node = NULL;
	struct st_proc_info_node *tmp_node = NULL;
	struct list_head *pos = NULL;
	struct list_head *n = NULL;

	if (info == NULL) {
		BASTET_LOGE("invalid parameter");
		return -EFAULT;
	}
	spin_lock_bh(&proc_info_lock);
	if (!list_empty(&g_white_list_head)) {
		list_for_each_safe(pos, n, &g_white_list_head) {
			tmp_node = list_entry(pos, struct st_proc_info_node, list);
			if (tmp_node->info.pid == info->pid) {
				BASTET_LOGI("pid =%d has existed in white list", info->pid);
				spin_unlock_bh(&proc_info_lock);
				return 0;
			}
		}
	}
	new_node = (struct st_proc_info_node *)kmalloc(sizeof(*new_node), GFP_ATOMIC);

	if (NULL == new_node) {
		BASTET_LOGE("kzalloc proc_info_node failed");
		spin_unlock_bh(&proc_info_lock);
		return -EFAULT;
	}

	if (get_uid_by_pid(info) != 0) {
		BASTET_LOGE("get_uid_by_pid fail");
		kfree(new_node);
		spin_unlock_bh(&proc_info_lock);
		return -EFAULT;
	}
	new_node->info.uid = info->uid;
	new_node->info.pid = info->pid;

	BASTET_LOGI("uid=%d, pid=%d add to list", new_node->info.uid, new_node->info.pid);
	list_add(&(new_node->list), &g_white_list_head);
	spin_unlock_bh(&proc_info_lock);
	return 0;
}


static int del_proc_info_from_white_list(struct set_process_info *info)
{
	struct st_proc_info_node *tmp_node;
	struct list_head *pos = NULL;
	struct list_head *n = NULL;

	if (NULL == info) {
		BASTET_LOGE("invalid parameter");
		return -EFAULT;
	}
	spin_lock_bh(&proc_info_lock);
	if (!list_empty(&g_white_list_head)) {
		list_for_each_safe(pos, n, &g_white_list_head) {
			tmp_node = list_entry(pos, struct st_proc_info_node, list);
			if (tmp_node->info.pid  == info->pid) {
				BASTET_LOGI("uid=%d, pid=%d delete", tmp_node->info.uid, tmp_node->info.pid);
				list_del(pos);
				kfree(tmp_node);
				break;
			}
		}
	}
	spin_unlock_bh(&proc_info_lock);
	return 0;
}


static int del_all_proc_info_from_white_list(void)
{
	struct st_proc_info_node *tmp_node;
	struct list_head *pos = NULL;
	struct list_head *n = NULL;

	spin_lock_bh(&proc_info_lock);
	if (!list_empty(&g_white_list_head)) {
		list_for_each_safe(pos, n, &g_white_list_head) {
			tmp_node = list_entry(pos, struct st_proc_info_node, list);
			list_del(pos);
			kfree(tmp_node);
		}
	}
	spin_unlock_bh(&proc_info_lock);
	return 0;
}

/**
 * Function: set_proc_info
 * Description: set process_info
 * Input:set_process_info
 * Output:
 * Return:
 * Date: 2015.12.24
 * Author: Zhang Kaige ID: 00220931
 */
int set_proc_info(struct set_process_info *info)
{
	int rc = 0;
	switch(info->cmd) {
		case CMD_ADD_PROC_INFO:
			rc = add_proc_info_to_white_list(info);
			break;
		case CMD_DEL_PROC_INFO:
			rc = del_proc_info_from_white_list(info);
			break;
		case CMD_DEL_ALL_INFO:
			rc = del_all_proc_info_from_white_list();
			break;
		default:
			BASTET_LOGE("invalid cmd");
			rc = -EFAULT;
			break;
	}
	return rc;
}

/**
 * Function: set_special_uid
 * Description: set netfilter 
 * Input:the special uid
 * Output:
 * Return:
 * Date: 2015.12.24
 * Author: Zhang Kaige ID: 00220931
 */
int set_special_uid(int32_t uid)
{
    spin_lock_bh(&proc_info_lock);
    g_special_uid = uid;
    spin_unlock_bh(&proc_info_lock);
    return 0;
}

/**
 * Function: set_netfilter
 * Description: set netfilter 
 * Input:state true register,false unregister
 * Output:
 * Return:
 * Date: 2015.12.24
 * Author: Zhang Kaige ID: 00220931
 */
int set_netfilter(bool state)
{
	static bool isRegistered = false;

	BASTET_LOGI("isRegister=%d", state);
	spin_lock_bh(&proc_info_lock);
	if (!state) {
		if (isRegistered) {
			nf_unregister_hook(&ipv4_local_out_ops);
			nf_unregister_hook(&ipv6_local_out_ops);
			isRegistered = false;
		}
		spin_unlock_bh(&proc_info_lock);
		return 0;
	}

	if (nf_register_hook(&ipv4_local_out_ops) < 0) {
		BASTET_LOGE("register ipv4 fail");
		nf_unregister_hook(&ipv4_local_out_ops);
		spin_unlock_bh(&proc_info_lock);
		return -EFAULT;
	}
	if (nf_register_hook(&ipv6_local_out_ops) < 0) {
		BASTET_LOGE("register ipv6 fail");
		nf_unregister_hook(&ipv4_local_out_ops);
		nf_unregister_hook(&ipv6_local_out_ops);
		spin_unlock_bh(&proc_info_lock);
		return -EFAULT;
	}
	isRegistered = true;
	spin_unlock_bh(&proc_info_lock);
	return 0;
}

/**
 * Function: bastet_filter_init
 * Description: init bastet filter info
 * Input:
 * Output:
 * Return:
 * Date: 2015.12.24
 * Author: Zhang Kaige ID: 00220931
 */
void bastet_filter_init(void)
{
    spin_lock_init(&proc_info_lock);
    INIT_LIST_HEAD(&g_white_list_head);
}
